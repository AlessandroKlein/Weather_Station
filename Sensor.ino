// Crear objeto OneWire
OneWire oneWire(TEMP_PIN);
// Pasar la referencia del bus OneWire al objeto DallasTemperature
DallasTemperature temperatureSensor(&oneWire);

extern "C" {
  uint8_t temprature_sens_read();
}

//===========================================
//DS18B20
//===========================================
void sensorEnable() {
#ifdef heltec
  Wire.begin(21, 22);
  Wire.available();  // Detecta si hay datos pendientes por ser leídos
#else
  Wire.begin();
#endif
}

void setupDS18B20() {
  temperatureSensor.begin();  // Iniciar el sensor DS18B20
#ifdef SerialMonitor
  Serial.println("Iniciando DS18B20...");
#endif
}

void loopDS18B20() {
  // Solicitar la lectura de las temperaturas
  temperatureSensor.requestTemperatures();

  // Obtener la temperatura en grados Celsius
  sensor.temperatureC = temperatureSensor.getTempCByIndex(0);  // 0 es el primer sensor
#ifdef SerialMonitor
  if (sensor.temperatureC != DEVICE_DISCONNECTED_C) {
    // Si el sensor está conectado, imprimir la temperatura
    Serial.print("Temperatura: ");
    Serial.print(sensor.temperatureC);
    Serial.println(" °C");
  } else {
    // Si no se puede leer la temperatura
    Serial.println("Error al leer el sensor DS18B20");
  }
#endif
}

//===========================================
//AHT20 + BMP280
//===========================================
void setubahtbmp() {
#ifdef AHTX0BMP280
  // Inicializa el sensor AHT20
  if (!aht.begin()) {
#ifdef SerialMonitor
    Serial.println("Error: No se pudo encontrar el sensor AHT20");
#endif
    while (1)
      ;
  }
#ifdef SerialMonitor
  Serial.println("Sensor AHT20 inicializado");
#endif

  // Inicializa el sensor BMP280
  if (!bmp.begin(0x76)) {  // Dirección I2C del BMP280
#ifdef SerialMonitor
    Serial.println("Error: No se pudo encontrar el sensor BMP280");
#endif
    while (1)
      ;
  }
#ifdef SerialMonitor
  Serial.println("Sensor BMP280 inicializado");
#endif
#endif
}

void loopahtbmp() {
#ifdef AHTX0BMP280
  // Leer datos del sensor AHT20
  sensors_event_t humidityEvent, tempEvent;
  aht.getEvent(&humidityEvent, &tempEvent);
  sensor.temperatureAHT = tempEvent.temperature;
  sensor.humidity = humidityEvent.relative_humidity;

  // Leer datos del sensor BMP280
  sensor.temperatureBMP = bmp.readTemperature();
  sensor.barometricPressure = bmp.readPressure() / 100.0F;  // Convierte a hPa
#ifdef SerialMonitor
  // Mostrar los datos en el Serial Monitor
  Serial.println("==== Datos del sensor ====");
  Serial.print("Temperatura (AHT20): ");
  Serial.print(sensor.temperatureAHT);
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(sensor.humidity);
  Serial.println(" %");

  Serial.print("Temperatura (BMP280): ");
  Serial.print(sensor.temperatureBMP);
  Serial.println(" °C");

  Serial.print("Presión: ");
  Serial.print(sensor.barometricPressure);
  Serial.println(" hPa");
  Serial.println("==========================");
#endif
#endif
}

//===========================================
//BH1750
//===========================================
void setupBH1750() {
#ifdef BH1750
  lightMeter.begin();  // Inicia el sensor BH1750
#endif
}

void loopBH1750() {
#ifdef BH1750
  sensor.lux = lightMeter.readLightLevel();  // Lee el valor de la luz en lux
#ifdef SerialMonitor
  if (lux != 0.0) {
    Serial.print("Intensidad de luz: ");
    Serial.print(sensor.lux);
    Serial.println(" lux");
  } else {
    Serial.println("No se pudo leer el sensor.");
  }
#endif
#endif
}

//===========================================
//CCS811
//===========================================
void setupCCS81189() {
#ifdef CCS811
  // Inicializa el sensor CCS811
  if (!ccs.begin()) {
#ifdef SerialMonitor
    Serial.println("No se pudo encontrar el sensor CCS811");
#endif
    while (1)
      ;
  }
#ifdef SerialMonitor
  Serial.println("Sensor CCS811 listo para leer datos.");
#endif
#endif
}

void loopCCS811() {
#ifdef CCS811
  / Verifica si el sensor está listo para dar datos if (ccs.available()) {
    if (!ccs.readData()) {  // Lee los datos del sensor
      // Lee el CO2 en ppm
      sensor.co2 = ccs.geteCO2();
      // Lee el valor de VOCs (en ppb)
      sensor.tvoc = ccs.getTVOC();

#ifdef SerialMonitor
      // Imprime los valores en el monitor serial
      Serial.print("CO2: ");
      Serial.print(sensor.co2);
      Serial.print(" ppm\t");

      Serial.print("TVOC: ");
      Serial.print(sensor.tvoc);
      Serial.println(" ppb");
#endif

      // Aquí puedes guardar los valores en tus estructuras o variables
    } else {
#ifdef SerialMonitor
      Serial.println("Error al leer datos del sensor.");
#endif
    }
  }
#endif
}

//===========================================
//S12SD
//===========================================
void loopS12SD() {
  // Lee el valor ADC del sensor conectado al pin 34
  int uvValue = analogRead(S12SD);

  // Convertir el valor ADC a índice UV
  sensor.UVIndex = convertToUVIndex(uvValue);

#ifdef SerialMonitor
  // Imprimir el valor de la radiación UV y el índice UV
  Serial.print("Valor ADC: ");
  Serial.print(uvValue);
  Serial.print("\tUV Index: ");
  Serial.println(sensor.UVIndex);
#endif
}

float convertToUVIndex(int adcValue) {
  // Convertir ADC a mV
  float voltage = (adcValue / 4095.0) * 3300;

  // Mapear el valor de mV al índice UV según la escala proporcionada
  if (voltage < 50) return 0;
  else if (voltage >= 50 && voltage < 227) return 1;
  else if (voltage >= 227 && voltage < 318) return 2;
  else if (voltage >= 318 && voltage < 408) return 3;
  else if (voltage >= 408 && voltage < 503) return 4;
  else if (voltage >= 503 && voltage < 606) return 5;
  else if (voltage >= 606 && voltage < 696) return 6;
  else if (voltage >= 696 && voltage < 795) return 7;
  else if (voltage >= 795 && voltage < 881) return 8;
  else if (voltage >= 881 && voltage < 976) return 9;
  else if (voltage >= 976 && voltage < 1079) return 10;
  else if (voltage >= 1079) return 11;

  return -1;  // Valor no válido
}