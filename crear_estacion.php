<?php
// crear_estacion.php
session_start();
include 'db.php';
if (!isset($_SESSION['usuario_id'])) {
    header("Location: login.php");
    exit;
}

$usuario_id = $_SESSION['usuario_id'];

// Obtener información del usuario para conocer su plan
$sqlUser = "SELECT * FROM usuarios WHERE id = '$usuario_id' LIMIT 1";
$resultUser = $conn->query($sqlUser);
$user = $resultUser->fetch_assoc();

// Definir límites según el plan
$maxEstaciones = 3; // Valor por defecto para plan 1
if ($user['plan'] == 2) {
    $maxEstaciones = 10;
}
// Puedes agregar más condiciones según otros planes

// Contar estaciones existentes para el usuario
$sqlCount = "SELECT COUNT(*) as total FROM api WHERE usuario_id = '$usuario_id'";
$resultCount = $conn->query($sqlCount);
$countData = $resultCount->fetch_assoc();
$totalEstaciones = $countData['total'];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if ($totalEstaciones >= $maxEstaciones) {
        echo "Has alcanzado el límite de estaciones para tu plan.";
    } else {
        $estacion = $conn->real_escape_string($_POST['estacion']);
        // Generar hash único para la estación
        $hash = hash('sha256', uniqid(rand(), true));

        // Obtener la dirección IP del usuario
        $ip = $_SERVER['REMOTE_ADDR'];

        // Obtener la información de la API
        $api_url = "https://api.ipquery.io/" . $ip;
        $api_data = @file_get_contents($api_url); // Usamos @ para suprimir errores si la API falla
        if ($api_data) {
            $api_result = json_decode($api_data, true);

            // Verificar si la API devolvió datos válidos
            if ($api_result && isset($api_result['ip'])) {
                // Extraer la información relevante
                $country = $api_result['location']['country'];
                $city = $api_result['location']['city'];
                $state = $api_result['location']['state'];

                $sqlInsert = "INSERT INTO api (hash, usuario_id, estacion, country, city, state) VALUES (?, ?, ?, ?, ?, ?)";
                $stmt = $conn->prepare($sqlInsert);
                $stmt->bind_param("sissis", $hash, $usuario_id, $estacion, $country, $city, $state);

                if ($stmt->execute()) {
                    echo "Estación creada exitosamente. El hash de la estación es: <strong>$hash</strong>";
                } else {
                    echo "Error: " . $stmt->error;
                }
                $stmt->close();

            } else {
                // Manejar el error si la API no devuelve datos válidos
                error_log("Error al obtener información de la API para la IP: " . $ip);
                echo "Error al obtener la informacion de ubicacion";
            }
        } else {
            error_log("Error al obtener datos de la API para la IP: " . $ip);
            echo "Error al obtener la informacion de ubicacion";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Crear Estación Meteorológica</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
</head>
<body>
    <h2>Crear Estación Meteorológica</h2>
    <p>Estaciones creadas: <?php echo $totalEstaciones; ?> / <?php echo $maxEstaciones; ?></p>
    <form method="post" action="crear_estacion.php">
        <label>Nombre de la Estación:</label>
        <input type="text" name="estacion" required><br>
        <input type="submit" value="Crear Estación">
    </form>
    <p><a href="dashboard.php">Volver al Dashboard</a></p>
</body>
</html>