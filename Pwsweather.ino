void pws(void) {
  HTTPClient http;

  // Enviar datos a Weathercloud (con JSON y POST)
  http.begin("http://api.weathercloud.net/v1/push/" + String(ID2) + "?key=" + String(Key2));
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Agregar datos de sensorData
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

  // Agregar datos de rainfallData (con arrays anidados)
  JsonObject rainfall = doc.createNestedObject("rainfall");
  rainfall["intervalRainfall"] = rainData.intervalRainfall;
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

  int httpResponseCode = http.POST(json);
  // ... (Manejo de la respuesta HTTP de Weathercloud)
  http.end();

  // Enviar datos a PWSweather (con GET)
  String serverPath = "http://pwsupdate.pwsweather.com/api/v1/submitwx?";
  serverPath += "ID=";
  serverPath += ID5;
  serverPath += "&PASSWORD=";
  serverPath += Key5;
  serverPath += "&dateutc=";
  serverPath += hour, ":", minute, ":", second;
  serverPath += "&tempf=";
  serverPath += String(sensor.temperatureC * 1.8 + 32);
  serverPath += "&humidity=";
  serverPath += String(sensor.humidity);
  serverPath += "&baromin=";
  serverPath += String(sensor.barometricPressure * 0.02953);
  serverPath += "&windspeedmph=";
  serverPath += String(sensor.windSpeed * 1.60934);
  serverPath += "&windgustmph=";
  serverPath += String(sensor.windSpeedMax * 1.60934);
  serverPath += "&winddir=";
  serverPath += String(sensor.windDirectiongradiant);
  serverPath += "&rainin=";
  serverPath += String(rainData.intervalRainfall * 0.0393701);
  serverPath += "&UV=";
  serverPath += String(sensor.UVIndex);
  serverPath += "&solar=";
  serverPath += String(sensor.lux);
  serverPath += "&co2=";
  serverPath += String(sensor.c02);

#ifdef SerialMonitor
  Serial.print("Enviando petición a: ");
  Serial.println(serverPath);
#endif

  http.begin(serverPath);
  httpResponseCode = http.GET();
  // ... (Manejo de la respuesta HTTP de PWSweather)
  http.end();
}