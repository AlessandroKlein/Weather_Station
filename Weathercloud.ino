void weathercloud(void) {
  /*{
    Serial.print("Conectado a ");
    Serial.print(server2);
    Serial.println("...");
    WiFiClient client;
    if (client.connect(server2, 80)) {
      Serial.print("Conectado a ");
      Serial.println(client.remoteIP());
    } else {
      Serial.println("la conexión falló");
    }
    client.print("GET /set/wid/");
    client.print(ID2);
    client.print("/key/");
    client.print(Key2);
    client.print("/temp/");
    client.print(sensor.temperatureAHT);
    /*client.print("/chill/");
      client.print(chill_c * 10);
      client.print("/dew/");
      client.print(dewpt_c * 10);
      client.print("/heat/");
      client.print(heat_c * 10);*/
  client.print("/hum/");
  client.print(sensor.humidity);
  client.print("/bar/");
  client.print(sensor.barometricPressure);
  /*client.print("/tempin/");
      client.print(tempc_min * 10);
      client.print("/dewin/");
      client.print(dewpt_c * 10);
      client.print("/heatin/");
      client.print(heat_c * 10);*/
  /* client.print("/humin/");
      client.print(humidity);*/
  /*client.print("/puntorocio/");
      client.print(puntoRocio);
      client.print("/sensaciontermica/");
      client.print(sensaciontermica);*/
  client.print("/uvi/");
  client.print(sensor.UVIndex);
  client.print("/CO2/");
  client.print(sensor.c02);
  client.print("/TVOC/");
  client.print(sensor.tvoc);
  client.print("/LUX/");
  client.print(sensor.lux);
  client.print("/windSpeed/");
  client.print(sensor.windSpeed);
  client.print("/rainTicks60m/");
  client.print(sensor.rainTicks60m);
  client.print("/rainTicks24h/");
  client.print(sensor.rainTicks24h);
  client.print("/LUX/");
  client.print(sensor.lux);
  /*client.print("/humedadabsoluta/");
      client.print(humedadabsoluta);
      client.print("/humedadespecifica/");
      client.print(humedadespecifica);
      client.print("/conforttermico/");
      client.print(conforttermico);
      client.print("/AlturaNubes/");
      client.print(AlturaNubes);
      client.print("/cargaCalor/");
      client.print(cargaCalor);
      client.print("/prevapor/");
      client.print(prevapor);*/
  //client.print("/uvi/");
  //client.print(uvi);
  /*client.println("/ HTTP/1.1");
    client.println("Host: api.weathercloud.net");
    client.println();
    //delay(1000);

    if (!client.connected()) {
      Serial.println("Cliente desconectado.");
      if (client.connect(server2, 80)) {
        delay(100);
        Serial.print("Conectado a ");
        Serial.println(client.remoteIP());

      } else {
        Serial.println("la conexión falló");
      }
    }
  }
  delay(1000);*/


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

  Serial.println("Enviando JSON:");
  Serial.println(json);

  int httpResponseCode = http.POST(json);

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

  http.end();
}
