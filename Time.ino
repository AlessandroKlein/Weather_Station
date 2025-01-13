//===========================================
//Time Setup
//===========================================
void SetupTime() {
  // Actualizar la hora desde el servidor NTP
  timeClient.update();

  // Obtener la hora, minuto y segundo
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
}

//===========================================
//Time Loop
//===========================================
void Time() {
  // Actualizar la hora desde el servidor NTP
  timeClient.update();

  // Obtener la hora, minuto y segundo
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
}