String getSensorDataJSON() {
  const size_t capacity = JSON_OBJECT_SIZE(16) + JSON_OBJECT_SIZE(9) + 24 * JSON_ARRAY_SIZE(1) + 5 * JSON_ARRAY_SIZE(1) + 384;
  StaticJsonDocument<capacity> doc;

  // Agregar datos de sensorData
  JsonObject sensorDataJson = doc.createNestedObject("sensorData");
  sensorDataJson["windDirectionADC"] = sensor.windDirectionADC;
  sensor.windDirectionGradient = convertToDegrees(sensor.windDirectionADC);
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
  sensorDataJson["co2"] = sensor.co2;
  sensorDataJson["tvoc"] = sensor.tvoc;

  // Agregar datos de rainfallData
  JsonObject rainfallDataJson = doc.createNestedObject("rainfallData");
  rainfallDataJson["intervalRainfall"] = rainData.intervalRainfall;

  rainfallDataJson["hourlyCarryover"] = rainData.hourlyCarryover;
  rainfallDataJson["priorHour"] = rainData.priorHour;
  rainfallDataJson["minuteCarryover"] = rainData.minuteCarryover;
  rainfallDataJson["priorMinute"] = rainData.priorMinute;

  String json;
  serializeJson(doc, json);
  return json;
}

void addRainfallArray(JsonObject& parent, const char* name, float* data, size_t length) {
  JsonArray array = parent.createNestedArray(name);
  for (size_t i = 0; i < length; i++) {
    array.add(data[i]);
  }
}

void windy(void) {
  HTTPClient http;
  String url = String("https://") + wy_server + wy_serverurl + wy_WINDYPAGE;

#ifdef SerialMonitor
  Serial.print("Enviando petición a Windy (POST): ");
  Serial.println(url);
#endif

  http.begin(url, true);
  http.addHeader("Content-Type", "application/json");  // Importante: indicar que se envía JSON

  String jsonData = getSensorDataJSON();  // Obtener el JSON
#ifdef SerialMonitor
  Serial.print("JSON a enviar: ");
  Serial.println(jsonData);
#endif

  int httpResponseCode = http.POST(jsonData);  // Enviar el JSON en el cuerpo de la petición

#ifdef SerialMonitor
  if (httpResponseCode > 0) {
    Serial.print("Código de respuesta HTTP de Windy: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Respuesta de Windy:");
      Serial.println(payload);
    } else {
      Serial.print("Respuesta de Windy (error): ");
      Serial.println(http.getString());
    }
  } else {
    Serial.print("Error al enviar la petición a Windy: ");
    Serial.println(http.errorToString(httpResponseCode));
  }
#endif

  http.end();
}
