<?php
// listar_estaciones.php
session_start();
if (!isset($_SESSION['usuario_id'])) {
    // Redirecciona a la página de login si el usuario no está autenticado
    header("Location: login.php");
    exit;
}

include 'db.php';
$usuario_id = $_SESSION['usuario_id'];

// Consultar las estaciones (tabla "api") asociadas al usuario actual
$sql = "SELECT * FROM api WHERE usuario_id = '$usuario_id'";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Listado de Estaciones Meteorológicas</title>
    <style>
        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 20px;
        }
        th, td {
            border: 1px solid #cccccc;
            padding: 10px;
            text-align: left;
        }
        th {
            background-color: #f2f2f2;
        }
        .btn {
            background-color: #4CAF50;
            color: white;
            padding: 8px 12px;
            text-decoration: none;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .btn:hover {
            background-color: #45a049;
        }
        
    </style>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
</head>
<body>
    <h2>Listado de Estaciones Meteorológicas</h2>
    <table>
        <tr>
            <th>Nombre de la Estación</th>
            <th>Hash</th>
            <th>Acción</th>
        </tr>
        <?php
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                // Se muestran el nombre de la estación y el hash; se utiliza htmlspecialchars para evitar inyección de código
                echo "<td>" . htmlspecialchars($row['estacion']) . "</td>";
                echo "<td>" . htmlspecialchars($row['hash']) . "</td>";
                // Botón que redirige a buscar_datos.php con el hash como parámetro GET
                echo "<td><a class='btn' href='buscar_datos.php?hash=" . urlencode($row['hash']) . "'>Ver Datos</a></td>";
                echo "</tr>";
            }
        } else {
            echo "<tr><td colspan='3'>No se encontraron estaciones registradas.</td></tr>";
        }
        ?>
    </table>
    <p><a href="dashboard.php">Volver al Dashboard</a></p>
</body>
</html>
