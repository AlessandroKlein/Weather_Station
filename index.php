<?php
// dashboard.php
session_start();

// Obtener la página actual
$currentPage = $_SERVER['REQUEST_URI'];
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta name="generator" content="Hugo 0.48" />
    <meta charset="utf-8">
    <meta name="robots" content="index, follow">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title>Datos del Sensor</title>
    <meta name="keywords" content="yeo">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <link href="https://fonts.googleapis.com/css?family=Poppins:200,400,700" rel="stylesheet">
    <link rel="stylesheet" href="./front/css/spectre.css">
    <link rel="stylesheet" href="./front/css/spectre-icons.css">
    <link rel="stylesheet" href="./front/css/spectre-exp.css">
    <link rel="stylesheet" href="./front/css/yeo.css">
    <meta property="og:title" content="">
    <meta property="og:url" content="">
    <meta property="og:description" content="">
    <meta property="og:site_name" content="">
    <meta property="og:type" content="product">
    <meta property="og:image" content="">
</head>
<body>
    <div class="yeo-slogan">
            <div class="container yeo-header">
                <div class="columns">
                    <div class="column col-12">
                        <header class="navbar">
                            <section class="navbar-section">
                                <a class="navbar-brand logo" href="./">
                                    <img class="logo-img"
                                        src="./front/images/logo.svg" alt><span>Dev
                                        Space</span>
                                </a>
                            </section>
                            <section class="navbar-section hide-sm">
                                <a class="btn btn-link" href="#we-do">What we
                                    do</a>
                                <a class="btn btn-link" href="#we-work">How we
                                    work</a>
                                <a class="btn btn-link"
                                    href="#price">Pricing</a>
                                <a class="btn btn-link" href="#team">Our
                                    Team</a>
                                <a class="btn btn-primary btn-hire-me"
                                    href="#">Download</a>
                            </section>
                        </header>
                    </div>
                </div>
            </div>
            <div class="container slogan">
                <div class="columns">
                    <div class="column col-7 col-sm-12">
                        <div class="slogan-content">
                            <h1>
                                <span class="slogan-bold">Design UI</span>
                                <span class="slogan-bold">App Development</span>
                                <span class="slogan-bold">Consultant
                                    Services</span>
                            </h1>
                            <p>Lorem ipsum dolor sit amet, consectetur
                                adipiscing elit, sed do eiusmod tempor
                                incididunt ut labore et dolore magna aliqua.</p>
                            <a class="btn btn-primary btn-lg btn-start"
                                target="_blank" href="#y">Start a project
                                today</a>

                        </div>
                    </div>
                    <div class="column col-5 hide-sm">
                        <img class="slogan-img" src="./images/yeo-feature-1.svg"
                            alt>
                    </div>
                </div>
            </div>
        </div>

    <div class="yeo-do" id="we-do">
            <div class="container yeo-body">
                <div class="columns">
                    <div class="column col-12">
                        <h2 class="feature-title">What We Do</h2>
                    </div>
                    <div class="column col-4 col-sm-12">
                        <div class="yeo-do-content">
                            <img src="./images/what-we-do-1.svg" alt>
                            <h3>Interface Design</h3>
                            <p>Excepteur sint occaecat cupidatat non proident,
                                sunt in culpa qui officia deserunt mollit anim
                                id est laborum</p>
                            <a href>Learn more</a>
                        </div>
                    </div>
                    <div class="column col-4 col-sm-12">
                        <div class="yeo-do-content">
                            <img src="./images/what-we-do-2.svg" alt>
                            <h3>Web Application</h3>
                            <p>Neque porro quisquam est, qui dolorem ipsum quia
                                dolor sit amet, consectetur, adipisci velit</p>
                            <a href>Learn more</a>
                        </div>
                    </div>
                    <div class="column col-4 col-sm-12">
                        <div class="yeo-do-content">
                            <img src="./images/what-we-do-3.svg" alt>
                            <h3>Software Development</h3>
                            <p>Quis autem vel eum iure reprehenderit qui in ea
                                voluptate velit esse quam nihil molestiae
                                consequatur</p>
                            <a href>Learn more</a>
                        </div>
                    </div>
                </div>
            </div>
        </div>

    <div class="container">
        <div class="columns">
            <div class="column col-12">
                <h1 class="feature-title">Datos del Sensor:</h1>
                <div class="panel">
                    <div id="sensorData"></div>
                </div>
            </div>
        </div>
    </div>


    <div class="yeo-open-source">
            <div class="container yeo-body">
                <div class="columns">
                    <div class="column col-12">
                        <h2 class="feature-title">We love Open Source</h2>
                    </div>
                    <div class="column col-10 centered col-sm-12">
                        <img class="open-source-img"
                            src="./images/open-source.svg" alt>
                        <h2 class="open-source-feature">
                            We're making
                            <br />
                            Open Source Software
                        </h2>
                        <a href="#" class="btn btn-lg btn-open-source">Follow us
                            on Github</a>
                    </div>
                </div>
            </div>
    </div>

    <script>
        function actualizarDatos() {
            // Reemplaza 'TU_HASH_AQUI' con el hash del usuario
            const hash = '29eb0850f30654d5faf6ab7c856c8e975396c75ef8ab726640b0bce99b25d6bf';

            $.ajax({
                url: 'datos/obtener_datos.php?hash=' + hash, // Envía el hash como parámetro
                dataType: 'json',
                success: function(data) {
                    if (data.error) {
                        $('#sensorData').html('<p>' + data.error + '</p>'); // Muestra el error
                    } else {
                        let html = '<ul>';
                        for (let key in data) {
                            html += '<li><b>' + key + ':</b> ' + data[key] + '</li>';
                        }
                        html += '</ul>';
                        $('#sensorData').html(html);
                    }
                },
                error: function() {
                    $('#sensorData').html('<p>Error al obtener los datos.</p>');
                }
            });
        }

        actualizarDatos();
        setInterval(actualizarDatos, 120000); // Actualiza cada 2 minutos
    </script>

    <?php include './nav/footer.php'; ?>
</body>
</html>