//===========================================
// definepin: Defino los pines
//===========================================
void definepin() {
  // Configuración de pines
  pinMode(WIND_SPD_PIN, INPUT_PULLUP);  // Pin de velocidad del viento con pull-up interno
  pinMode(RAIN_PIN, INPUT);  // Pin de lluvia como entrada
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), contadorLitros, FALLING);  // Interrupción para contar litros de lluvia

  pinMode(WIND_DIR_PIN, INPUT);  // Pin de dirección del viento como entrada
  pinMode(S12SD, INPUT);  // Pin del sensor S12SD
  pinMode(MQ_7, INPUT);  // Pin del sensor MQ-7
  pinMode(LED_BUILTIN, OUTPUT);  // Pin del LED incorporado como salida

  // Apagar el LED incorporado por defecto
  digitalWrite(LED_BUILTIN, LOW);
}


//===========================================
// Estructura clima-ambiental
//===========================================
struct sensorData {
  int windDirectionADC;         // Dirección del viento en ADC
  float windDirectionGradient;  // Dirección del viento en grados
  int rainTicks24h;             // Total de ticks de lluvia en las últimas 24 horas
  int rainTicks60m;             // Total de ticks de lluvia en los últimos 60 minutos
  float temperatureC;           // Temperatura en °C (sensor específico)
  float temperatureAHT;         // Temperatura desde el sensor AHT
  float temperatureBMP;         // Temperatura desde el sensor BMP
  float windSpeed;              // Velocidad del viento en m/s
  float windSpeedMax;           // Velocidad máxima del viento en m/s
  float barometricPressure;     // Presión barométrica en hPa
  float humidity;               // Humedad relativa en %
  float UVIndex;                // Índice UV
  float lux;                    // Iluminancia en lux
  float co2;                    // Nivel de CO2 en ppm
  float tvoc;                   // Nivel de TVOC (compuestos orgánicos volátiles)
};

//===========================================
// Estructura de inicialización del sensor
//===========================================
struct sensorStatus {
  int uv;           // Estado del sensor UV (activo/inactivo)
  int bme;          // Estado del sensor BME (activo/inactivo)
  int lightMeter;   // Estado del sensor de luz (activo/inactivo)
  int temperature;  // Estado del sensor de temperatura (activo/inactivo)
};

//===========================================
// Estructura de datos de precipitaciones
//===========================================
struct rainfallData {
  unsigned int intervalRainfall;        // Lluvia en el intervalo actual (en mm)
  unsigned int hourlyRainfall[24];     // Lluvia por cada hora en las últimas 24 horas (arreglo de 24)
  unsigned int current60MinRainfall[5]; // Lluvia acumulada de los últimos 60 minutos, segmentada en 5 intervalos
  unsigned int hourlyCarryover;         // Lluvia acumulada de la hora anterior
  unsigned int priorHour;               // Lluvia de la hora anterior
  unsigned int minuteCarryover;         // Lluvia acumulada en el minuto actual
  unsigned int priorMinute;             // Lluvia del minuto anterior
};

//===========================================
// Instanciamos structure
//===========================================
sensorData sensor;         // Datos de los sensores
sensorStatus sensorStatusid; // Estado de los sensores
rainfallData rainData;     // Datos de lluvia

//===========================================
// iniciodatos: Inicio los datos
//===========================================
void iniciodatos() {
  // Inicializar todos los valores de la estructura a cero
  memset(&sensor, 0, sizeof(sensor));  // Esto establece todos los campos de 'sensor' a cero
}


//===================================================
// printTitle
//===================================================
void printTitle(void) {
  // Imprimir título y versión
  Serial.printf("\n\n%s\n", DEVICE_NAME);  // Imprimir el nombre del dispositivo
  Serial.printf("Version %s\n\n", VERSION);  // Imprimir la versión
}

//===========================================
// Título: Banner a la terminal
//===========================================
void title(const char* format, ...) {
  char buffer[200];  // Reservamos el espacio para la cadena formateada

  // Iniciar la lista de argumentos variables
  va_list args;
  va_start(args, format);

  // Formatear la cadena en el buffer
  vsnprintf(buffer, sizeof(buffer), format, args);

  // Finalizar la lista de argumentos
  va_end(args);

#ifdef SerialMonitor
  // Imprimir el título formateado entre líneas
  Serial.printf("==============================================\n");
  Serial.printf("%s\n", buffer);
  Serial.printf("==============================================\n");
#endif
}

//===========================================
// BlinkLED: Parpadea BUILTIN x veces
//===========================================
void BlinkLED(int count) {
  static unsigned long previousMillis = 0;
  static int ledState = LOW;
  static int blinkCount = 0;

  if (count <= 0) count = 1;  // Asegura que al menos parpadee una vez

  unsigned long currentMillis = millis();
  
  if (blinkCount < count) {
    // Cambiar el estado del LED si ha pasado suficiente tiempo
    if (currentMillis - previousMillis >= (ledState == HIGH ? 150 : 350)) {
      previousMillis = currentMillis;
      ledState = (ledState == HIGH) ? LOW : HIGH;  // Cambiar el estado del LED
      digitalWrite(LED_BUILTIN, ledState);
      
      // Si el LED se apaga, contar un parpadeo
      if (ledState == LOW) {
        blinkCount++;
      }
    }
  } else {
    // Reiniciar el contador cuando ya se haya parpadeado el número de veces deseado
    blinkCount = 0;
    digitalWrite(LED_BUILTIN, LOW);  // Asegura que el LED quede apagado al final
  }
}

//===========================================
// Enviar datos y habilitar
//===========================================
void enviardatos() {
  if (WiFi.status() != WL_CONNECTED) {
    #ifdef SerialMonitor
    Serial.println("No hay conexión Wi-Fi\n");
    #endif
    return;
  }

  // Enviar datos a los servicios habilitados
  if (thingspeak_enabled) {
    thingspeak();
    #ifdef SerialMonitor
    printServiceStatus("ThingSpeak");
    #endif
  }

  if (weathercloud_enabled) {
    weathercloud();
    #ifdef SerialMonitor
    printServiceStatus("Weathercloud");
    #endif
  }

  if (windy_enabled) {
    windy();
    #ifdef SerialMonitor
    printServiceStatus("Windy");
    #endif
  }

  if (pwsweather_enabled) {
    pws();
    #ifdef SerialMonitor
    printServiceStatus("Pwsweather");
    #endif
  }
}

// Función para manejar la impresión de los mensajes de estado
#ifdef SerialMonitor
void printServiceStatus(const char* service) {
  Serial.println(String("Enviando datos a ") + service + "\n"); 
}
#endif
//===========================================
// Enviar datos y habilitar
//===========================================
void impdatos() {
  // Si el monitoreo por serial está habilitado
#ifdef SerialMonitor
  Serial.println("Velocidad actual del viento: " + String(sensor.windSpeed) + " km/h");
  Serial.println("Velocidad máxima registrada: " + String(sensor.windSpeedMax) + " km/h");
#endif
}
