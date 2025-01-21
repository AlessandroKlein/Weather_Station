void thingspeak(void) {
  // Enviar datos a ThingSpeak
  ThingSpeak.setField(1, sensor.temperatureAHT);  // Campo 1: Temperatura
  ThingSpeak.setField(2, sensor.humidity);        // Campo 2: Humedad
  ThingSpeak.setField(3, sensor.barometricPressure);  // Campo 3: Presión barométrica
  ThingSpeak.setField(4, sensor.co2);                  // Campo 4: CO2
  ThingSpeak.setField(5, sensor.windDirectionGradient); // Campo 5: Dirección del viento en grados
  ThingSpeak.setField(6, sensor.rainTicks60m);         // Campo 6: Lluvia en los últimos 60 minutos
  ThingSpeak.setField(7, sensor.rainTicks24h);         // Campo 7: Lluvia en las últimas 24 horas
  ThingSpeak.setField(8, sensor.windSpeed);            // Campo 8: Velocidad del viento

  // Escribir los campos en ThingSpeak
  int x = ThingSpeak.writeFields(channelID, ts_api_key);

#ifdef SerialMonitor
  if (x == 200) {
    // Si el código HTTP es 200, la actualización fue exitosa
    Serial.println("Canal actualizado correctamente.");
  } else {
    // Si no, muestra el código de error HTTP
    Serial.print("Error al actualizar el canal. Código de error HTTP: ");
    Serial.println(x);
  }
#endif
}
