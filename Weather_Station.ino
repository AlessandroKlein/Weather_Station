#include "defines.h"
#include "config.h"
#include "webs.h"

#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <DNSServer.h>
#include <ESPmDNS.h>  // Librería para mDNS

//#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>

#ifdef OTAWeb
// OTA
#include <Update.h>
#endif

//#include <LITTLEFS.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include "ThingSpeak.h"
#include <OneWire.h>
#include <Wire.h>
#include <stdlib.h>
#include <SPI.h>
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

#include "style.h"
//===================================================
// Declaración de variables servidores
//===================================================
// Credenciales de ThingSpeak
const char* server3 = "api.thingspeak.com";
char ts_api_key[MAX_API_KEY_LENGTH + 1] = "";  // Thingspeak API Key
long unsigned int channelID;
char channelIDStr[20]; // Asegúrate de que el buffer sea lo suficientemente grande.
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

  //nombre_red_stup();

  // Configurar rutas del servidor web
  //server.on("/", HTTP_GET, handleRoot);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", handleWebPage);
  });
  server.on("/get_data", HTTP_GET, handleGetDataRequest);
  //server.on("/config", HTTP_GET, handleRoot);
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", handleRoot.c_str(), processor);
  });


#ifdef OTAWeb
  server.on("/updateota", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", handleHomePageOTA);
  });
  //server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){request->send(200);}, handleUpdate);
#endif

   server.on("/save", HTTP_POST, handleSave);
  // Estilo css
  server.on("/style.css", HTTP_GET, handleCSS);

  // Pagina no funciona
  server.onNotFound(notFound);

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

  ThingSpeak.begin(client);

#ifdef demo
  readSensors();
  sensordemoprint();

#ifdef SerialMonitor
  Serial.println("Datos demo actualizados");
#endif
#endif
#ifdef SerialMonitor
  Serial.println("Estacion iniciada");
#endif
  //MDNS declaration
  MDNS.addService("http", "tcp", 80);
  //MDNS.addService("mqtt", "tcp", mqtt_port);

}

//===================================================
// Loop
//===================================================
void loop() {
  // Procesar solicitudes del servidor web
  //server.handleClient();
#ifdef pruebas

#else

  // Comprobar si han pasado 5 minutos (300000 ms)
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;
    Time();
#ifdef demo
    readSensors();
#ifdef SerialMonitor
    Serial.println("Datos demo actualizados");
    sensordemoprint();
#endif
#else
    measureWindSpeed();  // Medir velocidad del viento
    readWindDirection();
    rainloop();
    loopahtbmp();
    loopBH1750();
    loopS12SD();
    loopDS18B20();
#endif
#ifdef SerialMonitor
    Serial.println("Datos actualizados");
#endif

    //Leer sensores
    //SensorManager::SensorData data = sensorManager.readSensors();

    enviardatos();

#ifdef SerialMonitor
    Serial.println("Datos publicado");
#endif

  }
#endif

  delay(5000);
}
