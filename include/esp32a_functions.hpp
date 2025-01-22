// -------------------------------------------------------------------
// DEFINICION DE FUNCIONES
// -------------------------------------------------------------------
void log(String type, String msg);
String platform();
float TempCPUValue();
String extractNumbers(String e);
String HexToStr(const unsigned long &h, const byte &l);
String UniqueID();
String DeviceID();
void contadorLitros();
void gpioDefine();
void settingsReset();
boolean settingsSave();

// -------------------------------------------------------------------
// Genera un log personalizado en el puerto Serial
// type: INFO, WARNING, DANGER
// msg: Mensaje
// -------------------------------------------------------------------
void log(String type, String msg){ // [INFO] demo
    Serial.println("[" + type + "] " + msg);
}

// -------------------------------------------------------------------
// Definir la Plataforma
// Optiene la plataforma de hardware
// -------------------------------------------------------------------
String platform(){
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}
// -------------------------------------------------------------------
// Sensor Temp Interno CPU
// -------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
// -------------------------------------------------------------------
// Retorna la temperatura del CPU
// -------------------------------------------------------------------
float TempCPUValue(){    
    return temp_cpu = (temprature_sens_read() - 32) / 1.8;
}

// -------------------------------------------------------------------
// Quitar numeros de la cadena
// -------------------------------------------------------------------
String extractNumbers(String e){
    String inputString = e;
    inputString.toLowerCase();
    String outString = "";
    int len = inputString.length();
    for (size_t i = 0; i < len; i++)
    {
        if (!isDigit((char)inputString[i]))
        {
            outString += (char)inputString[i];
        }       
    }
    return outString;
}
// -------------------------------------------------------------------
// De HEX a String
// -------------------------------------------------------------------
String HexToStr(const unsigned long &h, const byte &l){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}

// -------------------------------------------------------------------
// Crear un ID unico desde la direccion MAC
// Retorna los ultimos 4 Bytes del MAC rotados
// -------------------------------------------------------------------
String UniqueID(){    
    char uniqueid[15]; 
    uint64_t chipid = ESP.getEfuseMac();           
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(uniqueid, 15, "%04X", chip);
    return uniqueid;
}
// -------------------------------------------------------------------
// Número de serie del Dispositivo único => ESP329B1C52100C3D
// -------------------------------------------------------------------
String DeviceID(){
    return String(platform())+ HexToStr(ESP.getEfuseMac(),8) + String(UniqueID());
}
// -------------------------------------------------------------------
// Definir Pines GPIO
// -------------------------------------------------------------------
void gpioDefine(){
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
// -------------------------------------------------------------------
// Estructura para definir los servicios y sus configuraciones
// -------------------------------------------------------------------
struct ServiceConfig {
    const char* name;            // Nombre del servicio
    boolean* enabled;           // Puntero al flag de habilitación
    void (*sendData)();        // Función para enviar datos
};
// -------------------------------------------------------------------
// Declaración de las funciones de envío (asumiendo que están definidas en otro lugar)
// -------------------------------------------------------------------
void thingspeak();
void weathercloud();
void windy();
void pws();

void enviardatos() {
    if (WiFi.status() != WL_CONNECTED) {
        #ifdef SerialMonitor
        Serial.println("No hay conexión Wi-Fi\n");
        #endif
        return;
    }

    // Array de configuraciones de servicios
    static const ServiceConfig services[] = {
        {"ThingSpeak", &thingspeak_enabled, thingspeak},
        {"Weathercloud", &weathercloud_enabled, weathercloud},
        {"Windy", &windy_enabled, windy},
        {"Pwsweather", &pwsweather_enabled, pws}
    };

    const size_t numServices = sizeof(services) / sizeof(services[0]);

    // Iterar sobre todos los servicios
    for (size_t i = 0; i < numServices; i++) {
        if (*services[i].enabled) {
            services[i].sendData();
            #ifdef SerialMonitor
            Serial.println(String("Enviando datos a ") + services[i].name + "\n");
            #endif
        }
    }
}

// -------------------------------------------------------------------
// Retorna segundos como "d:hh:mm:ss"
// -------------------------------------------------------------------
String longTimeStr(const time_t &t){        
    String s = String(t / SECS_PER_DAY) + ':';
    if (hour(t) < 10)
    {
        s += '0';
    }
    s += String(hour(t)) + ':';
    if (minute(t) < 10)
    {
        s += '0';
    }
    s += String(minute(t)) + ':';
    if (second(t) < 10)
    {
        s += '0';
    }
    s += String(second(t));
    return s;
}

// -------------------------------------------------------------------
// Retorna la calidad de señal WIFI en % => 0 - 100%
// -------------------------------------------------------------------
int getRSSIasQuality(int RSSI){
    int quality = 0;
    if(RSSI <= -100){
        quality = 0;
    }else if (RSSI >= -50){
        quality = 100;
    }else{
       quality = 2 * (RSSI + 100);
    }
    return quality;
}