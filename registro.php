<?php
// registro.php
include 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $conn->real_escape_string($_POST['username']);
    $email = $conn->real_escape_string($_POST['email']);
    $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
    // Por simplicidad se asigna un plan por defecto (por ejemplo, 1 para plan básico)
    $plan = 1;

    $sql = "INSERT INTO usuarios (username, email, password, plan) VALUES ('$username', '$email', '$password', '$plan')";

    if ($conn->query($sql) === TRUE) {
        echo "Usuario registrado con éxito.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registro de Usuario</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
</head>
<body>
    <h2>Registro de Usuario</h2>
    <form method="post" action="registro.php">
        <label>Nombre de Usuario:</label>
        <input type="text" name="username" required><br>
        <label>Email:</label>
        <input type="email" name="email" required><br>
        <label>Contraseña:</label>
        <input type="password" name="password" required><br>
        <input type="submit" value="Registrar">
    </form>
    <p>¿Ya tienes cuenta? <a href="login.php">Inicia Sesión</a></p>
</body>
</html>
<?php
// registro.php
include 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $conn->real_escape_string($_POST['username']);
    $email = $conn->real_escape_string($_POST['email']);
    $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
    // Por simplicidad se asigna un plan por defecto (por ejemplo, 1 para plan básico)
    $plan = 1;

    $sql = "INSERT INTO usuarios (username, email, password, plan) VALUES ('$username', '$email', '$password', '$plan')";

    if ($conn->query($sql) === TRUE) {
        echo "Usuario registrado con éxito.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registro de Usuario</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
</head>
<body>
    <h2>Registro de Usuario</h2>
    <form method="post" action="registro.php">
        <label>Nombre de Usuario:</label>
        <input type="text" name="username" required><br>
        <label>Email:</label>
        <input type="email" name="email" required><br>
        <label>Contraseña:</label>
        <input type="password" name="password" required><br>
        <input type="submit" value="Registrar">
    </form>
    <p>¿Ya tienes cuenta? <a href="login.php">Inicia Sesión</a></p>
</body>
</html>
