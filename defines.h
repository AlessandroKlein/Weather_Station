//Hardware build target: ESP32
#define VERSION "0.0.10"
const char* DEVICE_NAME = "VentoMeter";  // Definir el nombre del dispositivo

#define FACTORY "Silbito"


//===========================================
// Pin Defines
//===========================================
#define WIND_SPD_PIN 32  //Contador de anemómetro basado en interruptor de láminas
#define RAIN_PIN 25      //Contador de ticks basado en interruptor de láminas en el cubo de la punta
#define WIND_DIR_PIN 35  //Salida de divisor de voltaje variable basada en la variación de la red R con interruptores de láminas
//#define PR_PIN       15  //pin de fotoresistor
#define TEMP_PIN 4     //DS18B20 conectado al pin GPIO 4
#define LED_BUILTIN 2  //Diagnóstico mediante LED incorporado, se puede configurar en 12 para placas más nuevas que no usan zócalos devkit
//#define SENSOR_PWR   26
#define S12SD 34  //Sensor UV
#define MQ_7 13   //Sensor MQ7

//===========================================
//Enable Sensor
//===========================================
#define SerialMonitor
//#define demo
//#define BH1750Enable
//#define AHTX0BMP280
//#define BH1750
//#define CCS811
//#define heltec
//#define webSocket
//#define OTAWeb
//#define pruebas

//===========================================
//Anemometer Calibration
//===========================================
//I see 2 switch pulls to GND per revolation. Not sure what others see
#define WIND_TICKS_PER_REVOLUTION 2

//===========================================
// Dirección MAC del Ethernet ENC28J60 (puedes asignar cualquier valor único)
//===========================================
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//===========================================
// IP estática para el módulo Ethernet
//===========================================
IPAddress ip(172, 20, 15, 248);

//===========================================
// Variables para la hora y temporizador
//===========================================
// Variables para la hora y temporizador
const long interval = 300000;  // Intervalo de 5 minutos en milisegundos (300000 ms)
//const long interval = 180000;  // Intervalo de 3 minutos en milisegundos (180000 ms)
//const long interval = 90000;

//===========================================
// WH-SP-WS01
//===========================================
//#define WIND_FACTOR 2.4     // Factor para convertir pulsos a velocidad (km/h)

//===========================================
// Tamaño datos eeprom
//===========================================
#define MAX_API_KEY_LENGTH 33             // Definir el máximo de caracteres permitidos
#define MAX_API_KEY_LENGTH_WINDYPAGE 133  // Definir el máximo de caracteres permitidos

//===========================================
// Buffer Json
//===========================================
// Tamaño del buffer JSON. Ajusta según la cantidad de datos.
#define JSON_BUFFER_SIZE 1024  // Aumentar si es necesario