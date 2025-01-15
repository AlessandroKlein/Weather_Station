//===========================================
//CSS Style
//===========================================
void handleCSS(AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(200, "text/css", css);
  response->addHeader("Content-Type", "text/css");
  request->send(response);
}

//===========================================
//Config Web
//===========================================
/*void handleRoot(AsyncWebServerRequest *request) {
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

  //server.send(200, "text/html", html);
  request->send(200, "text/html", html);
}
*/

// Función para limitar la longitud de las cadenas antes de guardarlas

void handleSave(AsyncWebServerRequest *request) {
  if (request->hasArg("ts_api_key")) {
    // Limitar el tamaño de la API Key
    String temp = request->arg("ts_api_key");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);  // Recortar si es necesario
    strcpy(ts_api_key, temp.c_str());
  }
  if (request->hasArg("ID2")) {
    // Limitar el tamaño del ID de Weathercloud
    String temp = request->arg("ID2");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(ID2, temp.c_str());
  }
  if (request->hasArg("channelID")) {
    String temp = request->arg("channelID");
    //channelID = temp.toInt();  // Convertir a número
    temp = temp.substring(0, MAX_API_KEY_LENGTH);  // Limitar longitud
    channelID = temp.toInt();  // Convertir a número
  }
  if (request->hasArg("Key2")) {
    // Limitar el tamaño de la clave de Weathercloud
    String temp = request->arg("Key2");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(Key2, temp.c_str());
  }
  if (request->hasArg("WINDYPAGE")) {
    // Limitar el tamaño del Endpoint de Windy
    String temp = request->arg("WINDYPAGE");
    temp = temp.substring(0, MAX_API_KEY_LENGTH_WINDYPAGE);
    strcpy(WINDYPAGE, temp.c_str());
  }
  if (request->hasArg("ID5")) {
    // Limitar el tamaño del ID de Pwsweather
    String temp = request->arg("ID5");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(ID5, temp.c_str());
  }
  if (request->hasArg("Key5")) {
    // Limitar el tamaño de la clave de Pwsweather
    String temp = request->arg("Key5");
    temp = temp.substring(0, MAX_API_KEY_LENGTH);
    strcpy(Key5, temp.c_str());
  }
  weathercloud_enabled = request->hasArg("weathercloud_enabled") && request->arg("weathercloud_enabled") == "on";
  thingspeak_enabled = request->hasArg("thingspeak_enabled") && request->arg("thingspeak_enabled") == "on";
  windy_enabled = request->hasArg("windy_enabled") && request->arg("windy_enabled") == "on";
  pwsweather_enabled = request->hasArg("pwsweather_enabled") && request->arg("pwsweather_enabled") == "on";

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

  //server.send(200, "text/html", html);
  request->send(200, "text/html", html);
}

//===========================================
//Actualizacion datos
//===========================================

/*void handleGetDataRequest(AsyncWebServerRequest *request) {
  // Aquí debes incluir la lógica para obtener los datos actualizados
  // desde tus sensores y generar un JSON con los datos.

  // Por simplicidad, aquí se proporciona un ejemplo estático de los datos:
  String jsonData = "{"
                    "\"temperatureC\": \"" + String(sensor.temperatureC) + "\","
                    "\"humidity\": \"" + String(sensor.humidity) + "\","
                    "\"barometricPressure\": \"" + String(sensor.barometricPressure) + "\","
                    "\"UVIndex\": \"" + String(sensor.UVIndex) + "\","
                    "\"lux\": \"" + String(sensor.lux) + "\","
                    "\"c02\": " + String(sensor.c02) + ","
                    "\"tvoc\": " + String(sensor.tvoc) + ","
                    "\"windSpeed\": \"" + String(sensor.windSpeed) + "\","
                    "\"windSpeedMax\": \"" + String(sensor.windSpeedMax) + "\","
                    "\"windDirectionADC\": \"" + String(sensor.windDirectionADC) + "\","
                    "\"windDirectiongradiant\": \"" + String(sensor.windDirectiongradiant) + "\","
                    "\"rainTicks60m\": \"" + String(sensor.rainTicks60m) + "\","
                    "\"rainTicks24h\": \"" + String(sensor.rainTicks24h) + "\""
                    "}";

  request->send(200, "application/json", jsonData);
}*/

void handleGetDataRequest(AsyncWebServerRequest *request) {
  StaticJsonDocument<512> jsonDoc;
  jsonDoc["temperatureC"] = sensor.temperatureC;
  jsonDoc["humidity"] = sensor.humidity;
  jsonDoc["barometricPressure"] = sensor.barometricPressure;
  jsonDoc["UVIndex"] = sensor.UVIndex;
  jsonDoc["lux"] = sensor.lux;
  jsonDoc["c02"] = sensor.c02;
  jsonDoc["tvoc"] = sensor.tvoc;
  jsonDoc["windSpeed"] = sensor.windSpeed;
  jsonDoc["windSpeedMax"] = sensor.windSpeedMax;
  jsonDoc["windDirectionADC"] = sensor.windDirectionADC;
  jsonDoc["windDirectiongradiant"] = sensor.windDirectiongradiant;
  jsonDoc["rainTicks60m"] = sensor.rainTicks60m;
  jsonDoc["rainTicks24h"] = sensor.rainTicks24h;

  String jsonData;
  serializeJson(jsonDoc, jsonData);
  request->send(200, "application/json", jsonData);
}


#ifdef OTAWeb

//===========================================
//OTA Web
//===========================================
void handleUpdate(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
 /* 
  if (!index) {
    Serial.printf("Actualizando: %s\n", filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
      Update.printError(Serial);
    }
  }

  if (Update.write(data, len) != len) {
    Update.printError(Serial);
  }

  if (final) {
    if (Update.end(true)) {
      Serial.println("Actualización exitosa. Reiniciando...");
      ESP.restart();
    } else {
      Update.printError(Serial);
    }
  }*/
}


#endif

//===========================================
//Config Web
//===========================================
String processor(const String& var) {
  if (var == "THING_SPEAK_CHECKED") {
    return thingspeak_enabled ? "checked" : "";
  }
  else if (var == "TS_API_KEY") {
    return ts_api_key;
  }
  else if (var == "CHANNEL_ID") {
    return String(channelIDStr);
  }
  else if (var == "WEATHER_CLOUD_CHECKED") {
    return weathercloud_enabled ? "checked" : "";
  }
  else if (var == "ID2") {
    return ID2;
  }
  else if (var == "Key2") {
    return Key2;
  }
  //
  else if (var == "WINDY_CHECKED") {
    return windy_enabled ? "checked" : "";
  }
  else if (var == "WINDYPAGE") {
    return WINDYPAGE;
  }
  else if (var == "PWSWEATHER_CHECKED") {
    return pwsweather_enabled ? "checked" : "";
  }
  else if (var == "ID5") {
    return ID5;
  }
  else if (var == "Key5") {
    return Key5;
  }
  //
  else if (var == "TS_API_DISABLED") {
    return thingspeak_enabled ? "" : "disabled";
  }
  else if (var == "WEATHER_CLOUD_DISABLED") {
    return weathercloud_enabled ? "" : "disabled";
  }
  else if (var == "WINDY_DISABLED") {
    return windy_enabled ? "" : "disabled";
  }
  else if (var == "PWSWEATHER_DISABLED") {
    return pwsweather_enabled ? "" : "disabled";
  }
  return String(); // Retorna vacío si el placeholder no coincide
}
