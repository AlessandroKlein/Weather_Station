//===========================================
// Pin Defines
//===========================================
#define WIND_SPD_PIN 32  //Contador de anemómetro basado en interruptor de láminas
#define RAIN_PIN     25  //Contador de ticks basado en interruptor de láminas en el cubo de la punta
#define WIND_DIR_PIN 35  //Salida de divisor de voltaje variable basada en la variación de la red R con interruptores de láminas
//#define PR_PIN       15  //pin de fotoresistor
#define TEMP_PIN      4  //DS18B20 conectado al pin GPIO 4
#define LED_BUILTIN   2  //Diagnóstico mediante LED incorporado, se puede configurar en 12 para placas más nuevas que no usan zócalos devkit
//#define SENSOR_PWR   26
#define S12SD        34  //Sensor UV
#define MQ_7         13  //Sensor MQ7

//===========================================
//Enable Sensor
//===========================================
#define SerialMonitor
//#define BH1750Enable
//#define AHTX0BMP280
//#define BH1750
//#define CCS811
//#define heltec

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

//===========================================
// WH-SP-WS01
//===========================================
#define WIND_FACTOR 2.4     // Factor para convertir pulsos a velocidad (km/h)