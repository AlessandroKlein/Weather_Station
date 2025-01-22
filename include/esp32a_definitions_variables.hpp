// -------------------------------------------------------------------
// Definiciones
// -------------------------------------------------------------------
#define WIND_SPD_PIN 32  //Contador de anemómetro basado en interruptor de láminas
#define RAIN_PIN 25      //Contador de ticks basado en interruptor de láminas en el cubo de la punta
#define WIND_DIR_PIN 35  //Salida de divisor de voltaje variable basada en la variación de la red R con interruptores de láminas
//#define PR_PIN       15  //pin de fotoresistor
#define TEMP_PIN 4     //DS18B20 conectado al pin GPIO 4
//#define LED_BUILTIN 2  //Diagnóstico mediante LED incorporado, se puede configurar en 12 para placas más nuevas que no usan zócalos devkit
//#define SENSOR_PWR   26
#define S12SD 34  //Sensor UV
#define MQ_7 13   //Sensor MQ7
// -------------------------------------------------------------------
// Hora
// -------------------------------------------------------------------
/*int hour;   // Variable para la hora
int minute; // Variable para el minuto*/

// -------------------------------------------------------------------
// CALCULAR LA CAPACIDAD DEL JSON
// Asistente ArduinoJson: https://arduinojson.org/v6/assistant/
// Documentación: https://arduinojson.org/v6/api/json/deserializejson/
// https://arduinojson.org/v6/doc/
// -------------------------------------------------------------------
const size_t capacitySettings = 1024*5;                 // 5KB
// -------------------------------------------------------------------
// Cantidad de caracteres permitidos en las api
// -------------------------------------------------------------------
#define MAX_API_KEY_LENGTH 34             // Definir el máximo de caracteres permitidos
#define MAX_API_KEY_LENGTH_WINDYPAGE 134  // Definir el máximo de caracteres permitidos
// -------------------------------------------------------------------
// Versión de Firmware desde las variables de entorno platformio.ini
// -------------------------------------------------------------------
#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)
String device_fw_version = ESCAPEQUOTE(BUILD_TAG);
// -------------------------------------------------------------------
// Version de Hardware y Fabricante
// -------------------------------------------------------------------
#define device_hw_version   "ADMINESP32 v1 00000000"    // Versión del hardware
#define device_manufacturer "IOTHOST"                   // Fabricante
// -------------------------------------------------------------------
// Zona configuración Dispositivo
// ------------------------------------------------------------------- 
char            device_id[30];                          // ID del dispositivo  
char            device_name[30];                        // Nombre del dispositivo
int             device_restart;                         // Número de reinicios 
char            device_user[15];                        // Usuario para acceso al servidor Web
char            device_password[15];                    // Contraseña del usuario servidor Web
// -------------------------------------------------------------------
// Zona Otras 
// -------------------------------------------------------------------
float           temp_cpu;                              // Temperatura del CPU en °C
// -------------------------------------------------------------------
// Declaración de variables servidor ThingSpeak
// -------------------------------------------------------------------
boolean thingspeak_enabled;
char ts_server[] = ""/* = "api.thingspeak.com"*/;
char ts_api_key[MAX_API_KEY_LENGTH] = "";  // Thingspeak API Key
long unsigned int channelID;
char channelIDStr[20];  // Asegúrate de que el buffer sea lo suficientemente grande.
// -------------------------------------------------------------------
// Declaración de variables servidor weathercloud
// -------------------------------------------------------------------
boolean weathercloud_enabled;
char wc_server[] = ""/* = "api.weathercloud.net"*/;
char wc_ID[MAX_API_KEY_LENGTH] = "";   // Weathercloud.net ID
char wc_Key[MAX_API_KEY_LENGTH] = "";  // Weathercloud.net Key
// -------------------------------------------------------------------
// Declaración de variables servidor windy
// -------------------------------------------------------------------
boolean windy_enabled;
char wy_server[] = ""/* = "stations.windy.com"*/;
char wy_serverurl[] = ""/* = "/pws/station/"*/;
char wy_WINDYPAGE[MAX_API_KEY_LENGTH_WINDYPAGE] = "";  // Windy API endpoint
int wy_serverPort;
// -------------------------------------------------------------------
// Declaración de variables servidor pwsweather
// -------------------------------------------------------------------
boolean pwsweather_enabled;
char pw_server[] = ""/* = "pwsupdate.pwsweather.com"*/;
char pw_WEBPAGE[] = ""/* = "GET /api/v1/submitwx?"*/;
char pw_I5[MAX_API_KEY_LENGTH] = "";   // Pwsweather ID
char pw_Key[MAX_API_KEY_LENGTH] = "";  // Pwsweather Key
// -------------------------------------------------------------------
// Tiempo de actualizacion
// -------------------------------------------------------------------
//const long interval = 300000;  // Intervalo de 5 minutos en milisegundos (300000 ms)
//const long interval = 180000;  // Intervalo de 3 minutos en milisegundos (180000 ms)
//const long interval = 90000;
const long interval = 10000;

// -------------------------------------------------------------------
// Zona EEPROM para contador de reinicios
// -------------------------------------------------------------------
#define Start_Address 0                                 // Posición de inicio en la EEPROM
#define Restart_Address Start_Address + sizeof(int)     // Dirección del dato en la EEPROM

// -------------------------------------------------------------------
// Estructura clima-ambiental
// -------------------------------------------------------------------
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

// -------------------------------------------------------------------
// Estructura de inicialización del sensor
// -------------------------------------------------------------------
struct sensorStatus {
  int uv;           // Estado del sensor UV (activo/inactivo)
  int bme;          // Estado del sensor BME (activo/inactivo)
  int lightMeter;   // Estado del sensor de luz (activo/inactivo)
  int temperature;  // Estado del sensor de temperatura (activo/inactivo)
};

// -------------------------------------------------------------------
// Estructura de datos de precipitaciones
// -------------------------------------------------------------------
struct rainfallData {
  unsigned int intervalRainfall;        // Lluvia en el intervalo actual (en mm)
  unsigned int hourlyRainfall[24];     // Lluvia por cada hora en las últimas 24 horas (arreglo de 24)
  unsigned int current60MinRainfall[5]; // Lluvia acumulada de los últimos 60 minutos, segmentada en 5 intervalos
  unsigned int hourlyCarryover;         // Lluvia acumulada de la hora anterior
  unsigned int priorHour;               // Lluvia de la hora anterior
  unsigned int minuteCarryover;         // Lluvia acumulada en el minuto actual
  unsigned int priorMinute;             // Lluvia del minuto anterior
};

// -------------------------------------------------------------------
// Instanciamos structure
// -------------------------------------------------------------------
sensorData sensor;         // Datos de los sensores
sensorStatus sensorStatusid; // Estado de los sensores
rainfallData rainData;     // Datos de lluvia

// -------------------------------------------------------------------
// Datos Eainfall
// -------------------------------------------------------------------
const int umbraltiempo = 300;  // Tiempo de umbral para evitar rebotes

volatile int ISRContador = 0;  // Contador de gotas
int contador = 0;
float litros = 0;
long tiempocontador = 0;
long tiempohora = 0;

// -------------------------------------------------------------------
// Zona Firmware
// ------------------------------------------------------------------- 
size_t content_len;
#define U_PART U_SPIFFS