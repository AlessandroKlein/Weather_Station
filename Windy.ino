String getSensorDataJSON() {
  const size_t capacity = JSON_OBJECT_SIZE(16) + JSON_OBJECT_SIZE(9) + 24 * JSON_ARRAY_SIZE(1) + 5 * JSON_ARRAY_SIZE(1) + 384;  // Estimación del tamaño del documento
  StaticJsonDocument<capacity> doc;

  // Agregar datos de sensorData
  JsonObject sensorDataJson = doc.createNestedObject("sensorData");
  sensorDataJson["windDirectionADC"] = sensor.windDirectionADC;
  sensorDataJson["windDirectiongradiant"] = sensor.windDirectiongradiant;
  sensorDataJson["rainTicks24h"] = sensor.rainTicks24h;
  sensorDataJson["rainTicks60m"] = sensor.rainTicks60m;
  sensorDataJson["temperatureC"] = sensor.temperatureC;
  sensorDataJson["temperatureAHT"] = sensor.temperatureAHT;
  sensorDataJson["temperatureBMP"] = sensor.temperatureBMP;
  sensorDataJson["windSpeed"] = sensor.windSpeed;
  sensorDataJson["windSpeedMax"] = sensor.windSpeedMax;
  sensorDataJson["barometricPressure"] = sensor.barometricPressure;
  sensorDataJson["humidity"] = sensor.humidity;
  sensorDataJson["UVIndex"] = sensor.UVIndex;
  sensorDataJson["lux"] = sensor.lux;
  sensorDataJson["c02"] = sensor.c02;
  sensorDataJson["tvoc"] = sensor.tvoc;

  // Agregar datos de rainfallData
  JsonObject rainfallDataJson = doc.createNestedObject("rainfallData");
  rainfallDataJson["intervalRainfall"] = rainData.intervalRainfall;

  JsonArray hourlyRainfallArray = rainfallDataJson.createNestedArray("hourlyRainfall");
  for (int i = 0; i < 24; i++) {
    hourlyRainfallArray.add(rainData.hourlyRainfall[i]);
  }

  JsonArray current60MinRainfallArray = rainfallDataJson.createNestedArray("current60MinRainfall");
  for (int i = 0; i < 5; i++) {
    current60MinRainfallArray.add(rainData.current60MinRainfall[i]);
  }

  rainfallDataJson["hourlyCarryover"] = rainData.hourlyCarryover;
  rainfallDataJson["priorHour"] = rainData.priorHour;
  rainfallDataJson["minuteCarryover"] = rainData.minuteCarryover;
  rainfallDataJson["priorMinute"] = rainData.priorMinute;

  String json;
  serializeJson(doc, json);
  return json;
}

void windy(void) {
  HTTPClient http;

  String url = String("https://") + server4 /*+ ":" + String(serverPort)*/ + serverurl + WINDYPAGE;  // Construcción de la URL (más concisa)
  //http.begin(url, true); // Habilitar verificación SSL

  Serial.print("Enviando petición a Windy: ");
  Serial.println(url);

  http.begin(url, true); // Inicializar la conexión *solo una vez* con verificación SSL

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("Código de respuesta HTTP de Windy: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Respuesta de Windy:");
      Serial.println(payload);
    } else {
      Serial.print("Respuesta de Windy (error): ");
      Serial.println(http.getString());  // Imprimir el mensaje de error del servidor
    }
  } else {
    Serial.print("Error al enviar la petición a Windy: ");
    Serial.println(http.errorToString(httpResponseCode));
  }

  http.end();
}
