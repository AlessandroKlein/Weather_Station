void thingspeak(void) {
  /*{
    Serial.print("conectado a ");
    Serial.print(server3);
    Serial.println("...");
    WiFiClient client;
    if (client.connect(server3, 80)) {  // usar ip 184.106.153.149 o api.thingspeak.com
      Serial.print("Conectado a ");
      Serial.println(client.remoteIP());

      String postStr = String(ts_api_key);
      postStr += "&field1=";
      postStr += String(sensor.temperatureAHT);
      postStr += "&field2=";
      postStr += String(sensor.humidity);
      postStr += "&field3=";
      postStr += String(sensor.barometricPressure);
      postStr += "&field4=";
      postStr += String(sensor.c02);
      postStr += "&field5=";
      postStr += String(sensor.windDirectiongradiant);
      postStr += "&field6=";
      postStr += String(sensor.rainTicks60m);
      postStr += "&field7=";
      postStr += String(sensor.rainTicks24h);
      postStr += "&field8=";
      postStr += String(sensor.windSpeed);
      postStr += "\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      //client.print("X-THINGSPEAKAPIKEY: " + String(ts_api_key) + "\n");
      client.print("X-THINGSPEAKAPIKEY: " + String(ts_api_key));
      //client.print(String("X-THINGSPEAKAPIKEY: ") + ts_api_key + "\n");
      //client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
#ifdef SerialMonitor
      Serial.println(postStr);
#endif
      delay(1000);
    }
    client.stop();
  }*/
  // Enviar datos a ThingSpeak
  ThingSpeak.setField(1, sensor.temperatureAHT); // Campo 1: Temperatura
  ThingSpeak.setField(2, sensor.humidity); // Campo 2: Humedad
  ThingSpeak.setField(3, sensor.barometricPressure);
  ThingSpeak.setField(4, sensor.c02);
  ThingSpeak.setField(5, sensor.windDirectiongradiant);
  ThingSpeak.setField(6, sensor.rainTicks60m);
  ThingSpeak.setField(7, sensor.rainTicks24h);
  ThingSpeak.setField(8, sensor.windSpeed);

  int x = ThingSpeak.writeFields(channelID, ts_api_key);
  if (x == 200) {
    Serial.println("Canal actualizado correctamente.");
  }
  else {
    Serial.print("Error al actualizar el canal. Código de error HTTP: ");
    Serial.println(x);
  }
}