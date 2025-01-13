#include "defines.h"
#include "config.h"

#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <DNSServer.h>
#include <ESPmDNS.h>  // Librería para mDNS
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#ifdef webSocket
#include <WebSocketsServer.h>
#endif

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
//===================================================
// Declaración de variables servidores
//===================================================
// Credenciales de ThingSpeak
const char* server3 = "api.thingspeak.com";
char ts_api_key[MAX_API_KEY_LENGTH + 1] = "";  // Thingspeak API Key
unsigned long channelID = 2801433;
// Credenciales de weathercloud
const char* server2 = "api.weathercloud.net";
char ID2[MAX_API_KEY_LENGTH + 1] = "";   // Weathercloud.net ID
char Key2[MAX_API_KEY_LENGTH + 1] = "";  // Weathercloud.net Key
// Credenciales de windy
char server4[] = "stations.windy.com";
char WINDYPAGE[MAX_API_KEY_LENGTH_WINDYPAGE + 1] = "";  // Windy API endpoint
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
WebServer server(80);

#ifdef webSocket
WebSocketsServer webSocket = WebSocketsServer(81);  // WebSocket en el puerto 81
#endif

//===================================================
// WiFi
//===================================================
WiFiManager wifiManager;
WiFiClient client;

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
#ifdef webSocket
  server.on("/", handleWebPage);
  server.on("/sensor-data", handleSensorData);
  server.on("/config", handleRoot);
#else
  server.on("/", handleRoot);
#endif
  server.on("/save", HTTP_POST, handleSave);


  // Iniciar el servidor web
  server.begin();
  MonPrintf("Servidor web iniciado\n");

  // Iniciar el servidor WebSocket
#ifdef webSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);  // Maneja los eventos WebSocket
#endif

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
  thingspeak();
#ifdef SerialMonitor
    Serial.println("Datos demo actualizados");
#endif
#endif
#ifdef SerialMonitor
  Serial.println("Estacion iniciada");
#endif

}

//===================================================
// Loop
//===================================================
void loop() {
  // Procesar solicitudes del servidor web
  server.handleClient();
// Manejar las conexiones WebSocket
#ifdef webSocket
  webSocket.loop();
#endif

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

    // Convertir los datos a JSON y enviarlos a los clientes WebSocket conectados
#ifdef webSocket
    String jsonData = sensorDataToJson();
    webSocket.broadcastTXT(jsonData);  // Enviar el JSON a todos los clientes conectados
#endif
  }

  delay(5000);
}
