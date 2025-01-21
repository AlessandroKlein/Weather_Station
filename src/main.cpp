#include <Arduino.h>

// Wifi
#include <WiFiManager.h>
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
// -------------------------------------------------------------------
// Configuración del sensor de temperatura DS18B20
// -------------------------------------------------------------------
/*OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);*/

// -------------------------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// -------------------------------------------------------------------
#include "esp32a_definitions_variables.hpp"
#include "esp32a_functions.hpp"
#include "esp32a_settings.hpp"
#include "esp32a_wifi.hpp"
#include "esp32a_wind.hpp"
#include "esp32a_rainfall.hpp"
#include "esp32a_sensor.hpp"
// Web
#include "esp32a_thingspeak.hpp"
#include "esp32a_weathercloud.hpp"
#include "esp32a_windy.hpp"
#include "esp32a_pws.hpp"


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

  // Conectar a Ethernet (o WiFi si es necesario)
  wifi_setup();

  // Iniciar el cliente NTP y configurar hora
  timeClient.begin();
  timeClient.update();

  // Configurar ThingSpeak
  ThingSpeak.begin(client);

  // Inicializar sensores y dispositivos
  initializeSensors();

#ifdef SerialMonitor
  Serial.println("Estación iniciada");
#endif
}

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
  measureWindSpeed();  // Medir velocidad del viento
  readWindDirection(); // Leer dirección del viento
  rainloop();          // Procesar lluvia
  loopahtbmp();        // Procesar sensor BMP
  loopBH1750();        // Procesar sensor BH1750
  loopS12SD();         // Procesar sensor S12SD
  loopDS18B20();       // Procesar sensor DS18B20
#endif

#ifdef SerialMonitor
  Serial.println("Datos actualizados");
#endif

  enviardatos(); // Enviar datos

#ifdef SerialMonitor
  Serial.println("Datos publicados");
#endif
  delay(10000);
}
