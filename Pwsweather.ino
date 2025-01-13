void pws(void) {
  Serial.print("Conectado a ");
  Serial.println(server5);
  WiFiClient client;
  if (client.connect(server5, 80)) {
    Serial.print("Conectado a ");
    Serial.println(client.remoteIP());
    delay(100);
  } else {
    Serial.println("la conexión falló");
  }
  client.print(WEBPAGE5);
  client.print("ID=");
  client.print(ID5);
  client.print("&PASSWORD=");
  client.print(Key5);
  client.print("&tempf=");
  client.print(sensor.temperatureAHT);
  client.print("&humidity=");
  client.print(sensor.humidity);
  client.print("&uvi=");
  client.print(sensor.UVIndex);
  client.print("&tvoc=");
  client.print(sensor.tvoc);
  client.print("&CO=");
  client.print(sensor.c02);
  client.print("&baromin=");
  client.print(sensor.barometricPressure);
  client.print("&windDirectiongradiant=");
  client.print(sensor.windDirectiongradiant);
  client.print("&windSpeed=");
  client.print(sensor.windSpeed);
  client.print("&lux=");
  client.print(sensor.lux);
  client.print("&rainTicks60m=");
  client.print(sensor.rainTicks60m);
  client.print("&rainTicks24h=");
  client.print(sensor.rainTicks24h);
  client.print("&softwaretype=NodeMCU-ESP12&action=updateraw");
  client.print("/ HTTP/1.1\r\nHost: pwsupdate.pwsweather.com:80\r\nConnection: close\r\n\r\n");
  Serial.println(" ");
  delay(1000);
}