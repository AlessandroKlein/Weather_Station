void pws(void)
{
  HTTPClient http;

  // Enviar datos a PWSweather (con GET)
  // String serverPath = "http://pwsupdate.pwsweather.com/api/v1/submitwx?";
  String serverPath = String(pw_server) + String(pw_WEBPAGE);
  serverPath += "ID=" + String(pw_I5);
  serverPath += "&PASSWORD=" + String(pw_Key);
  //serverPath += "&dateutc=" + String(hour) + ":" + String(minute) + ":" + String(second);
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
  int httpResponseCode;
  http.begin(serverPath);
  httpResponseCode = http.GET();
  if (httpResponseCode > 0)
  {
#ifdef SerialMonitor
    Serial.println("Datos enviados correctamente a PWSweather\n");
#endif
  }
  else
  {
#ifdef SerialMonitor
    Serial.printf("Error al enviar datos a PWSweather. Código de error: %d\n", httpResponseCode);
#endif
  }
  http.end();
}
