#ifndef STYLE_H
#define STYLE_H

const char* css = R"(
@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;500;600;700&display=swap');

* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    font-family: 'Poppins', sans-serif;
    list-style: none;
}

body {
    background-color: #222831;

    /*font-family: Arial, sans-serif;
    text-transform: capitalize;
    margin: 0;
    padding: 0;*/

    display: flex;
    flex-direction: column;
    min-height: 100vh;
    font-size: 16px;
    line-height: 1.6;
}

.sidebar {
    position: fixed;
    top: 0;
    left: 0;
    height: 100%;
    width: 350px;
    background: #11101d;
    z-index: 100;
    transition: all 0.5s ease;
}

.sidebar.close {
    width: 78px;
    background-color: #11101d;
}

.sidebar .logo-details {
    height: 60px;
    width: 100%;
    display: flex;
    align-items: center;
}

.sidebar .logo-details i {
    font-size: 30px;
    color: #fff;
    height: 50px;
    min-width: 78px;
    text-align: center;
    line-height: 50px;
}

.sidebar .logo-details .logo_name {
    font-size: 22px;
    color: #fff;
    font-weight: 600;
    transition: 0.3s ease;
    transition-delay: 0.1s;
}

.sidebar.close .logo-details .logo_name {
    transition-delay: 0s;
    opacity: 0;
    pointer-events: none;
}

.sidebar .nav-links {
    height: 100%;
    padding: 30px 0 150px 0;
    overflow: auto;
}

.sidebar.close .nav-links {
    overflow: visible;
}

.sidebar .nav-links::-webkit-scrollbar {
    display: none;
}

.sidebar .nav-links li {
    position: relative;
    list-style: none;
    transition: all 0.4s ease;
}

.sidebar .nav-links li:hover {
    background: #1d1b31;
}

.sidebar .nav-links li .iocn-link {
    display: flex;
    align-items: center;
    justify-content: space-between;
}

.sidebar.close .nav-links li .iocn-link {
    display: block
}

.sidebar .nav-links li i {
    height: 50px;
    min-width: 78px;
    text-align: center;
    line-height: 50px;
    color: #fff;
    font-size: 20px;
    cursor: pointer;
    transition: all 0.3s ease;
}

.sidebar .nav-links li.showMenu i.arrow {
    transform: rotate(-180deg);
}

.sidebar.close .nav-links i.arrow {
    display: none;
}

.sidebar .nav-links li a {
    display: flex;
    align-items: center;
    text-decoration: none;
}

.sidebar .nav-links li a .link_name {
    font-size: 18px;
    font-weight: 400;
    color: #fff;
    transition: all 0.4s ease;
}

.sidebar.close .nav-links li a .link_name {
    opacity: 0;
    pointer-events: none;
}

.sidebar .nav-links li .sub-menu {
    padding: 6px 6px 14px 80px;
    background: #1d1b31;
    /*margin-top: -10px;
    display: none;*/
}

.sidebar .nav-links li.showMenu .sub-menu {
    display: block;
}

.sidebar .nav-links li .sub-menu a {
    color: #fff;
    font-size: 15px;
    padding: 5px 0;
    white-space: nowrap;
    opacity: 0.6;
    transition: all 0.3s ease;
}

.sidebar .nav-links li .sub-menu a:hover {
    opacity: 1;
}

.sidebar.close .nav-links li .sub-menu {
    position: absolute;
    left: 100%;
    top: -10px;
    margin-top: 0;
    padding: 10px 20px;
    border-radius: 0 6px 6px 0;
    opacity: 0;
    display: block;
    pointer-events: none;
    transition: 0s;
}

.sidebar.close .nav-links li:hover .sub-menu {
    top: 0;
    opacity: 1;
    pointer-events: auto;
    transition: all 0.4s ease;
}

.sidebar .nav-links li .sub-menu .link_name {
    display: none;
}

.sidebar.close .nav-links li .sub-menu .link_name {
    font-size: 18px;
    opacity: 1;
    display: block;
}

.sidebar .nav-links li .sub-menu.blank {
    opacity: 1;
    pointer-events: auto;
    padding: 3px 20px 6px 16px;
    opacity: 0;
    pointer-events: none;
}

.sidebar .nav-links li:hover .sub-menu.blank {
    top: 50%;
    transform: translateY(-50%);
}

/*.sidebar .profile-details {
    position: fixed;
    bottom: 0;
    width: 350px;
    min-width: 300px;
    display: flex;
    align-items: center;
    justify-content: space-between;
    background: #1d1b31;
    padding: 12px 0;
    transition: all 0.5s ease;
}*/

.sidebar .profile-details {
    position: fixed;
    bottom: 0;
    width: 100%; /* Cambié a 100% para hacerla más adaptable */
    max-width: 350px; /* Para limitar su ancho máximo */
    min-width: 300px; /* Para establecer un mínimo ancho cuando se achique la ventana */
    display: flex;
    align-items: center;
    justify-content: space-between;
    background: #1d1b31;
    padding: 12px 0;
    transition: all 0.5s ease;
}

.sidebar.close .profile-details {
    background: none;
}

.sidebar.close .profile-details {
    width: 78px;
}

.sidebar .profile-details .profile-content {
    display: flex;
    align-items: center;
}

.sidebar .profile-details img {
    height: 52px;
    width: 52px;
    object-fit: cover;
    border-radius: 16px;
    margin: 0 14px 0 12px;
    background: #1d1b31;
    transition: all 0.5s ease;
}

.sidebar.close .profile-details img {
    padding: 10px;
}

.sidebar .profile-details .profile_name,
.sidebar .profile-details .job {
    color: #fff;
    font-size: 18px;
    font-weight: 500;
    white-space: nowrap;
}

.sidebar.close .profile-details i,
.sidebar.close .profile-details .profile_name,
.sidebar.close .profile-details .job {
    display: none;
}

.sidebar .profile-details .job {
    font-size: 12px;
}

.sidebar.close .profile-details .name-job {
    text-decoration: none;
    text-align: center;
    block-size: auto;
}

.home-section {
    position: relative;
    background: #222831;
    height: auto;
    left: 350px;
    /* Ajustado para que coincida con el ancho total de la barra lateral expandida */
    /*margin-left: 5px; /* Agregado para asegurar que el contenido quede separado del menú */
    /*width: calc(100% - 350px - 75px); /* Considerando tanto el menú como el margen */
    width: calc(100% - 350px);
    transition: all 0.5s ease;
}

.sidebar.close~.home-section {
    left: 78px;
    /* Ancho de la barra lateral cuando está cerrada */
    /*margin-left: 5px; /* Manteniendo el margen */
    /*width: calc(100% - 78px - 75px); /* Ajustado para el estado cerrado */
    width: calc(100% - 78px);
}

.sidebar.close~.home-section {
    left: 78px;
    width: calc(100% - 78px);
}

.home-section .home-content {
    height: 60px;
    display: flex;
    align-items: center;
    padding: 0 15px;
    /* Espaciado interno opcional */

}

.home-section .home-content .bx-menu,
.home-section .home-content .text {
    color: #fff;
    font-size: 35px;

}

.home-section .home-content .bx-menu {
    margin: 0 20px;
    /* Reduce el margen para acercarlo */
    cursor: pointer;
    transition: all 0.3s ease;
    /* Agrega una transición suave */


}

.sidebar.close~.home-section .home-content .bx-menu {
    margin-left: 10px;
    /* Ajusta la posición del botón */
}

.home-section .home-content .text {
    font-size: 26px;
    font-weight: 600;

}

.cuerpo {
    text-align: center;
    font-size: 18px;
    font-weight: 4000;
    color: #fff;
}

.h1-head {
    color: #fff;
    text-decoration: none;
    padding: 10px;
    font-size: 26px;
}

.h2-head {
    color: #fff;
    text-decoration: none;
    padding: 10px;
    font-size: 20px;
}

:root {
    --button: #b3b3b3;
    --button-color: #0a0a0a;
    --shadow: #000;
    --bg: #737373;
    --header: #7a7a7a;
    --color: #fafafa;
    --lit-header: #e6e6e6;
    --speed: 2s;
}

@property --swing-x {
    initial-value: 0;
    inherits: false;
    syntax: '<integer>';
}

@property --swing-y {
    initial-value: 0;
    inherits: false;
    syntax: '<integer>';
}

.error404 a {
    text-transform: uppercase;
    text-decoration: none;
    background: var(--button);
    color: var(--button-color);
    padding: 1rem 4rem;
    border-radius: 4rem;
    font-size: 0.875rem;
    letter-spacing: 0.05rem;
}

.error404 p {
    font-weight: 100;
}

.error404 h1 {
    --speed: 1s;
    -webkit-animation: swing var(--speed) infinite alternate ease-in-out;
    animation: swing var(--speed) infinite alternate ease-in-out;
    font-size: clamp(5rem, 40vmin, 20rem);
    font-family: 'Open Sans', sans-serif;
    margin: 0;
    margin-bottom: 1rem;
    letter-spacing: 1rem;
    transform: translate3d(0, 0, 0);
    --x: calc(50% + (var(--swing-x) * 0.5) * 1%);
    background: radial-gradient(var(--lit-header), var(--header) 45%) var(--x) 100%/200% 200%;
    -webkit-background-clip: text;
    background-clip: text;
    color: transparent;
}

.error404 h1:after {
    --speed: 1s;
    -webkit-animation: swing var(--speed) infinite alternate ease-in-out;
    animation: swing var(--speed) infinite alternate ease-in-out;
    content: "404";
    position: absolute;
    top: 0;
    left: 0;
    color: var(--shadow);
    filter: blur(1.5vmin);
    transform: scale(1.05) translate3d(0, 12%, -10vmin) translate(calc((var(--swing-x, 0) * 0.05) * 1%), calc((var(--swing-y) * 0.05) * 1%));
}

.error404 .cloak {
    --speed: 1s;
    animation: swing var(--speed) infinite alternate-reverse ease-in-out;
    height: 100%;
    width: 100%;
    transform-origin: 50% 30%;
    transform: rotate(calc(var(--swing-x) * -0.25deg));
    background: radial-gradient(40% 40% at 50% 42%, transparent, #000 35%);
}

.error404 .cloak__wrapper {
    position: fixed;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    overflow: hidden;
}

.error404 .cloak__container {
    height: 250vmax;
    width: 250vmax;
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
}

.error404 info {
    text-align: center;
    line-height: 1.5;
    max-width: clamp(16rem, 90vmin, 25rem);
}

.error404 .info>p {
    margin-bottom: 3rem;
}

@-webkit-keyframes swing {
    0% {
        --swing-x: -100;
        --swing-y: -100;
    }

    50% {
        --swing-y: 0;
    }

    100% {
        --swing-y: -100;
        --swing-x: 100;
    }
}

@keyframes swing {
    0% {
        --swing-x: -100;
        --swing-y: -100;
    }

    50% {
        --swing-y: 0;
    }

    100% {
        --swing-y: -100;
        --swing-x: 100;
    }
}

.variables-editables {
    align-items: center;
    margin: 20px 0;
    text-align: center;
    color: #fff;
}

variables-editables h1 {
    color: #fff;
    text-decoration: none;
    padding: auto;
    font-size: 20px;
}

variables-editables label {
    color: #fff;
    text-decoration: none;
    display: block;
    margin-top: 15px;
    margin-bottom: 10px;
    font-weight: 700;
    text-align: center;
}

input[type=number] {
    padding: 5px;
    border-radius: 5px;
    border: 1px solid #393e46;
    color: #fff;
    text-decoration: none;
    background-color: #393e46;
    margin-bottom: 10px;
    font-size: 16px;
    width: 200px;
    text-align: center;
    display: block;
    margin: auto;
}

.mqtt-class input[type=number] {
    padding: 5px;
    border-radius: 5px;
    border: 1px solid #393e46;
    color: #fff;
    text-decoration: none;
    background-color: #393e46;
    margin-bottom: 10px;
    font-size: 16px;
    width: 400px;
    text-align: center;
    display: block;
    margin: auto;
}

input[type=password],
input[type=text] {
    padding: 5px;
    border-radius: 5px;
    border: 1px solid #393e46;
    color: #fff;
    text-decoration: none;
    background-color: #393e46;
    margin-bottom: 10px;
    font-size: 16px;
    width: 400px;
    text-align: center;
    display: block;
    margin: auto;
}

input[type=submit] {
    background-color: #393e46;
    color: #fff;
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    font-size: 16px;
    margin-top: 10px;
    display: block;
    margin: auto;
}

input[type=submit]:hover {
    background-color: #222831;
}

.botones-class {
    padding: 5px;
    border-radius: 10px;
    margin-bottom: 10px;
    align-items: center;
    text-align: center;
    margin: 20px 0;
    color: #fff;
    margin-top: 15px;
}

botones-class label {
    color: #fff;
    text-decoration: none;
    display: block;
    text-align: center;
}

.tex-class {
    color: #fff;
    margin: 30px 30px 30px 30px;
    font-weight: 700;
    text-align: center;
}

.button-container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 5vh;
}

.botones-class h1:first-child {
    font-size: 35px;
    margin: 0 0 30px 0;
}

.botones-class h1 {
    font-size: 35px;
    margin: 40px 0px 0px 0px;
}

.botones-class h3 {
    font-size: 25px;
    margin: 40px 0px 30px 0px;
}

.botones-class h3:last-child {
    font-size: 25px;
    margin: 40px 0px 30px 0px;
}

.botones-class .elementos-button {
    margin: 50px 0px 30px 0px;
}

.button {
    padding: 10px 20px;
    background-color: #393e46;
    color: #fff;
    margin-top: 20px;
    border: none;
    border-radius: 10px;
    font-size: 16px;
}

button a {
    color: #fff;
    text-decoration: none;
    size: 40px;
    height: 5vh;
}

.container-booton {
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 5vh;
}


.tabla-stilo {
    position: relative;
    margin-top: auto;
    align-items: center;
    justify-content: center;
    text-decoration: none;
    text-align: center;
}

.tabla-stilo h1 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 25px;
    margin: 0 0 30px 0;
}

.tabla-stilo h2 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 20px;
    margin: 40px 0px 0px 0px;
}

.tabla-stilo h3 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 18px;
    margin: 40px 0px 0px 0px;
}

.tabla-stilo label {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 14px;
    margin: 40px 0px 0px 0px;
}

.tabla-stilo table {
    color: #fff;
    margin: 0 auto;
}

.tabla-stilo td {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 18px;
}

.tabla-stilo table {
    border-collapse: separate;
    border-spacing: 50px 20px;
}

.ota-stilo {
    position: relative;
    margin-top: auto;
    align-items: center;
    justify-content: center;
    text-decoration: none;
    text-align: center;
}

.ota-stilo h1 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 25px;
    margin: 0 0 30px 0;
}

.ota-stilo h2 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 20px;
    margin: 40px 0px 20px 0px;
}

.ota-stilo .upload {
    border: 2px solid #393e46;
    padding: 10px;
    border-radius: 5px;
    background-color: #393e46;
    color: #fff;
    font-size: 16px;
}

.pines-stilo {
    position: relative;
    margin-top: auto;
    align-items: center;
    justify-content: center;
    text-decoration: none;
    text-align: center;
}

.pines-stilo h1 {
    color: #fff;
    text-align: center;
    text-decoration: none;
    font-size: 25px;
    margin: 0 0 30px 0;
}

.pines-stilo label {
    color: #fff;
    font-size: 22px;
    text-decoration: none;
    display: block;
    text-align: center;
    margin-top: 30px;
    margin-bottom: 5px;
}

.pines-stilo .selectortext {
    margin-right: 30px;
}

.pines-stilo .selectortextluz {
    margin-right: 100px;
}

.pines-stilo .selector {
    margin-right: 70px;
}

.pines-stilo .dropdown {
    display: inline-block;
    position: relative;
    color: #fff;
}

.pines-stilo .dropdown select {
    width: 200px;
    padding: 5px;
    font-size: 16px;
    color: #fff;
    border: 2px solid #393e46;
    background-color: #393e46;
    border-radius: 5px;
}

.pines-stilo input[type="submit"] {
    margin-top: 30px;
    margin-bottom: 30px;
    padding: 10px 20px;
    font-size: 16px;
}

.container-pines {
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 5vh;
    margin-top: 50px;
    margin-bottom: 60px;
}

.container-pines2 {
    display: flex;
    flex-direction: column-reverse;
    justify-content: center;
    text-align: center;
    align-items: center;
    height: 5vh;
    margin-top: 50px;
    margin-bottom: 60px;
}

.container-pines2:not(:last-child) {
    margin-right: 30px;
}

.volver {
    margin-top: 10px;
    margin-bottom: 10px;
    color: #fff;
    position: relative;
    width: auto;
    justify-content: center;
    align-items: center;
    text-align: center;
}

.volver .boton {
    display: inline-block;
    padding: 8px 16px;
    margin-top: 10px;
    font-size: 16px;
    font-weight: bold;
    text-decoration: none;
    color: #fff;
    background-color: #393e46;
    border-radius: 4px;
    border: none;
    cursor: pointer;
}

footer {
    position: relative;
    width: 100%;
    background-color: #11101d;
    min-height: 100px;
    padding: 20px 50px;
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
    font-family: sans-serif;
    margin-top: auto;
}

footer .social_icon,
footer .menu__footer {
    position: relative;
    display: flex;
    justify-content: center;
    align-items: center;
    margin: 1px 0;
    flex-wrap: wrap;
}

footer .social_icon li,
footer .menu__footer li {
    list-style: none;
}

footer .social_icon li a,
footer .menu__footer li a {
    font-size: 2em;
    color: #fff;
    margin: 0 10px;
    display: inline-block;
    transition: 0.5s;
}

footer .social_icon li a:hover {
    transform: translateY(-10px);
}

footer .menu__footer li a {
    font-size: 1.2em;
    color: #fff;
    margin: 0 10px;
    display: inline-block;
    text-decoration: none;
    opacity: 0.75;
}

footer .menu__footer li a:hover {
    opacity: 1;
}

footer .p-class {
    color: #fff;
    text-align: center;
    margin-top: 15px;
    margin-bottom: 10px;
    font-size: 1.1em;
}

@media (max-width: 400px) {
    .sidebar.close .nav-links li .sub-menu {
        display: none;
    }

    .sidebar {
        width: 78px;
    }

    .sidebar.close {
        width: 0;
    }

    .home-section {
        left: 260px;
        width: calc(100% - 260px);
        transition: all 0.5s ease;
        /* Transición para suavizar el cambio */
    }

    .sidebar.close~.home-section {
        left: 78px;
        width: calc(100% - 78px);
    }
}

/* Dispositivos pequeños (celulares) */
@media screen and (max-width: 768px) {
    .sidebar {
        width: 100%;
        height: auto;
        position: relative;
    }

    .sidebar.close {
        width: 100%;
    }

    .home-section {
        left: 0;
        width: 100%;
    }

    .sidebar .profile-details {
        position: relative;
        flex-direction: column;
    }

    .sidebar .nav-links li {
        text-align: center;
    }

    .sidebar .nav-links li .sub-menu {
        padding: 10px;
        padding: 6px 6px 14px 80px;
    }

    .home-section .home-content {
        flex-direction: column;
        padding: 10px;
    }
}

/* Dispositivos medianos (tabletas) */
@media screen and (max-width: 1024px) {
    .sidebar {
        width: 250px;
    }

    .sidebar.close {
        width: 78px;
    }

    .home-section {
        left: 250px;
        width: calc(100% - 250px);
    }

    .sidebar.close~.home-section {
        left: 78px;
        width: calc(100% - 78px);
    }
}

@media (max-width: 768px) {
    .sidebar .profile-details {
        width: 100%; /* Para pantallas más pequeñas */
        max-width: 100%; /* Asegura que ocupe todo el espacio disponible */
        padding: 8px 0; /* Se puede reducir el padding si es necesario */
    }
}
)";

#endif
