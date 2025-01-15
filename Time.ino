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

// Función para obtener la fecha y hora actual en formato YYYY-MM-DD HH:mm:ss UTC
String getCurrentDateTimeUTC() {
  if (!timeClient.update()) { // Actualiza solo si es necesario
    Serial.println("Error al obtener la hora del servidor NTP");
    return ""; // Devuelve una cadena vacía en caso de error
  }

  // Obtener el tiempo en segundos desde el epoch (1970-01-01 00:00:00 UTC)
  unsigned long epochTime = timeClient.getEpochTime();

  // Convertir el tiempo al formato requerido
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", gmtime((time_t *)&epochTime));

  return String(buffer);
}