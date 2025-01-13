void windy(void) {
  Serial.print("Conectado a ");
  Serial.println(server4);
  WiFiClient client;
  if (client.connect(server4, 80)) {
    Serial.print("Conectado a ");
    Serial.println(client.remoteIP());
    delay(100);
  } else {
    Serial.println("la conexión falló");
  }
  client.print(WINDYPAGE);
  client.print("station=");
  client.print("0");
  client.print("temp=");
  client.print(sensor.temperatureAHT);
  client.print("&humidity=");
  client.print(sensor.humidity);
  client.print("&uvi=");
  client.print(sensor.UVIndex);
  /*client.print("&dewpoint=");
    client.print(dewpt_c);*/
  client.print("&mbar=");
  client.print(sensor.barometricPressure);
  client.print("&TVOC=");
  client.print(sensor.tvoc);
  client.print("&CO=");
  client.print(sensor.c02);
  client.print("&LUX=");
  client.print(sensor.lux);
  client.print("&windDirectiongradiant=");
  client.print(sensor.windDirectiongradiant);
  client.print("&windSpeed=");
  client.print(sensor.windSpeed);
  client.print("&rainTicks60m=");
  client.print(sensor.rainTicks60m);
  client.print("&rainTicks24h=");
  client.print(sensor.rainTicks24h);

  client.print("/ HTTP/1.1\r\nHost: stations.windy.com:80\r\nConnection: close\r\n\r\n");
  Serial.println(" ");
  delay(1000);
}
