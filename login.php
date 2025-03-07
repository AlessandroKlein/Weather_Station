<?php
session_start();
include 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $conn->real_escape_string($_POST['username']);
    $password = $_POST['password'];
    $remember = isset($_POST['remember']); // Verifica si la casilla "mantener sesión" está marcada

    $sql = "SELECT * FROM usuarios WHERE username = '$username' LIMIT 1";
    $result = $conn->query($sql);

    if ($result->num_rows == 1) {
        $user = $result->fetch_assoc();
        if (password_verify($password, $user['password'])) {
            $_SESSION['usuario_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];

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
                    $country_code = $api_result['location']['country_code'];
                    $city = $api_result['location']['city'];
                    $state = $api_result['location']['state'];
                    $localtime = date('Y-m-d H:i:s', strtotime($api_result['location']['localtime'])); //formato correcto para mysql
                    //$risk = $api_result['risk']['risk_score'];
                    $risk = json_encode($api_result['risk']);

                    // Guardar la información en la base de datos
                    $sql = "UPDATE `usuarios` SET `ip` = ?, `country` = ?, `country_code` = ?, `city` = ?, `state` = ?, `localtime` = ?, `risk` = ? WHERE `id` = ?";
                    $stmt = $conn->prepare($sql);
                    $stmt->bind_param("ssssssii", $ip, $country, $country_code, $city, $state, $localtime, $risk, $_SESSION['usuario_id']);
                    $stmt->execute();
                    $stmt->close();
                } else {
                    // Manejar el error si la API no devuelve datos válidos
                    error_log("Error al obtener información de la API para la IP: " . $ip);
                }
            } else {
                error_log("Error al obtener datos de la API para la IP: " . $ip);
            }

            if ($remember) {
                // Crear cookie para mantener la sesión
                $cookie_value = $user['id'] . '|' . hash('sha256', $user['password']); // Almacena ID y hash de la contraseña
                setcookie('remember_me', $cookie_value, time() + (86400 * 30), "/"); // 30 días de duración
            } else {
                // Establecer tiempo de expiración de la sesión a 5 minutos
                $_SESSION['expire'] = time() + (5 * 60); // 5 minutos
            }

            header("Location: dashboard.php");
            exit;
        } else {
            echo "Contraseña incorrecta.";
        }
    } else {
        echo "Usuario no encontrado.";
    }
}

// Verificar si hay una cookie de "remember_me"
if (isset($_COOKIE['remember_me']) && !isset($_SESSION['usuario_id'])) {
    $cookie_data = explode('|', $_COOKIE['remember_me']);
    $user_id = $cookie_data[0];
    $password_hash = $cookie_data[1];

    $sql = "SELECT * FROM usuarios WHERE id = $user_id LIMIT 1";
    $result = $conn->query($sql);

    if ($result->num_rows == 1) {
        $user = $result->fetch_assoc();
        if (hash('sha256', $user['password']) === $password_hash) {
            $_SESSION['usuario_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];
            header("Location: ./dashboard");
            exit;
        }
    }
}

// Verificar expiración de sesión
if (isset($_SESSION['expire']) && time() > $_SESSION['expire']) {
    session_unset();
    session_destroy();
    echo "Sesión expirada.";
}
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Inicio de Sesión</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
</head>
<body>
    <h2>Inicio de Sesión</h2>
    <form method="post" action="login.php">
        <label>Nombre de Usuario:</label>
        <input type="text" name="username" required><br>
        <label>Contraseña:</label>
        <input type="password" name="password" required><br>
        <label>Mantener sesión:</label>
        <input type="checkbox" name="remember"><br>
        <input type="submit" value="Iniciar Sesión">
    </form>
    <p>¿No tienes cuenta? <a href="registro.php">Regístrate aquí</a></p>
</body>
</html>