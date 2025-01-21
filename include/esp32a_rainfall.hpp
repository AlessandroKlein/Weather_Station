void contadorLitros()
{
  // Asegura que solo se cuenten interrupciones después del umbral de tiempo
  if (millis() > (tiempocontador + umbraltiempo))
  {
    ISRContador++;             // Aumenta el contador de gotas
    tiempocontador = millis(); // Actualiza el tiempo del contador
#ifdef SerialMonitor
    Serial.println(ISRContador); // Muestra el número de gotas detectadas
#endif
  }
}

void rainloop()
{
  unsigned long currentMillis = millis(); // Mejor práctica para evitar "millis() overflow" en cálculos repetitivos

  // Si ha pasado una hora (cada 3600 segundos)
  if (currentMillis - tiempohora >= 3600000UL)
  {
    // Guarda la lluvia caída en la hora actual
    rainData.intervalRainfall = ISRContador * 0.27945; // Calcular los milímetros de lluvia en la hora (ajustar el factor según el sensor)

    // Actualiza el total de lluvia por hora
    // Desplaza las lluvias de las horas anteriores y añade la lluvia de esta hora
    for (int i = 23; i > 0; i--)
    {
      rainData.hourlyRainfall[i] = rainData.hourlyRainfall[i - 1];
    }
    rainData.hourlyRainfall[0] = rainData.intervalRainfall; // La lluvia más reciente se almacena en la primera posición

    // Calcula la lluvia acumulada por hora (si supera el umbral de tiempo)
    rainData.hourlyCarryover = rainData.intervalRainfall + rainData.priorHour;

    // Actualiza el total de lluvia de la hora previa
    rainData.priorHour = rainData.intervalRainfall;

    sensor.rainTicks24h = ISRContador * 0.27945;            // Los ticks de lluvia en las últimas 24 horas
    sensor.rainTicks60m = rainData.current60MinRainfall[4]; // Los ticks de lluvia de los últimos 60 minutos

    // Muestra la lluvia de la hora y del día
#ifdef SerialMonitor
    Serial.print("Lluvia en esta hora (mm): ");
    Serial.println(rainData.intervalRainfall);
    Serial.print("Lluvia total del día (mm): ");
    Serial.println(rainData.hourlyCarryover);
#endif

    // Resetea el contador de gotas y los valores de lluvia por hora
    ISRContador = 0;
    rainData.intervalRainfall = 0;
    tiempohora = currentMillis; // Reinicia el tiempo de la hora
  }

  // Si ha pasado un minuto (60 segundos)
  if (currentMillis - tiempocontador >= 60000UL)
  {
    // Actualiza la lluvia de los últimos 60 minutos
    for (int i = 4; i > 0; i--)
    {
      rainData.current60MinRainfall[i] = rainData.current60MinRainfall[i - 1];
    }
    rainData.current60MinRainfall[0] = rainData.intervalRainfall;

    // Actualiza la lluvia acumulada por minuto
    rainData.minuteCarryover = rainData.intervalRainfall + rainData.priorMinute;

    // Actualiza la lluvia del minuto anterior
    rainData.priorMinute = rainData.intervalRainfall;

    tiempocontador = currentMillis; // Reinicia el tiempo del contador del minuto
  }

  // Reinicia los datos a las 00:09 (medianoche)
  if (0 == timeClient.getHours() && 9 >= timeClient.getMinutes())
  { // Solo reinicia a medianoche
    // Resetea todos los valores a medianoche
    for (int i = 0; i < 24; i++)
    {
      rainData.hourlyRainfall[i] = 0; // Resetea lluvia por hora
    }
    rainData.intervalRainfall = 0;
    rainData.hourlyCarryover = 0;
    rainData.priorHour = 0;
    rainData.minuteCarryover = 0;
    rainData.priorMinute = 0;

#ifdef SerialMonitor
    Serial.println("Datos reiniciados a medianoche.");
#endif
  }
}