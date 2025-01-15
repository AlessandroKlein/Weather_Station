void pws(void) {
  HTTPClient http;

  // Enviar datos a Weathercloud (con JSON y POST)
  http.begin("http://api.weathercloud.net/v1/push/" + String(ID2) + "?key=" + String(Key2));
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Agregar datos de sensorData
  doc["windDirectionADC"] = sensor.windDirectionADC;
  doc["windDirectionGradient"] = sensor.windDirectionGradient;
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
  doc["co2"] = sensor.co2;
  doc["tvoc"] = sensor.tvoc;

  // Agregar datos de rainfallData (con arrays anidados)
  JsonObject rainfall = doc.createNestedObject("rainfall");
  rainfall["hourlyCarryover"] = rainData.hourlyCarryover;
  rainfall["priorHour"] = rainData.priorHour;
  rainfall["minuteCarryover"] = rainData.minuteCarryover;
  rainfall["priorMinute"] = rainData.priorMinute;

  String json;
  serializeJson(doc, json);

  int httpResponseCode = http.POST(json);
  if (httpResponseCode > 0) {
#ifdef SerialMonitor
    Serial.println("Datos enviados correctamente a Weathercloud\n");
#endif
  } else {
#ifdef SerialMonitor
    Serial.printf("Error al enviar datos a Weathercloud. Código de error: %d\n", httpResponseCode);
#endif
  }
  http.end();

  // Enviar datos a PWSweather (con GET)
  String serverPath = "http://pwsupdate.pwsweather.com/api/v1/submitwx?";
  serverPath += "ID=" + String(ID5);
  serverPath += "&PASSWORD=" + String(Key5);
  serverPath += "&dateutc=" + String(hour) + ":" + String(minute) + ":" + String(second);
  serverPath += "&tempf=" + String(sensor.temperatureC * 1.8 + 32);
  serverPath += "&humidity=" + String(sensor.humidity);
  serverPath += "&baromin=" + String(sensor.barometricPressure * 0.02953);
  serverPath += "&windspeedmph=" + String(sensor.windSpeed * 1.60934);
  serverPath += "&windgustmph=" + String(sensor.windSpeedMax * 1.60934);
  serverPath += "&winddir=" + String(sensor.windDirectionGradient);
  serverPath += "&rainin=" + String(rainData.intervalRainfall * 0.0393701);
  serverPath += "&UV=" + String(sensor.UVIndex);
  serverPath += "&solar=" + String(sensor.lux);
  serverPath += "&co2=" + String(sensor.co2);

#ifdef SerialMonitor
  Serial.print("Enviando petición a: ");
  Serial.println(serverPath);
#endif

  http.begin(serverPath);
  httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
#ifdef SerialMonitor
    Serial.println("Datos enviados correctamente a PWSweather\n");
#endif
  } else {
#ifdef SerialMonitor
    Serial.printf("Error al enviar datos a PWSweather. Código de error: %d\n", httpResponseCode);
#endif
  }
  http.end();
}
