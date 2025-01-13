void pws(void) {
  HTTPClient http;
  
  String dateTimeUTC = getCurrentDateTimeUTC();
  String serverPath = "http://pwsupdate.pwsweather.com/api/v1/submitwx?";
  serverPath += "ID=";
  serverPath += ID5;
  serverPath += "&PASSWORD=";
  serverPath += Key5;
  serverPath += "&dateutc=";
  serverPath += dateTimeUTC;  // Fecha y hora UTC
  serverPath += "&tempf=";
  serverPath += String(sensor.temperatureC * 1.8 + 32);  // Convertir a Fahrenheit
  serverPath += "&humidity=";
  serverPath += String(sensor.humidity);
  serverPath += "&baromin=";
  serverPath += String(sensor.barometricPressure * 0.02953);  // Convertir a pulgadas de Hg
  serverPath += "&windspeedmph=";
  serverPath += String(sensor.windSpeed * 1.60934);  // Convertir a mph
  serverPath += "&windgustmph=";
  serverPath += String(sensor.windSpeedMax * 1.60934);  // Convertir a mph
  serverPath += "&winddir=";
  serverPath += String(sensor.windDirectiongradiant);
  serverPath += "&rainin=";
  serverPath += String(rainData.intervalRainfall * 0.0393701);  // Convertir a pulgadas

  // Agregar otros parámetros según tus sensores y la documentación de PWSweather
  // Ejemplos:
  // serverPath += "&UV=";
  // serverPath += String(sensor.UVIndex);
  // serverPath += "&solar=";
  // serverPath += String(sensor.lux);


  Serial.print("Enviando petición a: ");
  Serial.println(serverPath);

  http.begin(serverPath);
  int httpResponseCode = http.GET();

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