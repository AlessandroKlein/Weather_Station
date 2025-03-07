<?php
include '../db.php';

if (isset($_GET['hash'])) {
    $hash = $_GET['hash'];

    $sql_api = "SELECT id FROM api WHERE hash = '$hash'";
    $result_api = $conn->query($sql_api);

    if ($result_api->num_rows > 0) {
        $row_api = $result_api->fetch_assoc();
        $api_id = $row_api['id'];

        $sql_sensor = "SELECT * FROM sensor_data WHERE api_id = $api_id ORDER BY timestamp DESC LIMIT 1";
        $result_sensor = $conn->query($sql_sensor);

        if ($result_sensor->num_rows > 0) {
            $row_sensor = $result_sensor->fetch_assoc();

            // Eliminar los campos que no deseas mostrar
            unset($row_sensor['id']);
            unset($row_sensor['api_id']);
            unset($row_sensor['windDirectionADC']);

            echo json_encode($row_sensor);
        } else {
            echo "{}";
        }
    } else {
        echo "{\"error\": \"Hash inválido\"}";
    }
} else {
    echo "{\"error\": \"Hash no proporcionado\"}";
}

$conn->close();
?>