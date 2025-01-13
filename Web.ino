void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";  // Especifica UTF-8 como codificación de caracteres
  html += "<title>Configuración Estación meteorológica</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 20px; background-color: #0E0E0E; color: #CCCCCC; }";
  html += "h1 { text-align: center; color: #00ABE4; }";
  html += "form { max-width: 600px; margin: auto; background: #000; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }";
  html += "h3 { color: #00ABE4; }";
  html += "label { display: block; margin-bottom: 8px; font-weight: bold; }";
  html += "input[type='text'], input[type='checkbox'] { margin-bottom: 20px; width: 100%; padding: 8px; box-sizing: border-box; border: 1px solid #ccc; border-radius: 4px; }";
  html += "input[type='submit'] { background-color: #00ABE4; color: white; border: none; padding: 10px 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; border-radius: 4px; cursor: pointer; }";
  html += "input[type='submit']:hover { background-color: #00ABE4; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Configuración de API Keys</h1>";

  // Formulario con los datos para la configuración
  html += "<form action='/save' method='POST'>";

  // ThingSpeak
  html += "<h3>ThingSpeak</h3>";
  html += "<label for='thingspeak_enabled'>Habilitar ThingSpeak:</label>";
  html += "<input type='checkbox' id='thingspeak_enabled' name='thingspeak_enabled' " + String(thingspeak_enabled ? "checked" : "") + " onchange='toggleField(\"thingspeak_enabled\", [\"ts_api_key\", \"channelID\"])'>";
  html += "<label for='ts_api_key'>ThingSpeak API Key:</label>";
  html += "<input type='text' id='ts_api_key' name='ts_api_key' value='" + String(ts_api_key) + "' " + String(thingspeak_enabled ? "" : "disabled") + ">";
  html += "<label for='channelID'>Channel ID:</label>";
  html += "<input type='text' id='channelID' name='channelID' value='" + String(channelID) + "' " + String(thingspeak_enabled ? "" : "disabled") + ">";

  // Weathercloud
  html += "<h3>Weathercloud</h3>";
  html += "<label for='weathercloud_enabled'>Habilitar Weathercloud.net:</label>";
  html += "<input type='checkbox' id='weathercloud_enabled' name='weathercloud_enabled' " + String(weathercloud_enabled ? "checked" : "") + " onchange='toggleField(\"weathercloud_enabled\", [\"ID2\", \"Key2\"])'>";
  html += "<label for='ID2'>Weathercloud ID:</label>";
  html += "<input type='text' id='ID2' name='ID2' value='" + String(ID2) + "' " + String(weathercloud_enabled ? "" : "disabled") + ">";
  html += "<label for='Key2'>Weathercloud Key:</label>";
  html += "<input type='text' id='Key2' name='Key2' value='" + String(Key2) + "' " + String(weathercloud_enabled ? "" : "disabled") + ">";

  // Windy
  html += "<h3>Windy</h3>";
  html += "<label for='windy_enabled'>Habilitar Windy.com:</label>";
  html += "<input type='checkbox' id='windy_enabled' name='windy_enabled' " + String(windy_enabled ? "checked" : "") + " onchange='toggleField(\"windy_enabled\", \"WINDYPAGE\")'>";
  html += "<label for='WINDYPAGE'>Windy API Endpoint:</label>";
  html += "<input type='text' id='WINDYPAGE' name='WINDYPAGE' value='" + String(WINDYPAGE) + "' " + String(windy_enabled ? "" : "disabled") + ">";

  // Pwsweather
  html += "<h3>Pwsweather</h3>";
  html += "<label for='pwsweather_enabled'>Habilitar Pwsweather.com:</label>";
  html += "<input type='checkbox' id='pwsweather_enabled' name='pwsweather_enabled' " + String(pwsweather_enabled ? "checked" : "") + " onchange='toggleField(\"pwsweather_enabled\", [\"ID5\", \"Key5\"])'>";
  html += "<label for='ID5'>Pwsweather ID:</label>";
  html += "<input type='text' id='ID5' name='ID5' value='" + String(ID5) + "' " + String(pwsweather_enabled ? "" : "disabled") + ">";
  html += "<label for='Key5'>Pwsweather Key:</label>";
  html += "<input type='text' id='Key5' name='Key5' value='" + String(Key5) + "' " + String(pwsweather_enabled ? "" : "disabled") + ">";

  html += "<input type='submit' value='Guardar'>";
  html += "</form>";

  // JavaScript para habilitar/deshabilitar campos
  html += "<script>";
  html += "function toggleField(checkboxId, fields) {";
  html += "    if (!Array.isArray(fields)) fields = [fields];";
  html += "    const isChecked = document.getElementById(checkboxId).checked;";
  html += "    fields.forEach(fieldId => {";
  html += "        const field = document.getElementById(fieldId);";
  html += "        if (field) field.disabled = !isChecked;";
  html += "    });";
  html += "}";
  html += "</script>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

// Función para limitar la longitud de las cadenas antes de guardarlas

void handleSave() {
  if (server.hasArg("ts_api_key")) {
    // Limitar el tamaño de la API Key
    String temp = server.arg("ts_api_key");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);  // Recortar si es necesario
    strcpy(ts_api_key, temp.c_str());
  }
  if (server.hasArg("ID2")) {
    // Limitar el tamaño del ID de Weathercloud
    String temp = server.arg("ID2");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(ID2, temp.c_str());
  }
  if (server.hasArg("channelID")) {
    String temp = server.arg("channelID");
    //channelID = temp.toInt();  // Convertir a número
    temp = temp.substring(0, MAX_API_KEY_LENGTH);  // Limitar longitud
    channelID = temp.toInt();  // Convertir a número
  }
  if (server.hasArg("Key2")) {
    // Limitar el tamaño de la clave de Weathercloud
    String temp = server.arg("Key2");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(Key2, temp.c_str());
  }
  if (server.hasArg("WINDYPAGE")) {
    // Limitar el tamaño del Endpoint de Windy
    String temp = server.arg("WINDYPAGE");
    temp = temp.substring(0, MAX_API_KEY_LENGTH_WINDYPAGE);
    strcpy(WINDYPAGE, temp.c_str());
  }
  if (server.hasArg("ID5")) {
    // Limitar el tamaño del ID de Pwsweather
    String temp = server.arg("ID5");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(ID5, temp.c_str());
  }
  if (server.hasArg("Key5")) {
    // Limitar el tamaño de la clave de Pwsweather
    String temp = server.arg("Key5");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(Key5, temp.c_str());
  }
  weathercloud_enabled = server.hasArg("weathercloud_enabled") && server.arg("weathercloud_enabled") == "on";
  thingspeak_enabled = server.hasArg("thingspeak_enabled") && server.arg("thingspeak_enabled") == "on";
  windy_enabled = server.hasArg("windy_enabled") && server.arg("windy_enabled") == "on";
  pwsweather_enabled = server.hasArg("pwsweather_enabled") && server.arg("pwsweather_enabled") == "on";

  saveConfig();  // Guarda la configuración

  // Respuesta HTML
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<title>Configuración guardada</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 20px; background-color: #0E0E0E; color: #CCCCCC; }";
  html += "h1 { text-align: center; color: #00ABE4; }";
  html += "p { font-size: 16px; line-height: 1.5; margin-bottom: 15px; }";
  html += "a { display: block; text-align: center; margin: 20px auto; text-decoration: none; font-size: 16px; background-color: #00ABE4; color: white; padding: 10px 20px; border-radius: 4px; width: 150px; }";
  html += "a:hover { background-color: #00ABE4; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Configuración guardada</h1>";
  html += "<p><strong>ThingSpeak API Key:</strong> " + String(ts_api_key) + " | <strong>channelID:</strong> " + String(channelID) + " | " + String(thingspeak_enabled ? "Habilitado" : "Deshabilitado") + "</p>";
  html += "<p><strong>Weathercloud ID:</strong> " + String(ID2) + " | <strong>Key:</strong> " + String(Key2) + " | " + String(weathercloud_enabled ? "Habilitado" : "Deshabilitado") + "</p>";
  html += "<p><strong>Windy Endpoint:</strong> " + String(WINDYPAGE) + " | " + String(windy_enabled ? "Habilitado" : "Deshabilitado") + "</p>";
  html += "<p><strong>Pwsweather ID:</strong> " + String(ID5) + " | <strong>Key:</strong> " + String(Key5) + " | " + String(pwsweather_enabled ? "Habilitado" : "Deshabilitado") + "</p>";
  html += "<a href='/'>Volver</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

#ifdef webSocket
//===========================================
//WebSocket
//===========================================
// Función para convertir los datos de sensorData a JSON
String sensorDataToJson() {
  DynamicJsonDocument doc(1024);
  doc["windDirectionADC"] = sensor.windDirectionADC;
  doc["windDirectiongradiant"] = sensor.windDirectiongradiant;
  doc["rainTicks24h"] = sensor.rainTicks24h;
  doc["rainTicks60m"] = sensor.rainTicks60m;
  doc["temperatureC"] = sensor.temperatureC;
  doc["temperatureAHT"] = sensor.temperatureAHT;
  doc["temperatureBMP"] = sensor.temperatureBMP;
  doc["windSpeed"] = sensor.windSpeed;
  doc["windSpeedMax"] = sensor.windSpeedMax;
  doc["barometricPressure"] = sensor.barometricPressure;
  doc["humidity"] = sensor.humidity;
  doc["UVIndex"] = sensor.UVIndex;
  doc["lux"] = sensor.lux;
  doc["c02"] = sensor.c02;
  doc["tvoc"] = sensor.tvoc;

  String output;
  serializeJson(doc, output);  // Serializa el objeto JSON en un String
  return output;
}

//===========================================
//WebSocket Web
//===========================================
void handleWebPage() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<title>Estación Meteorológica</title>";

  // Estilo CSS para la página
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 20px; background-color: #0E0E0E; color: #CCCCCC; }";
  html += "h1 { text-align: center; color: #00ABE4; }";
  html += "p { font-size: 16px; line-height: 1.5; margin-bottom: 15px; }";
  html += "span { font-weight: bold; color: #00ABE4; }";
  html += "div#sensorData { max-width: 800px; margin: auto; background: #000; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }";
  html += "h3 { color: #00ABE4; margin-top: 20px; }";
  html += "hr { border: 1px solid #00ABE4; margin-top: 30px; margin-bottom: 30px; }";
  html += "</style>";

  html += "</head><body>";

  // Título de la página
  html += "<h1>Estación Meteorológica</h1>";

  // Contenedor de los datos de los sensores
  html += "<div id='sensorData'>";
  html += "<h3>Datos en tiempo real</h3>";

  // Mostrar los valores iniciales de los sensores
  html += "<p><span>Dirección del viento (ADC):</span> <span id='windDirectionADC'>" + String(sensor.windDirectionADC) + "</span></p>";
  html += "<p><span>Temperatura (°C):</span> <span id='temperatureC'>" + String(sensor.temperatureC) + "</span></p>";
  html += "<p><span>Humedad (%):</span> <span id='humidity'>" + String(sensor.humidity) + "</span></p>";
  html += "<p><span>Velocidad del viento (m/s):</span> <span id='windSpeed'>" + String(sensor.windSpeed) + "</span></p>";
  html += "<p><span>Presión barométrica (hPa):</span> <span id='barometricPressure'>" + String(sensor.barometricPressure) + "</span></p>";
  html += "<p><span>Índice UV:</span> <span id='UVIndex'>" + String(sensor.UVIndex) + "</span></p>";
  html += "<p><span>Luz (lux):</span> <span id='lux'>" + String(sensor.lux) + "</span></p>";
  html += "<p><span>CO2 (ppm):</span> <span id='c02'>" + String(sensor.c02) + "</span></p>";
  html += "<p><span>TVOC (ppb):</span> <span id='tvoc'>" + String(sensor.tvoc) + "</span></p>";
  html += "</div>";

  // Script JavaScript para WebSocket
  html += "<script>";
  html += "var ws = new WebSocket('ws://' + window.location.hostname + ':81');";  // Conexión WebSocket
  html += "ws.onopen = function() {";
  html += "  console.log('Conexión WebSocket establecida.');";
  html += "};";

  html += "ws.onmessage = function(event) {";
  html += "  var sensorData = JSON.parse(event.data);";  // Recibe los datos en formato JSON
  html += "  document.getElementById('windDirectionADC').textContent = sensorData.windDirectionADC;";
  html += "  document.getElementById('temperatureC').textContent = sensorData.temperatureC;";
  html += "  document.getElementById('humidity').textContent = sensorData.humidity;";
  html += "  document.getElementById('windSpeed').textContent = sensorData.windSpeed;";
  html += "  document.getElementById('barometricPressure').textContent = sensorData.barometricPressure;";
  html += "  document.getElementById('UVIndex').textContent = sensorData.UVIndex;";
  html += "  document.getElementById('lux').textContent = sensorData.lux;";
  html += "  document.getElementById('c02').textContent = sensorData.c02;";
  html += "  document.getElementById('tvoc').textContent = sensorData.tvoc;";
  html += "};";
  html += "</script>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

//===========================================
//WebSocket Web
//===========================================
// Función que maneja los eventos de WebSocket
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("Cliente WebSocket conectado");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Cliente WebSocket desconectado");
      break;
    case WStype_TEXT:
      Serial.println("Mensaje recibido");
      break;
  }
}

//===========================================
//olicitud AJAX
//===========================================
void handleSensorData() {
  String json = "{";
  json += "\"windDirectionADC\":" + String(sensor.windDirectionADC) + ",";
  json += "\"temperatureC\":" + String(sensor.temperatureC) + ",";
  json += "\"humidity\":" + String(sensor.humidity) + ",";
  json += "\"windSpeed\":" + String(sensor.windSpeed) + ",";
  json += "\"barometricPressure\":" + String(sensor.barometricPressure) + ",";
  json += "\"UVIndex\":" + String(sensor.UVIndex) + ",";
  json += "\"lux\":" + String(sensor.lux) + ",";
  json += "\"c02\":" + String(sensor.c02) + ",";
  json += "\"tvoc\":" + String(sensor.tvoc);
  json += "}";
  server.send(200, "application/json", json);
}

#endif
