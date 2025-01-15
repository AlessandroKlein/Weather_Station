//===========================================
//Time Setup
//===========================================
unsigned long lastUpdate = 0;
unsigned long updateInterval = 60000; // 1 minuto
String currentDateTime = "";

void Time() {
  // Solo actualizar la hora si ha pasado el intervalo de actualización
  if (millis() - lastUpdate >= updateInterval) {
    if (timeClient.update()) {
      hour = timeClient.getHours();
      minute = timeClient.getMinutes();
      second = timeClient.getSeconds();

      // Mostrar la hora en consola serial
      #ifdef SerialMonitor
        Serial.print("Hora actual: ");
        Serial.print(hour);
        Serial.print(":");
        Serial.print(minute);
        Serial.print(":");
        Serial.println(second);
      #endif

      lastUpdate = millis();  // Registrar el tiempo de la última actualización
    } else {
      #ifdef SerialMonitor
        Serial.println("Error al obtener la hora del servidor NTP");
      #endif
    }
  }
}

String getCurrentDateTimeUTC() {
  // Actualiza la hora solo cuando sea necesario
  if (millis() - lastUpdate >= updateInterval) {
    if (timeClient.update()) {
      unsigned long epochTime = timeClient.getEpochTime();
      char buffer[20];
      strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", gmtime((time_t *)&epochTime));
      currentDateTime = String(buffer);
      lastUpdate = millis();
    } else {
      #ifdef SerialMonitor
        Serial.println("Error al obtener la hora del servidor NTP");
      #endif
      currentDateTime = "";  // Si hubo un error, devolver una cadena vacía
    }
  }

  return currentDateTime;
}
