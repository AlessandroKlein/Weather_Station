// -------------------------------------------------------------------
// Variables utilizadas en el cálculo de la velocidad del viento
// -------------------------------------------------------------------
const int RECORD_TIME = 3;          // Tiempo de medición en segundos
volatile int interruptCounter = 0;  // Contador de interrupciones
float windSpeed;                    // Velocidad del viento

void IRAM_ATTR countPulses() {
  interruptCounter++;  // Incrementar el contador en cada interrupción
}

void measureWindSpeed() {
  interruptCounter = 0;                                                       // Reiniciar el contador
  attachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN), countPulses, RISING);  // Configurar interrupción

  // Medir durante RECORD_TIME segundos sin usar delay
  unsigned long startMillis = millis();
  while (millis() - startMillis < RECORD_TIME * 1000) {
    // Esperar hasta que pase el tiempo de medición
  }

  detachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN));                       // Desactivar interrupción

  // Calcular velocidad actual en km/h
  sensor.windSpeed = (float)interruptCounter / RECORD_TIME * 2.4;

  // Actualizar velocidad máxima si la actual es mayor
  if (sensor.windSpeed > sensor.windSpeedMax) {
    sensor.windSpeedMax = sensor.windSpeed;
  }
}

// -------------------------------------------------------------------
//  readWindDirection: lee ADC para encontrar la dirección del viento
// -------------------------------------------------------------------
String windDirectionText = "";

float convertToDegrees(int adcValue) {
  // Se ajustan los valores de ADC según los cálculos previos para cada dirección
  if (adcValue < 100) return 0.0;           // N o 0°
  if (adcValue < 200) return 45.0;          // NE o 45°
  if (adcValue < 300) return 90.0;          // E o 90°
  if (adcValue < 400) return 135.0;         // SE o 135°
  if (adcValue < 500) return 180.0;         // S o 180°
  if (adcValue < 600) return 225.0;         // SO o 225°
  if (adcValue < 700) return 270.0;         // O o 270°
  if (adcValue < 800) return 315.0;         // NO o 315°
  return 360.0;                            // NNO o 337.5°
}

String direccionweb(int adcValue) {
  if (adcValue < 100) windDirectionText = "N o 0°"; // 0°
  else if (adcValue < 200) windDirectionText = "NE o 45°"; // 45°
  else if (adcValue < 300) windDirectionText = "E o 90°"; // 90°
  else if (adcValue < 400) windDirectionText = "SE o 135°"; // 135°
  else if (adcValue < 500) windDirectionText = "S o 180°"; // 180°
  else if (adcValue < 600) windDirectionText = "SO o 225°"; // 225°
  else if (adcValue < 700) windDirectionText = "O o 270°"; // 270°
  else if (adcValue < 800) windDirectionText = "NO o 315°"; // 315°
  else windDirectionText = "NNO o 337.5°"; // 337.5°
  
  return windDirectionText; // Retornar el texto para usarlo en la interfaz web o en otros lugares
}

void readWindDirection() {
  sensor.windDirectionADC = analogRead(WIND_DIR_PIN);
  sensor.windDirectionGradient = convertToDegrees(sensor.windDirectionADC);

  direccionweb(sensor.windDirectionADC);
#ifdef SerialMonitor
  // Imprime el valor del ADC
  Serial.print("ADC leído: ");
  Serial.println(sensor.windDirectionADC);
#endif
}