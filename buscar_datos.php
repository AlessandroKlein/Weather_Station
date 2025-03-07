<?php
session_start();
include 'db.php';
if (!isset($_SESSION['usuario_id'])) {
    header("Location: login.php");
    exit;
}

// Obtener el hash ya sea por GET o POST
$hash = null;
if (isset($_GET['hash']) && !empty($_GET['hash'])) {
    $hash = $conn->real_escape_string($_GET['hash']);
} elseif ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['hash']) && !empty($_POST['hash'])) {
    $hash = $conn->real_escape_string($_POST['hash']);
}

if (!$hash) {
    // Si no se envía hash, mostrar formulario para ingresarlo manualmente
    ?>
    <!DOCTYPE html>
    <html lang="es">
    <head>
        <meta charset="UTF-8">
        <title>Buscar Datos de Sensores</title>
    </head>
    <body>
        <h2>Buscar Datos de Sensores por Hash</h2>
        <form method="post" action="buscar_datos.php">
            <label>Hash de la Estación:</label>
            <input type="text" name="hash" required><br>
            <input type="submit" value="Buscar">
        </form>
        <p><a href="dashboard.php">Volver al Dashboard</a></p>
    </body>
    </html>
    <?php
    exit;
}

// Verificar que el hash corresponda a una estación perteneciente al usuario
$sqlApi = "SELECT id FROM api WHERE hash = '$hash' AND usuario_id = '".$_SESSION['usuario_id']."' LIMIT 1";
$resultApi = $conn->query($sqlApi);
if ($resultApi->num_rows == 1) {
    $apiData = $resultApi->fetch_assoc();
    $api_id = $apiData['id'];

    // Consultar los datos en sensor_data para la estación
    $sqlData = "SELECT * FROM sensor_data WHERE api_id = '$api_id' ORDER BY timestamp DESC";
    $resultData = $conn->query($sqlData);
    ?>
    <!DOCTYPE html>
    <html lang="es">
    <head>
        <meta charset="UTF-8">
        <title>Datos de Sensores</title>
        <style>
            /*table {
                border-collapse: collapse;
                width: 100%;
                margin-top: 20px;
            }*/
            th, td {
                border: 1px solid #cccccc;
                padding: 10px;
                text-align: left;
            }
            th {
                background-color: #f2f2f2;
            }
            table {
                font-size: 12px; /* Ajusta el tamaño de la fuente */
                width: 100%; /* Asegura que la tabla ocupe todo el ancho disponible */
                border-collapse: collapse; /* Colapsa los bordes de las celdas */
            }

            th, td {
                padding: 5px; /* Reduce el padding */
                border: 1px solid #ddd; /* Añade bordes para mejor legibilidad */
                white-space: nowrap; /* Evita que el texto se envuelva */
            }
            .responsive {
                display: table-cell; /* Mostrar por defecto */
            }

            @media screen and (max-width: 768px) {
                .responsive {
                    display: none; /* Ocultar en pantallas pequeñas */
                }
            }
        </style>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
    </head>
    <body>
        <h2>Datos de Sensores</h2>
        <div style="overflow-x: auto;">
            <?php
            if ($resultData->num_rows > 0) {
                echo "<table>
                        <tr>
                            <th>windDirectionADC</th>
                            <th>windDirectionGradient</th>
                            <th>rainTicks24h</th>
                            <th>rainTicks60m</th>
                            <th>temperatureC</th>
                            <th>temperatureAHT</th>
                            <th>temperatureBMP</th>
                            <th>windSpeed</th>
                            <th>windSpeedMax</th>
                            <th>barometricPressure</th>
                            <th>humidity</th>
                            <th>UVIndex</th>
                            <th>lux</th>
                            <th>co2</th>
                            <th>tvoc</th>
                            <th>heatIndex</th>
                            <th>windChill</th>
                            <th>dewPoint</th>
                            <th>aqi</th>
                            <th>et0</th>
                            <th>altitude</th>
                            <th>cloudIndex</th>
                            <th>windSpeedAvg</th>
                            <th>timestamp</th>
                        </tr>";
                while ($row = $resultData->fetch_assoc()) {
                    echo "<tr>";
                        echo "<td>".$row['windDirectionADC']."</td>";
                        echo "<td>".$row['windDirectionGradient']."</td>";
                        echo "<td>".$row['rainTicks24h']."</td>";
                        echo "<td>".$row['rainTicks60m']."</td>";
                        echo "<td>".$row['temperatureC']."</td>";
                        echo "<td>".$row['temperatureAHT']."</td>";
                        echo "<td>".$row['temperatureBMP']."</td>";
                        echo "<td>".$row['windSpeed']."</td>";
                        echo "<td>".$row['windSpeedMax']."</td>";
                        echo "<td>".$row['barometricPressure']."</td>";
                        echo "<td>".$row['humidity']."</td>";
                        echo "<td>".$row['UVIndex']."</td>";
                        echo "<td>".$row['lux']."</td>";
                        echo "<td>".$row['co2']."</td>";
                        echo "<td>".$row['tvoc']."</td>";
                        echo "<td>".$row['heatIndex']."</td>";
                        echo "<td>".$row['windChill']."</td>";
                        echo "<td>".$row['dewPoint']."</td>";
                        echo "<td>".$row['aqi']."</td>";
                        echo "<td>".$row['et0']."</td>";
                        echo "<td>".$row['altitude']."</td>";
                        echo "<td>".$row['cloudIndex']."</td>";
                        echo "<td>".$row['windSpeedAvg']."</td>";
                        echo "<td>".$row['timestamp']."</td>";
                    echo "</tr>";
                }
                echo "</table>";
            } else {
                echo "<p>No se encontraron datos para esta estación.</p>";
            }
            ?>
        </div>
        <p><a href="dashboard.php">Volver al Dashboard</a></p>
    </body>
    </html>
    <?php
} else {
    echo "Hash no válido o no pertenece a este usuario.";
}
?>
