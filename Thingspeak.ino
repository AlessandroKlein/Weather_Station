void thingspeak(void) {
  // Enviar datos a ThingSpeak
  ThingSpeak.setField(1, sensor.temperatureAHT);  // Campo 1: Temperatura
  ThingSpeak.setField(2, sensor.humidity);        // Campo 2: Humedad
  ThingSpeak.setField(3, sensor.barometricPressure);
  ThingSpeak.setField(4, sensor.c02);
  ThingSpeak.setField(5, sensor.windDirectiongradiant);
  ThingSpeak.setField(6, sensor.rainTicks60m);
  ThingSpeak.setField(7, sensor.rainTicks24h);
  ThingSpeak.setField(8, sensor.windSpeed);

  int x = ThingSpeak.writeFields(channelID, ts_api_key);

#ifdef SerialMonitor
  if (x == 200) {
    Serial.println("Canal actualizado correctamente.");
  } else {
    Serial.print("Error al actualizar el canal. Código de error HTTP: ");
    Serial.println(x);
  }
#endif

}