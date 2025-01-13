//Hardware build target: ESP32
#define VERSION "0.0.1"

#include "defines.h"
#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <EEPROM.h>
#include <WebServer.h>
#include "ThingSpeak.h"
#include <DNSServer.h>
#include <OneWire.h>
#include <Wire.h>
#include <stdlib.h>
#include <SPI.h>
#include <ESPmDNS.h>  // Librería para mDNS
#include <esp_task_wdt.h>
#include <esp_system.h>
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
//===================================================
// Declaración de variables servidores
//===================================================
const char* server3 = "api.thingspeak.com";
char ts_api_key[34] = "";  // Thingspeak API Key
const char* server2 = "api.weathercloud.net";
char ID2[34] = "";   // Weathercloud.net ID
char Key2[34] = "";  // Weathercloud.net Key
char server4[] = "stations.windy.com";
char WINDYPAGE[256] = "";  // Windy API endpoint
char server5[] = "pwsupdate.pwsweather.com";
char WEBPAGE5[] = "GET /api/v1/submitwx?";
char ID5[34] = "";   // Pwsweather ID
char Key5[34] = "";  // Pwsweather Key

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
WebServer server(80);

//===================================================
// WiFi
//===================================================
WiFiManager wifiManager;

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

  printTitle();
  definepin();

  // Inicializar EEPROM y cargar valores guardados
  readConfig();
  Wire.begin();

  // Conectar automáticamente a WiFi
  Ethernet();
  //WiFiManager wifiManager;
  /*if (!wifiManager.autoConnect("ESP32_AP", "password123")) {
    Serial.println("Falló la conexión y expiró el tiempo de espera");
    ESP.restart();
  }

  Serial.println("Conectado a WiFi: " + WiFi.SSID());
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());*/

  // Configurar rutas del servidor web
  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);


  // Iniciar el servidor web
  server.begin();
  MonPrintf("Servidor web iniciado\n");

  // Iniciar el cliente NTP
  timeClient.begin();
  SetupTime();

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
  // Procesar solicitudes del servidor web
  server.handleClient();
  // Procesar WebSocket
  // Comprobar si han pasado 5 minutos (300000 ms)
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;
    Time();
    measureWindSpeed();  // Medir velocidad del viento
    readWindDirection();
    rainloop();
    loopahtbmp();
    loopBH1750();
    loopS12SD();
    loopDS18B20();

    enviardatos();
  }
}
