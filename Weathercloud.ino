void weathercloud(void) {
  HTTPClient http;
  http.begin("http://api.weathercloud.net/v1/push/" + String(ID2) + "?key=" + String(Key2));
  http.addHeader("Content-Type", "application/json");

  //StaticJsonDocument doc(JSON_BUFFER_SIZE);
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Agregar datos de sensorData al JSON
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

  // Agregar datos de rainfallData al JSON (como un objeto anidado)
  JsonObject rainfall = doc.createNestedObject("rainfall");
  rainfall["intervalRainfall"] = rainData.intervalRainfall;
  //Para los arrays, se debe iterar sobre ellos
  JsonArray hourlyRainfallArray = rainfall.createNestedArray("hourlyRainfall");
  for (int i = 0; i < 24; i++) {
    hourlyRainfallArray.add(rainData.hourlyRainfall[i]);
  }
  JsonArray current60MinRainfallArray = rainfall.createNestedArray("current60MinRainfall");
  for (int i = 0; i < 5; i++) {
    current60MinRainfallArray.add(rainData.current60MinRainfall[i]);
  }
  rainfall["hourlyCarryover"] = rainData.hourlyCarryover;
  rainfall["priorHour"] = rainData.priorHour;
  rainfall["minuteCarryover"] = rainData.minuteCarryover;
  rainfall["priorMinute"] = rainData.priorMinute;


  String json;
  serializeJson(doc, json);

#ifdef SerialMonitor
  Serial.println("Enviando JSON:");
  Serial.println(json);
#endif

  int httpResponseCode = http.POST(json);

#ifdef SerialMonitor
  if (httpResponseCode > 0) {
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Respuesta del servidor:");
      Serial.println(payload);
    }
  } else {
    Serial.print("Error al enviar la petición: ");
    Serial.println(http.errorToString(httpResponseCode));
  }
#endif

  http.end();
}
