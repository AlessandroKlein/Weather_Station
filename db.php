<?php
// db.php
$servername = "sql205.infinityfree.com";
$username = "if0_38462059";
$password = "75lxZpaZvAsW";
$dbname = "if0_38462059_est";

// Crear conexión
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}
?>
