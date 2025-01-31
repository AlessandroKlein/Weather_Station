// #define webactivation
#define SerialMonitor

#include <Arduino.h>

// Wifi
#include <WiFiManager.h>
#include <ETH.h>
#include <WIFI.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <DNSServer.h>

// Time
#include <NTPClient.h>

// Enviar datos
#include <HTTPClient.h>
#include "ThingSpeak.h"

// Arduino
#include <stdlib.h>
#include <EEPROM.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

// Comunicaion
#include <SPI.h>
#include <Wire.h>

// Sensores
#include <OneWire.h>
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
BH1750 lightMeter; // Crea una instancia del sensor BH1750
#endif

#ifdef CCS811
#include <Adafruit_CCS811.h>
Adafruit_CCS811 ccs; // Crear una instancia del sensor CCS811
#endif
#ifdef DEEP_SLEEPoffon
#include <esp_sleep.h> // Para funciones de sueño
#endif
// -------------------------------------------------------------------
// Configuración del sensor de temperatura DS18B20
// -------------------------------------------------------------------
/*OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);*/

// -------------------------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// -------------------------------------------------------------------
#include "esp32a_definitions_variables.hpp"
#include "esp32a_wifi.hpp"
#include "esp32a_functions.hpp"
#include "esp32a_settings.hpp"
#include "esp32a_server.hpp"
// #include "esp32a_web.hpp"
#include "esp32a_websockets.hpp"

// otros Sensores
#include "esp32a_wind.hpp"
#include "esp32a_rainfall.hpp"
#include "esp32a_sensor.hpp"
// Web
#include "esp32a_thingspeak.hpp"
#include "esp32a_weathercloud.hpp"
#include "esp32a_windy.hpp"
#include "esp32a_pws.hpp"

#include "esp32a_environmental.hpp"
#include "esp32a_sql.hpp"

// #include "esp32a_task.hpp"

// -------------------------------------------------------------------
// DeepSleep
// -------------------------------------------------------------------
/*void enterDeepSleep()
{
#ifdef DEEP_SLEEPoffon
  Serial.println("Entrando en Deep Sleep");

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_25, 0);
  // esp_sleep_enable_ext0_wakeup((gpio_num_t)RAIN_PIN, 0);

  esp_sleep_enable_timer_wakeup(interval * 1000);
  esp_deep_sleep_start();
#endif
}*/

void enterDeepSleep()
{
#ifdef DEEP_SLEEPoffon
  Serial.println("Entrando en Deep Sleep");

  // Configurar el sensor para despertar al detectar lluvia
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_25, 0); // Pin 25, nivel bajo

  // Configurar el timer para despertar después de `interval` segundos
  esp_sleep_enable_timer_wakeup(interval * 1000);

  // Iniciar Deep Sleep
  esp_deep_sleep_start();
#endif
}

// -------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(256);                           // Memoria EEPROM init 256 bytes
  EEPROM.get(Restart_Address, device_restart); // Leer el valor de la memoria
  device_restart++;                            // Aumentar el contador
  EEPROM.put(Restart_Address, device_restart); // Guardar el valor a la memoria
  EEPROM.commit();
  EEPROM.end();

  // traer las configuraciones desde json
  if (!settingsRead())
  {
    settingsSave();
  }

  // definir los pines y setearlos
  gpioDefine();

  Wire.begin();

  SPI.begin();

  // Conectar a Ethernet (o WiFi si es necesario)
  wifi_setup();

  // Iniciar el cliente NTP y configurar hora
  timeClient.begin();
  timeClient.update();
  // inicializar el servidor
  initServer();

  // iniciar el websockets
  setupwebsocket();

  // Configurar ThingSpeak
  ThingSpeak.begin(client);

  // Inicializar sensores y dispositivos
  initializeSensors();
  initWindSensors();

#ifdef SerialMonitor
  Serial.println("Estación iniciada");
#endif
  // xTaskCreate(TaskWsSend, "TaskWsSend", 2048, NULL, 1, NULL);

#ifdef DEEP_SLEEPoffon
  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER)
  {
    // Primera ejecución
  }
#endif
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), contadorLitros, FALLING);
}

// -------------------------------------------------------------------
// Loop
// -------------------------------------------------------------------
void loop()
{
  timeClient.update(); // Actualizar la hora

#ifdef demo
  readSensors(); // Leer sensores en modo demo
#ifdef SerialMonitor
  Serial.println("Datos demo actualizados");
  sensordemoprint(); // Imprimir datos de demo
#endif
#else
                       // Medir y procesar datos de sensores en modo normal
  updateWindSensors();
  rainloop(); // Procesar lluvia

  loopSensors();

  updateCalculations();
#endif

#ifdef SerialMonitor
  Serial.println("Datos actualizados");
#endif

  enviardatos(); // Enviar datos

#ifdef SerialMonitor
  Serial.println("Datos publicados");
#endif
#ifdef webactivation
  sendSensorData();
#endif

#ifdef DEEP_SLEEPoffon
  if (rainData.intervalRainfall > 0)
  {
    enterDeepSleep(); // Entrar en Deep Sleep si ha llovido
  }
  else
  {
    delay(1000); // Esperar 1 segundo antes de verificar nuevamente
  }

/*
#ifdef DEEP_SLEEPoffon
  enterDeepSleep();*/
#else
  delay(interval);
#endif
}
