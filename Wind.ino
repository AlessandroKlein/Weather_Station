//=======================================================
// Variables utilizadas en el cálculo de la velocidad del viento (según ISR) (WH-SP-WS01)
//=======================================================
const int RECORD_TIME = 3;          // Tiempo de medición en segundos
volatile int interruptCounter = 0;  // Contador de interrupciones
float windSpeed;                    // Velocidad del viento

void IRAM_ATTR countPulses() {
  interruptCounter++;  // Incrementar el contador en cada interrupción
}

void measureWindSpeed() {
  interruptCounter = 0;                                                       // Reiniciar el contador
  attachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN), countPulses, RISING);  // Configurar interrupción
  delay(RECORD_TIME * 1000);                                                  // Medir durante RECORD_TIME segundos
  detachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN));                       // Desactivar interrupción

  // Calcular velocidad actual en km/h
  sensor.windSpeed = (float)interruptCounter / RECORD_TIME * 2.4;

  // Actualizar velocidad máxima si la actual es mayor
  if (sensor.windSpeed > sensor.windSpeedMax) {
    sensor.windSpeedMax = sensor.windSpeed;
  }
}

//=======================================================
//  readWindDirection: lee ADC para encontrar la dirección del viento (WH-SP-WD)
//=======================================================
String windDirectionText = "";

void readWindDirection() {
  sensor.windDirectionADC = analogRead(WIND_DIR_PIN);
  sensor.windDirectiongradiant = convertToDegrees(sensor.windDirectionADC);

  direccionweb(sensor.windDirectionADC);
#ifdef SerialMonitor
  // Imprime el valor del ADC
  Serial.print("ADC leído: ");
  Serial.println(sensor.windDirectionADC);

  
#endif
}

float convertToDegrees(int adcValue) {
  // Se ajustan los valores de ADC según los cálculos previos para cada dirección
  if ((745 < adcValue) && (adcValue < 825)) return 0.0;         // N o 0°
  if ((386 < adcValue) && (adcValue < 426)) return 22.5;        // NNE o 22.5°
  if ((442 < adcValue) && (adcValue < 483)) return 45.0;        // NE o 45°
  if ((74 < adcValue) && (adcValue < 94)) return 67.5;          // ENE o 67.5°
  if ((89 < adcValue) && (adcValue < 97)) return 90.0;          // E o 90°
  if ((60 < adcValue) && (adcValue < 70)) return 112.5;         // ESE o 112.5°
  if ((181 < adcValue) && (adcValue < 191)) return 135.0;       // SE o 135°
  if ((122 < adcValue) && (adcValue < 132)) return 157.5;       // SSE o 157.5°
  if ((278 < adcValue) && (adcValue < 298)) return 180.0;       // S o 180°
  if ((240 < adcValue) && (adcValue < 250)) return 202.5;       // SSO o 202.5°
  if ((615 < adcValue) && (adcValue < 645)) return 225.0;       // SO o 225°
  if ((583 < adcValue) && (adcValue < 613)) return 247.5;       // OSO o 247.5°
  if ((931 < adcValue) && (adcValue < 961)) return 270.0;       // O o 270°
  if ((813 < adcValue) && (adcValue < 843)) return 292.5;       // ONO o 292.5°
  if ((872 < adcValue) && (adcValue < 902)) return 315.0;       // NO o 315°
  if ((691 < adcValue) && (adcValue < 711)) return 337.5;       // NNO o 337.5°

  return -1.0; // Valor no válido, fuera de rango
}

float direccionweb(int adcValue) {
  if (adcValue >= 745 && adcValue <= 825)
    windDirectionText = "N o 0°"; // 0°
  else if (adcValue >= 386 && adcValue <= 426)
    windDirectionText = "NNE o 22.5°"; // 22.5°
  else if (adcValue >= 442 && adcValue <= 482)
    windDirectionText = "NE o 45°"; // 45°
  else if (adcValue >= 74 && adcValue <= 94)
    windDirectionText = "ENE o 67.5°"; // 67.5°
  else if (adcValue >= 89 && adcValue <= 97)
    windDirectionText = "E o 90°"; // 90°
  else if (adcValue >= 60 && adcValue <= 70)
    windDirectionText = "ESE o 112.5°"; // 112.5°
  else if (adcValue >= 181 && adcValue <= 191)
    windDirectionText = "SE o 135°"; // 135°
  else if (adcValue >= 122 && adcValue <= 132)
    windDirectionText = "SSE o 157.5°"; // 157.5°
  else if (adcValue >= 278 && adcValue <= 298)
    windDirectionText = "S o 180°"; // 180°
  else if (adcValue >= 240 && adcValue <= 250)
    windDirectionText = "SSO o 202.5°"; // 202.5°
  else if (adcValue >= 615 && adcValue <= 645)
    windDirectionText = "SO o 225°"; // 225°
  else if (adcValue >= 583 && adcValue <= 613)
    windDirectionText = "OSO o 247.5°"; // 247.5°
  else if (adcValue >= 931 && adcValue <= 961)
    windDirectionText = "O o 270°"; // 270°
  else if (adcValue >= 813 && adcValue <= 843)
    windDirectionText = "ONO o 292.5°"; // 292.5°
  else if (adcValue >= 872 && adcValue <= 902)
    windDirectionText = "NO o 315°"; // 315°
  else if (adcValue >= 691 && adcValue <= 711)
    windDirectionText = "NNO o 337.5°"; // 337.5°
  else
    windDirectionText = "Sin dirección válida detectada";
}
