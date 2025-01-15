//===========================================
//CSS Style
//===========================================
void handleCSS(AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(200, "text/css", css);
  response->addHeader("Content-Type", "text/css");
  request->send(response);
}

//===========================================
//Salve Web
//===========================================
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
                    "\"co2\": " + String(sensor.co2) + ","
                    "\"tvoc\": " + String(sensor.tvoc) + ","
                    "\"windSpeed\": \"" + String(sensor.windSpeed) + "\","
                    "\"windSpeedMax\": \"" + String(sensor.windSpeedMax) + "\","
                    "\"windDirectionADC\": \"" + String(sensor.windDirectionADC) + "\","
                    "\"windDirectionGradient\": \"" + String(sensor.windDirectionGradient) + "\","
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
  jsonDoc["co2"] = sensor.co2;
  jsonDoc["tvoc"] = sensor.tvoc;
  jsonDoc["windSpeed"] = sensor.windSpeed;
  jsonDoc["windSpeedMax"] = sensor.windSpeedMax;
  jsonDoc["windDirectionADC"] = sensor.windDirectionADC;
  jsonDoc["windDirectionGradient"] = sensor.windDirectionGradient;
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
