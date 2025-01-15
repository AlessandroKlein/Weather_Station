//===========================================
//Pagina Inicio
//===========================================

String handleWebPage = R"rawliteral(
<!DOCTYPE html>

<head>
  <meta charset='UTF-8'>
  <title> VentoMeter | Silbito </title>
  <link rel='stylesheet' href='style.css'>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
</head>

<body>
  <div class='sidebar close'>
    <div class='logo-details'>
      <i class='bx bxl-mongodb'></i>
      <span class='logo_name'>VentoMeter</span>
    </div>
    <ul class='nav-links'>
      <li>
        <a href='#'>
          <i class='bx bx-grid-alt'></i>
          <span class='link_name'>Categorias</span>
        </a>
        <ul class='sub-menu blank'>
          <li><a class='link_name' href='#'>Categorias</a></li>
        </ul>
      </li>
      <li>
        <a href='/'>
          <i class='bx bx-home-alt-2'></i>
          <span class='link_name'>Inicio</span>
        </a>
        <ul class='sub-menu blank'>
          <li><a class='link_name' href='/'>Inicio</a></li>
        </ul>
      </li>
      <li>
        <div class='iocn-link'>
        <a href='/config'>
          <i class='bx bx-cog'></i>
          <span class='link_name'>Configuraciones</span>
        </a>
        <ul class='sub-menu blank'>
          <li><a class='link_name' href='/'>Configuraciones</a></li>
        </ul>
        </div>
      </li>
      

      <li>
        <a href='/updateota'>
          <div class='profile-details'>
            <div class='profile-content'>
            </div>
            <div class='name-job'>
              <div class='profile_name'>Actualizar</div>
              <div class='job'>" + String(VERSION) + "</div>
            </div>
            <i class='bx bxs-cloud-upload'></i>
          </div>
        </a>
      </li>

    </ul>
  </div>
  <section class='home-section'>
    <div class='home-content'>
      <i class='bx bx-menu' id='menu-btn'></i>
    </div>
    <header>
    </header>
    <main>
      <div class='cuerpo'>
        <h1 class='h1-head'> Estación Meteorológica </h1>
      </div>
    </main>
    <div class='tabla-stilo'>
      <h2 id='current-time'></h2>
      <h1>Datos</h1>
      <table>
        <tr>
          <td>Temperatura:</td>
          <td id='temperatureC'> (°C)</td>
        </tr>
        <tr>
          <td>Humedad:</td>
          <td id='humidity'> (%)</td>
        </tr>
        <tr>
          <td>Presión barométrica:</td>
          <td id='barometricPressure'> (hPa)</td>
        </tr>
        <tr>
          <td>Índice UV:</td>
          <td id='UVIndex'></td>
        </tr>
        <tr>
          <td>Luz:</td>
          <td id='lux'> (lux)</td>
        </tr>
        <tr>
          <td>CO2:</td>
          <td id='c02'> (ppm)</td>
        </tr>
        <tr>
          <td>TVOC:</td>
          <td id='tvoc'> (ppb)</td>
        </tr>
        <tr>
          <td>Velocidad del viento:</td>
          <td id='windSpeed'> (m/s)</td>
        </tr>
        <tr>
          <td>Velocidad max del viento:</td>
          <td id='windSpeedMax'> (m/s)</td>
        </tr>
        <tr>
          <td>Dirección del viento:</td>
          <td id='windDirectionADC'> (ADC)</td>
        </tr>
        <tr>
          <td>Dirección del viento:</td>
          <td id='windDirectiongradiant'> (°)</td>
        </tr>
        <tr>
          <td>Lluvia acumulada 60 minutos:</td>
          <td id='rainTicks60m'> (mm)</td>
        </tr>
        <tr>
          <td>Lluvia acumulada 24 horas:</td>
          <td id='rainTicks24h'> (mm)</td>
        </tr>
      </table>
    </div>
  </section>
  <footer>
    <ul class='social_icon'>
      <li><a href='#' target='_blank'><i class='bx bxl-instagram'></i></a></li>
      <li><a href='#' target='_blank'><i class='bx bxl-facebook'></i></a></li>
      <li><a href='https://github.com/AlessandroKlein' target='_blank'><i class='bx bxl-github'></i></a>
      </li>
      <li><a href='#'><i class='bx bxl-telegram' target='_blank'></i></a></li>
      <li><a href='#'><i class='bx bxl-discord-alt' target='_blank'></i></a></li>
      <li><a href='https://www.youtube.com/channel/UCEv8bj0D22b9hCfhylVzmoQ'><i class='bx bxl-youtube'
            target='_blank'></i></a></li>
    </ul>
    <ul class='menu__footer'>
      <li><a href='/'>Inicio</a></li>
      <li><a href='#'>Acerca de</a></li>
      <li><a href='#'>Servicios</a></li>
      <li><a href='#'>Team</a></li>
      <li><a href='#'>Contacto</a></li>
    </ul>
    <div class='p-class'>
      <p id='copyright'>&copy; Silbito. Todos los derechos reservados.</p>
    </div>
  </footer>
  <script type='module' src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js'></script>
  <script nomodule src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js'></script>
  <script>
    let arrow = document.querySelectorAll('.arrow'); for (var i = 0; i < arrow.length; i++) { arrow[i].addEventListener('click', (e) => { let arrowParent = e.target.parentElement.parentElement; arrowParent.classList.toggle('showMenu'); }); }
    let sidebar = document.querySelector('.sidebar'); let sidebarBtn = document.querySelector('.bx-menu'); console.log(sidebarBtn); sidebarBtn.addEventListener('click', () => { sidebar.classList.toggle('close'); });
    document.addEventListener('DOMContentLoaded', function () { var currentYear = new Date().getFullYear(); var copyright = document.getElementById('copyright'); copyright.innerHTML = '&copy;' + currentYear + ' Silbito. Todos los derechos reservados.'; });

    setInterval(updateData, 5000);
    function updateData() {
    fetch('/get_data').then(response => response.json()).then(data => {
        document.getElementById('temperatureC').innerHTML = data.temperatureC;
        document.getElementById('humidity').innerHTML = data.humidity;
        document.getElementById('barometricPressure').innerHTML = data.barometricPressure;
        document.getElementById('UVIndex').innerHTML = data.UVIndex;
        document.getElementById('lux').innerHTML = data.lux;
        document.getElementById('c02').innerHTML = data.c02;
        document.getElementById('tvoc').innerHTML = data.tvoc;
        document.getElementById('windSpeed').innerHTML = data.windSpeed;
        document.getElementById('windSpeedMax').innerHTML = data.windSpeedMax;
        document.getElementById('windDirectionADC').innerHTML = data.windDirectionADC;
        document.getElementById('windDirectiongradiant').innerHTML = data.windDirectiongradiant;
        document.getElementById('rainTicks60m').innerHTML = data.rainTicks60m;
        document.getElementById('rainTicks24h').innerHTML = data.rainTicks24h;
      });
    }
  </script>
</body>

</html>
)rawliteral";

//===========================================
//OTA Web
//===========================================
#ifdef OTAWeb
String handleHomePageOTA = R"rawliteral(
<!DOCTYPE html>

<head>
    <meta charset='UTF-8'>
    <title> VentoMeter | Silbito </title>
    <link rel='stylesheet' href='style.css'>
    <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
</head>

<body>
    <div class='sidebar close'>
        <div class='logo-details'>
            <i class='bx bxl-mongodb'></i>
            <span class='logo_name'>VentoMeter</span>
        </div>
        <ul class='nav-links'>
            <li>
                <a href='#'>
                    <i class='bx bx-grid-alt'></i>
                    <span class='link_name'>Categorias</span>
                </a>
                <ul class='sub-menu blank'>
                    <li><a class='link_name' href='#'>Categorias</a></li>
                </ul>
            </li>
            <li>
                <a href='/'>
                    <i class='bx bx-home-alt-2'></i>
                    <span class='link_name'>Inicio</span>
                </a>
                <ul class='sub-menu blank'>
                    <li><a class='link_name' href='/'>Inicio</a></li>
                </ul>
            </li>
            <li>
                <div class='iocn-link'>
                    <a href='/config'>
                        <i class='bx bx-cog'></i>
                        <span class='link_name'>Configuraciones</span>
                    </a>
                    <ul class='sub-menu blank'>
                        <li><a class='link_name' href='/'>Configuraciones</a></li>
                    </ul>
                </div>
            </li>


            <li>
                <a href='/updateota'>
                    <div class='profile-details'>
                        <div class='profile-content'>
                        </div>
                        <div class='name-job'>
                            <div class='profile_name'>Actualizar</div>
                            <div class='job'>" + String(VERSION) + "</div>
                        </div>
                        <i class='bx bxs-cloud-upload'></i>
                    </div>
                </a>
            </li>

        </ul>
    </div>

    <section class='home-section'>
        <div class='home-content'>
            <i class='bx bx-menu'></i>
        </div>
        <header>
        </header>
        <main>
            <div class='cuerpo'>
                <h1 class='h1-head'> Actualizar via OTA </h1>
            </div>
        </main>
        <div class='ota-stilo'>
            <h2>" + String(OTA_ACTUALIZAR_V_A) + " " + String(VERSION) + "</h2>
            <form method='POST' action='/update' enctype='multipart/form-data'>
                <input class='upload' type='file' name='update'>
                <br>
                <br>
                <input type='submit' value='Cargar'>
            </form>
        </div>
    </section>

    <footer>
        <ul class='social_icon'>
            <li><a href='#' target='_blank'><i class='bx bxl-instagram'></i></a></li>
            <li><a href='#' target='_blank'><i class='bx bxl-facebook'></i></a></li>
            <li><a href='https://github.com/AlessandroKlein' target='_blank'><i class='bx bxl-github'></i></a>
            </li>
            <li><a href='#'><i class='bx bxl-telegram' target='_blank'></i></a></li>
            <li><a href='#'><i class='bx bxl-discord-alt' target='_blank'></i></a></li>
            <li><a href='https://www.youtube.com/channel/UCEv8bj0D22b9hCfhylVzmoQ'><i class='bx bxl-youtube'
                        target='_blank'></i></a></li>
        </ul>
        <ul class='menu__footer'>
            <li><a href='/'>Inicio</a></li>
            <li><a href='#'>Acerca de</a></li>
            <li><a href='#'>Servicios</a></li>
            <li><a href='#'>Team</a></li>
            <li><a href='#'>Contacto</a></li>
        </ul>
        <div class='p-class'>
            <p id='copyright'>&copy; Silbito. Todos los derechos reservados.</p>
        </div>
    </footer>
    <script type='module' src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js'></script>
    <script nomodule src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js'></script>
    <script>
        let arrow = document.querySelectorAll('.arrow'); for (var i = 0; i < arrow.length; i++) { arrow[i].addEventListener('click', (e) => { let arrowParent = e.target.parentElement.parentElement; arrowParent.classList.toggle('showMenu'); }); }
        let sidebar = document.querySelector('.sidebar'); let sidebarBtn = document.querySelector('.bx-menu'); console.log(sidebarBtn); sidebarBtn.addEventListener('click', () => { sidebar.classList.toggle('close'); });
        document.addEventListener('DOMContentLoaded', function () { var currentYear = new Date().getFullYear(); var copyright = document.getElementById('copyright'); copyright.innerHTML = '&copy;' + currentYear + ' Silbito. Todos los derechos reservados.'; });
    </script>
</body>

</html>
)rawliteral";
#endif
//===========================================
//Config Web
//===========================================
String handleRoot = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
  <meta charset='UTF-8'>
  <title> VentoMeter | Silbito </title>
  <link rel='stylesheet' href='style.css'>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
</head>

<body>
  <div class='sidebar close'>
    <div class='logo-details'>
      <i class='bx bxl-mongodb'></i>
      <span class='logo_name'>VentoMeter</span>
    </div>
    <ul class='nav-links'>
      <li>
        <a href='#'>
          <i class='bx bx-grid-alt'></i>
          <span class='link_name'>Categorias</span>
        </a>
        <ul class='sub-menu blank'>
          <li><a class='link_name' href='#'>Categorias</a></li>
        </ul>
      </li>
      <li>
        <a href='/'>
          <i class='bx bx-home-alt-2'></i>
          <span class='link_name'>Inicio</span>
        </a>
        <ul class='sub-menu blank'>
          <li><a class='link_name' href='/'>Inicio</a></li>
        </ul>
      </li>
      <li>
        <div class='iocn-link'>
          <a href='/config'>
            <i class='bx bx-cog'></i>
            <span class='link_name'>Configuraciones</span>
          </a>
          <ul class='sub-menu blank'>
            <li><a class='link_name' href='/'>Configuraciones</a></li>
          </ul>
        </div>
      </li>


      <li>
        <a href='/updateota'>
          <div class='profile-details'>
            <div class='profile-content'>
            </div>
            <div class='name-job'>
              <div class='profile_name'>Actualizar</div>
              <div class='job'>" + String(VERSION) + "</div>
            </div>
            <i class='bx bxs-cloud-upload'></i>
          </div>
        </a>
      </li>

    </ul>
  </div>

  <section class='home-section'>
    <div class='home-content'>
      <i class='bx bx-menu'></i>
    </div>
    <header>
    </header>
    <main>
      <div class='cuerpo'>
        <h1 class='h1-head'> Configuración de API Keys </h1>
      </div>
    </main>
    <div class='tabla-stilo'>
      <form action='/save' method='POST'>


        <h3>ThingSpeak</h3>
        <label for='thingspeak_enabled'>Habilitar:</label>
        <input type='checkbox' id='thingspeak_enabled' name='thingspeak_enabled' %THING_SPEAK_CHECKED%
          onchange='toggleField("thingspeak_enabled", ["ts_api_key", "channelID"])'>
        <p></p>
        <label for='ts_api_key'>API Key:</label>
        <input type='text' id='ts_api_key' name='ts_api_key' value='%TS_API_KEY%' %TS_API_DISABLED%>
        <label for='channelID'>Channel ID:</label>
        <input type='text' id='channelID' name='channelID' value='%CHANNEL_ID%' %TS_API_DISABLED%>



        <h3>Weathercloud</h3>
        <label for='weathercloud_enabled'>Habilitar:</label>
        <input type='checkbox' id='weathercloud_enabled' name='weathercloud_enabled' %WEATHER_CLOUD_CHECKED%
          onchange='toggleField("weathercloud_enabled", ["ID2", "Key2"])'>
        <p></p>
        <label for='ID2'>ID:</label>
        <input type='text' id='ID2' name='ID2' value='%ID2%' %WEATHER_CLOUD_DISABLED%>
        <label for='Key2'>Key:</label>
        <input type='text' id='Key2' name='Key2' value='%Key2%' %WEATHER_CLOUD_DISABLED%>



        <h3>Windy</h3>
        <label for='windy_enabled'>Habilitar:</label>
        <input type='checkbox' id='windy_enabled' name='windy_enabled' %WINDY_CHECKED%
          onchange='toggleField("windy_enabled", ["WINDYPAGE"])'>
        <p></p>
        <label for='WINDYPAGE'>Windy API:</label>
        <input type='text' id='WINDYPAGE' name='WINDYPAGE' value='%WINDYPAGE%' %WINDY_DISABLED%>



        <h3>Weathercloud</h3>
        <label for='pwsweather_enabled'>Habilitar:</label>
        <input type='checkbox' id='pwsweather_enabled' name='pwsweather_enabled' %Pwsweather_CHECKED%
          onchange='toggleField("pwsweather_enabled", ["ID5", "Key5"])'>
        <p></p>
        <label for='ID5'>ID:</label>
        <input type='text' id='ID5' name='ID5' value='%ID5%' %Pwsweather_DISABLED%>
        <label for='Key5'>Key:</label>
        <input type='text' id='Key5' name='Key5' value='%Key5%' %Pwsweather_DISABLED%>
        <br>

        <input type='submit' value='Guardar'><br>
      </form>
    </div>
  </section>
  <footer>
    <ul class='social_icon'>
      <li><a href='#' target='_blank'><i class='bx bxl-instagram'></i></a></li>
      <li><a href='#' target='_blank'><i class='bx bxl-facebook'></i></a></li>
      <li><a href='https://github.com/AlessandroKlein' target='_blank'><i class='bx bxl-github'></i></a>
      </li>
      <li><a href='#'><i class='bx bxl-telegram' target='_blank'></i></a></li>
      <li><a href='#'><i class='bx bxl-discord-alt' target='_blank'></i></a></li>
      <li><a href='https://www.youtube.com/channel/UCEv8bj0D22b9hCfhylVzmoQ'><i class='bx bxl-youtube'
            target='_blank'></i></a></li>
    </ul>
    <ul class='menu__footer'>
      <li><a href='/'>Inicio</a></li>
      <li><a href='#'>Acerca de</a></li>
      <li><a href='#'>Servicios</a></li>
      <li><a href='#'>Team</a></li>
      <li><a href='#'>Contacto</a></li>
    </ul>
    <div class='p-class'>
      <p id='copyright'>&copy; Silbito. Todos los derechos reservados.</p>
    </div>
  </footer>
  <script type='module' src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js'></script>
  <script nomodule src='https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js'></script>
  <script>
    let arrow = document.querySelectorAll('.arrow'); for (var i = 0; i < arrow.length; i++) { arrow[i].addEventListener('click', (e) => { let arrowParent = e.target.parentElement.parentElement; arrowParent.classList.toggle('showMenu'); }); }
    let sidebar = document.querySelector('.sidebar'); let sidebarBtn = document.querySelector('.bx-menu'); console.log(sidebarBtn); sidebarBtn.addEventListener('click', () => { sidebar.classList.toggle('close'); });
    document.addEventListener('DOMContentLoaded', function () { var currentYear = new Date().getFullYear(); var copyright = document.getElementById('copyright'); copyright.innerHTML = '&copy;' + currentYear + ' Silbito. Todos los derechos reservados.'; });
  </script>

  <script>
    // Función para habilitar/deshabilitar campos
    function toggleField(checkboxId, fieldIds) {
      const isChecked = document.getElementById(checkboxId).checked;
      fieldIds.forEach(fieldId => {
        const field = document.getElementById(fieldId);
        if (field) {
          field.disabled = !isChecked;
        }
      });
    }

    // Inicializar los campos según el estado de los checkboxes
    document.addEventListener('DOMContentLoaded', function () {
      toggleField(" thingspeak_enabled", ["ts_api_key", "channelID"]); toggleField("weathercloud_enabled",
        ["ID2", "Key2"]); toggleField(" windy_enabled", ["WINDYPAGE"]); toggleField(" pwsweather_enabled",
          ["ID5", "Key5"]);
    }); </script>

</body>

</html>
)rawliteral";