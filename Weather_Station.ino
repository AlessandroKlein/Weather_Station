#include "defines.h"
#include "webs.h"

#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
//#include <DNSServer.h>
#include <ESPmDNS.h>  // Librería para mDNS

//#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>

#ifdef OTAWeb
// OTA
#include <Update.h>
#include <LittleFS.h>
#endif

#include <EEPROM.h>
#include "ThingSpeak.h"
#include <OneWire.h>
#include <Wire.h>
#include <stdlib.h>
#include <SPI.h>
/*
#include <esp_task_wdt.h>
#include <esp_system.h>
*/
#include <DallasTemperature.h>

#ifdef AHTX0BMP280
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
// Instancia para los sensores
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;
#endif

#ifdef BH1750
#include <BH1750.h>
BH1750 lightMeter;  // Crea una instancia del sensor BH1750
#endif

#ifdef CCS811
#include <Adafruit_CCS811.h>
Adafruit_CCS811 ccs;  // Crear una instancia del sensor CCS811
#endif

#include "style.h"
//===================================================
// Declaración de variables servidores
//===================================================
// Credenciales de ThingSpeak
const char* server3 = "api.thingspeak.com";
char ts_api_key[MAX_API_KEY_LENGTH + 1] = "";  // Thingspeak API Key
long unsigned int channelID;
char channelIDStr[20];  // Asegúrate de que el buffer sea lo suficientemente grande.
// Credenciales de weathercloud
const char* server2 = "api.weathercloud.net";
char ID2[MAX_API_KEY_LENGTH + 1] = "";   // Weathercloud.net ID
char Key2[MAX_API_KEY_LENGTH + 1] = "";  // Weathercloud.net Key
// Credenciales de windy
char server4[] = "stations.windy.com";
char serverurl[] = "/pws/station/";
char WINDYPAGE[MAX_API_KEY_LENGTH_WINDYPAGE + 1] = "";  // Windy API endpoint
int serverPort = 443;
// Credenciales de pwsweather
char server5[] = "pwsupdate.pwsweather.com";
char WEBPAGE5[] = "GET /api/v1/submitwx?";
char ID5[MAX_API_KEY_LENGTH + 1] = "";   // Pwsweather ID
char Key5[MAX_API_KEY_LENGTH + 1] = "";  // Pwsweather Key

//===================================================
// Variables para el control de servicios
//===================================================
bool weathercloud_enabled = false;
bool thingspeak_enabled = false;
bool windy_enabled = false;
bool pwsweather_enabled = false;

//===================================================
// Servidor web
//===================================================
//WebServer server(80);
AsyncWebServer server(80);

//===================================================
// WiFi
//===================================================
WiFiManager wifiManager;
WiFiClient client;
WiFiManager wm;

//===================================================
// Time
//===================================================
// Crear objetos necesarios para la conexión NTP
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", -10800, 7200);  // -10800 segundos para UTC-3, 3600 es el intervalo de actualización en segundos

// Variable para almacenar la hora
int hour, minute, second;

//===========================================
// Variables para la hora y temporizador
//===========================================
// Variables para la hora y temporizador
unsigned long previousMillis = 0;  // Para almacenar el último tiempo de actualización

//===================================================
// Setup
//===================================================
void setup() {
  Serial.begin(115200);

  // Convertir channelID a String
  sprintf(channelIDStr, "%lu", channelID);

  // Inicialización general
  printTitle();
  //title("Dispositivo: %s | Versión: %s", DEVICE_NAME, VERSION);
  definepin();
  readConfig();
  Wire.begin();

  // Conectar a Ethernet (o WiFi si es necesario)
  Ethernet();

  // Configuración de rutas del servidor web
  setupServer();

  // Iniciar el cliente NTP y configurar hora
  timeClient.begin();
  Time();

  // Inicializar sensores y dispositivos
  initializeSensors();

  // Configurar ThingSpeak
  ThingSpeak.begin(client);

  // Configuración MDNS
  MDNS.addService("http", "tcp", 80);

  // Mensaje de inicio
#ifdef SerialMonitor
  Serial.println("Servidor web iniciado\n");
#endif

#ifdef demo
  // Demo de lectura de sensores
  readSensors();
  sensordemoprint();

#ifdef SerialMonitor
  Serial.println("Datos demo actualizados");
#endif
#endif

#ifdef SerialMonitor
  Serial.println("Estación iniciada");
#endif
}

void setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", handleWebPage);
  });
  server.on("/get_data", HTTP_GET, handleGetDataRequest);
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", handleRoot.c_str(), processor);
  });

#ifdef OTAWeb
  server.on("/updateota", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", handleHomePageOTA);
  });
#endif

  server.on("/save", HTTP_POST, handleSave);
  server.on("/style.css", HTTP_GET, handleCSS);
  server.onNotFound(notFound);
  server.begin();
}

void initializeSensors() {
  sensorEnable();
  iniciodatos();
  setubahtbmp();
  setupBH1750();
  setupDS18B20();
}

//===================================================
// Loop
//===================================================
void loop() {
  // Comprobar si han pasado 5 minutos (300000 ms)
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Time();  // Actualizar la hora

#ifdef demo
    readSensors();  // Leer sensores en modo demo
#ifdef SerialMonitor
    Serial.println("Datos demo actualizados");
    sensordemoprint();  // Imprimir datos de demo
#endif
#else
      // Medir y procesar datos de sensores en modo normal
    measureWindSpeed();   // Medir velocidad del viento
    readWindDirection();  // Leer dirección del viento
    rainloop();           // Procesar lluvia
    loopahtbmp();         // Procesar sensor BMP
    loopBH1750();         // Procesar sensor BH1750
    loopS12SD();          // Procesar sensor S12SD
    loopDS18B20();        // Procesar sensor DS18B20
#endif

#ifdef SerialMonitor
    Serial.println("Datos actualizados");
#endif

    enviardatos();  // Enviar datos

#ifdef SerialMonitor
    Serial.println("Datos publicados");
#endif
  }

  // No usar delay; se puede realizar otras tareas mientras no han pasado los 5 minutos.
}
