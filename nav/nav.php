<?php
// dashboard.php
session_start();

// Obtener la página actual
$currentPage = $_SERVER['REQUEST_URI'];
?>



<div class="yeo-slogan">
<div class="container yeo-header">
                <div class="columns">
                    <div class="column col-12">
                        <header class="navbar">
                            <section class="navbar-section">
                                <a class="navbar-brand logo" href="./">
                                    <img class="logo-img"
                                        src="./images/logo.svg" alt><span>Dev
                                        Space</span>
                                </a>
                            </section>
                            <section class="navbar-section hide-sm">
                                <a class="btn btn-link" href="#we-do">Inicio</a>
                                <?php if (isset($_SESSION['usuario_id'])) { ?>
                                <a class="btn btn-link"
                                    href="/buscar_datos">Buscar Estacion</a>
                                <a class="btn btn-link"
                                    href="/crear_estacion">Crear Nueva Estacion</a>
                                <a class="btn btn-link" href="/logout">Cerrar Sesión</a>
                                <?php } else { ?>
                                    <a class="btn btn-primary btn-hire-me"
                                        href="/login">Iniciar Sesión</a>
                                <?php } ?>
                            </section>
                        </header>
                    </div>
                </div>
            </div>
</div>