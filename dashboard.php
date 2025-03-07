<?php
// dashboard.php
session_start();

if (!isset($_SESSION['usuario_id'])) {
    header("Location: login.php");
    exit;
}

// Verificar expiración de sesión
if (isset($_SESSION['expire']) && time() > $_SESSION['expire']) {
    session_unset();
    session_destroy();
    header("Location: login.php?expired=1"); // Redirige al login con un mensaje de expiración
    exit;
}

// Actualizar el tiempo de expiración si la sesión no se mantiene
if (isset($_SESSION['expire'])) {
    $_SESSION['expire'] = time() + (5 * 60); // Restablece el tiempo de expiración
}

// Conexión a la base de datos (asegúrate de que $conn esté definido)
// Ejemplo de conexión:
// $conn = new mysqli("localhost", "usuario", "contraseña", "basededatos");
// if ($conn->connect_error) {
//     die("Conexión fallida: " . $conn->connect_error);
// }
include 'db.php';
$usuario_id = $_SESSION['usuario_id'];

// Consultar las estaciones (tabla "api") asociadas al usuario actual
$sql = "SELECT * FROM api WHERE usuario_id = '$usuario_id'";
$result = $conn->query($sql);

?>

<!DOCTYPE html>
<html lang="es">
<head>
    <?php include './nav/head.php'; ?>
</head>
<body>
    <?php include './nav/nav.php'; ?>

    <div class="yeo-do" id="we-do">
        <h2>Bienvenido, <?php echo $_SESSION['username']; ?></h2>

        <div class="column col-12">
            
        </div>


        <div class="yeo-open-source">
            <div class="container yeo-body">
                <div class="columns">
                    <div class="column col-12">
                        <h2 class="feature-title"></h2>
                    </div>
                    <div class="column col-10 centered col-sm-12">
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
                    </div>
                </div>
            </div>
        </div>

    </div>

    <footer>
        <?php include './nav/footer.php'; ?>
    </footer>
</body>
<script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.3/dist/umd/popper.min.js"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</html>