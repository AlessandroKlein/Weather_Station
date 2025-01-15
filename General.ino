//===========================================
// definepin: Defino los pines
//===========================================
void definepin() {
  //set hardware pins
  pinMode(WIND_SPD_PIN, INPUT_PULLUP);
  pinMode(RAIN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), contadorLitros, FALLING);  // Configura la interrupción
  pinMode(WIND_DIR_PIN, INPUT);                                               //Ver
  pinMode(S12SD, INPUT);
  pinMode(MQ_7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  digitalWrite(LED_BUILTIN, LOW);
}

//===========================================
// Estructura clima-ambiental
//===========================================
struct sensorData {
  int windDirectionADC;
  float windDirectiongradiant;
  int rainTicks24h;
  int rainTicks60m;
  float temperatureC;
  float temperatureAHT;
  float temperatureBMP;
  float windSpeed;
  float windSpeedMax;
  float barometricPressure;
  float humidity;
  float UVIndex;
  float lux;
  float c02;
  float tvoc;
};

//===========================================
// Estructura de inicialización del sensor
//===========================================
struct sensorStatus {
  int uv;
  int bme;
  int lightMeter;
  int temperature;
};

//===========================================
// Estructura de datos de precipitaciones
//===========================================
struct rainfallData {
  unsigned int intervalRainfall;         // Lluvia en el intervalo (hora actual)
  unsigned int hourlyRainfall[24];       // Lluvia por cada hora (24 horas)
  unsigned int current60MinRainfall[5];  // Lluvia de los últimos 60 minutos
  unsigned int hourlyCarryover;          // Lluvia acumulada de la hora pasada
  unsigned int priorHour;                // Lluvia de la hora anterior
  unsigned int minuteCarryover;          // Lluvia acumulada en el minuto actual
  unsigned int priorMinute;              // Lluvia del minuto anterior
};

//===========================================
// Instanciamos structure
//===========================================
sensorData sensor;  // Instanciamos la estructura
sensorStatus sensorStatusid;
rainfallData rainData;

// Crear configuración y rangos válidos
SensorConfig sensorConfig;
ValidRanges validRanges;

//===========================================
// iniciodatos: Inicio los datos
//===========================================
void iniciodatos() {
  // Inicializar valores en la estructura
  sensor.windSpeed = 0.0;
  sensor.windSpeedMax = 0.0;
  sensor.windDirectionADC = 0.0;
  sensor.rainTicks24h = 0.0;
  sensor.rainTicks60m = 0.0;
  sensor.temperatureC = 0.0;
  sensor.humidity = 0.0;
  sensor.UVIndex = 0.0;
  sensor.lux = 0.0;
}

//===================================================
// printTitle
//===================================================
void printTitle(void) {
  char buffer[32];
  Serial.printf("\n\n", String(DEVICE_NAME), "\n");
  Serial.printf("Version %s\n\n", VERSION);
}

//===========================================
// Título: Banner a la terminal
//===========================================
void title(const char* format, ...) {
  char buffer[200];
#ifdef SerialMonitor
  Serial.printf("==============================================\n");
  Serial.printf("%s\n", buffer);
  Serial.printf("==============================================\n");
#endif
}

//===========================================
// MonPrintf: impresión de diagnóstico a la terminal
//===========================================
void MonPrintf(const String& dato) {
#ifdef SerialMonitor
  Serial.print(dato);
#endif
}

//===========================================
// BlinkLED: Parpadea BUILTIN x veces
//===========================================
void BlinkLED(int count) {
  int x;
  //if reason code =0, then set count =1 (just so I can see something)
  if (!count) {
    count = 1;
  }
  for (x = 0; x < count; x++) {
    //LED ON
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    //LED OFF
    digitalWrite(LED_BUILTIN, LOW);
    delay(350);
  }
}

//===========================================
// Enviar datos y habilitar
//===========================================
void enviardatos() {
  if (WiFi.status() == WL_CONNECTED) {
    // Enviar datos a los servicios habilitados
    if (thingspeak_enabled) {
      // Código para enviar datos a ThingSpeak
      //ThingSpeak.writeField(channelNumber, field, ts_api_key);
      thingspeak();
      MonPrintf("Enviando datos a ThingSpeak\n");
    }

    if (weathercloud_enabled) {  //Revisar
      // Código para enviar datos a Weathercloud
      //String url = String("http://") + server2 + "/v1/update?ID=" + String(ID2) + "&KEY=" + String(Key2);
      weathercloud();
      MonPrintf("Enviando datos a Weathercloud\n");
      // Realiza la solicitud HTTP para enviar los datos
    }

    if (windy_enabled) {
      // Código para enviar datos a Windy
      //String url = String("http://") + String(WINDYPAGE);
      windy();
      MonPrintf("Enviando datos a Windy\n");
      // Realiza la solicitud HTTP para enviar los datos
    }

    if (pwsweather_enabled) {
      // Código para enviar datos a Pwsweather
      //String url = String("http://") + String(server5) + String(WEBPAGE5) + "?ID=" + String(ID5) + "&KEY=" + String(Key5);
      pws();
      MonPrintf("Enviando datos a Pwsweather\n");
      // Realiza la solicitud HTTP para enviar los datos
    }
  }
}

//===========================================
// Enviar datos y habilitar
//===========================================
void impdatos() {
#ifdef SerialMonitor
  Serial.print("Velocidad actual del viento: ");
  Serial.print(sensor.windSpeed);  // Imprimir velocidad en km/h
  Serial.println(" km/h");

  Serial.print("Velocidad máxima registrada: ");
  Serial.print(sensor.windSpeedMax);  // Imprimir velocidad máxima
  Serial.println(" km/h");
#endif
}