<?php
header("Content-Type: application/json");

class SensorAPI {
    private $db;
    private $queueTable = 'sensor_queue';
    private $dataTable = 'sensor_data';

    public function __construct() {
        $this->connectDB();
    }

    /**
     * Establece la conexión a la base de datos usando los datos definidos en db.php.
     */
    private function connectDB() {
        require '../db.php'; // Este archivo debe definir: $servername, $username, $password, $dbname
        try {
            $this->db = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
            $this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        } catch(PDOException $e) {
            $this->sendResponse(500, ['error' => 'Error de conexión a la base de datos']);
        }
    }

    /**
     * Gestiona la petición HTTP (POST o GET) y valida que se incluya el parámetro hash.
     */
    public function handleRequest() {
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $data = json_decode(file_get_contents('php://input'), true);
        } elseif ($_SERVER['REQUEST_METHOD'] === 'GET') {
            $data = $_GET;
        } else {
            $this->sendResponse(405, ['error' => 'Método no permitido']);
        }

        if (!$data) {
            $this->sendResponse(400, ['error' => 'JSON inválido o vacío']);
        }

        // Validar que se envíe el hash
        if (!isset($data['hash']) || empty($data['hash'])) {
            $this->sendResponse(400, ['error' => 'Hash requerido']);
        }
        
        // Obtener el api_id a partir del hash proporcionado
        $api_id = $this->getApiId($data['hash']);
        if (!$api_id) {
            $this->sendResponse(400, ['error' => 'Hash inválido']);
        }

        // Eliminar el hash del array original y procesar el resto de datos
        $dataSinHash = $data;
        unset($dataSinHash['hash']);
        $processedData = $this->sanitizeData($dataSinHash);
        // Agregar la referencia a la estación (api_id) para relacionar los datos
        $processedData['api_id'] = $api_id;

        $this->processData($processedData);
    }

    /**
     * Consulta la tabla "api" para obtener el ID asociado al hash recibido.
     */
    private function getApiId($hash) {
        $sql = "SELECT id FROM api WHERE hash = :hash LIMIT 1";
        $stmt = $this->db->prepare($sql);
        $stmt->execute([':hash' => $hash]);
        $result = $stmt->fetch(PDO::FETCH_ASSOC);
        if ($result && isset($result['id'])) {
            return $result['id'];
        }
        return false;
    }

    /**
     * Procesa los datos: intenta guardarlos directamente o en cola en función de la conectividad.
     */
    private function processData($data) {
        try {
            if ($this->isConnected()) {
                $this->saveToDatabase($data);
                $this->processQueue();
                $this->sendResponse(200, ['message' => 'Datos guardados']);
            } else {
                $this->queueData($data);
                $this->sendResponse(200, ['message' => 'Datos en cola']);
            }
        } catch(Exception $e) {
            $this->sendResponse(500, ['error' => $e->getMessage()]);
        }
    }

    /**
     * Sanitiza y prepara los datos recibidos.
     */
    private function sanitizeData($data) {
        return [
            'windDirectionADC'      => isset($data['windDirectionADC']) ? (int)$data['windDirectionADC'] : 0,
            'windDirectionGradient' => isset($data['windDirectionGradient']) ? (float)$data['windDirectionGradient'] : 0.0,
            'humidity'              => isset($data['humidity']) ? max(0, min(100, (float)$data['humidity'])) : 0.0,
            'temperatureC'          => isset($data['temperatureC']) ? (float)$data['temperatureC'] : 0.0,
            'windSpeedAvg'          => isset($data['windSpeedAvg']) ? (float)$data['windSpeedAvg'] : 0.0,
            'timestamp'             => date('Y-m-d H:i:s')
        ];
    }

    /**
     * Inserta los datos sanitizados en la tabla sensor_data.
     */
    private function saveToDatabase($data) {
        $columns = implode(', ', array_keys($data));
        $placeholders = ':' . implode(', :', array_keys($data));
        
        $sql = "INSERT INTO {$this->dataTable} ($columns) VALUES ($placeholders)";
        $stmt = $this->db->prepare($sql);
        $stmt->execute($data);
    }

    /**
     * Inserta los datos en cola en la tabla sensor_queue.
     */
    private function queueData($data) {
        $sql = "INSERT INTO {$this->queueTable} (data, created_at) VALUES (:data, NOW())";
        $stmt = $this->db->prepare($sql);
        $stmt->execute([':data' => json_encode($data)]);
    }

    /**
     * Procesa la cola de datos pendientes e inserta cada registro en la tabla sensor_data.
     */
    private function processQueue() {
        $stmt = $this->db->query("SELECT * FROM {$this->queueTable}");
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $data = json_decode($row['data'], true);
            $this->saveToDatabase($data);
            $this->db->exec("DELETE FROM {$this->queueTable} WHERE id = {$row['id']}");
        }
    }

    /**
     * Verifica que la conexión a la base de datos esté activa.
     */
    private function isConnected() {
        try {
            $this->db->query("SELECT 1");
            return true;
        } catch (PDOException $e) {
            return false;
        }
    }

    /**
     * Envía la respuesta HTTP con el código y mensaje correspondiente.
     */
    private function sendResponse($code, $data) {
        http_response_code($code);
        echo json_encode($data);
        exit;
    }
}

$api = new SensorAPI();
$api->handleRequest();
