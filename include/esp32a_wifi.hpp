#include "esp32a_ethernet.hpp"

WiFiManager wifiManager;
WiFiClient client;
WiFiManager wm;
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", -10800, 7200); // -10800 segundos para UTC-3, 3600 es el intervalo de actualización en segundos

// e.j http://adminesp32.local
const char *esp_hostname = device_name;
/*
W5500 -> ESP32
MOSI  -> GPIO23
MISO  -> GPIO19
SCK   -> GPIO18
CS    -> GPIO5  (configurable)
GND   -> GND
3.3V  -> 3.3V
*/
// -------------------------------------------------------------------
// Declaración de funciones
// -------------------------------------------------------------------
void wifi_setup();

// -------------------------------------------------------------------
// Estado de conexion
// -------------------------------------------------------------------
bool networkConnected() {
    return ethConnected() || (WiFi.status() == WL_CONNECTED);
}

// -------------------------------------------------------------------
// Iniciar WIFI Modo Estación
// -------------------------------------------------------------------
void wifi_setup()
{
    // Primero intentar conexión Ethernet
    ethSetup();
    delay(2000); // Tiempo para estabilizar

    if (ethConnected())
    {
#ifdef SerialMonitor
        Serial.println("Conectado por Ethernet!");
#endif
        return;
    }

// Fallback a WiFi si Ethernet falla
#ifdef SerialMonitor
    Serial.println("Falló Ethernet, intentando WiFi...");
#endif

    if (!wifiManager.autoConnect(esp_hostname, "estacion1234"))
    {
#ifdef SerialMonitor
        Serial.println("Falló la conexión y expiró el tiempo de espera");
#endif
        ESP.restart();
    }

#ifdef SerialMonitor
    Serial.println("Conectado a WiFi: " + WiFi.SSID());
    Serial.print("Dirección IP: ");
    if (ethConnected())
    {
        // Usar Ethernet
        IPAddress ip = Ethernet.localIP();
        // ...
    }
    else
    {
        // Usar WiFi
        IPAddress ip = WiFi.localIP();
        // ...
    }
#endif

    // Intentar conectar a WiFi
    /*if (!wifiManager.autoConnect(esp_hostname, "estacion1234"))
    {
#ifdef SerialMonitor
        Serial.println("Falló la conexión y expiró el tiempo de espera");
#endif
        ESP.restart(); // Reiniciar el dispositivo si no se conecta
    }*/

#ifdef SerialMonitor
    // Imprimir información sobre la conexión WiFi
    Serial.println("Conectado a WiFi: " + WiFi.SSID());
    Serial.print("Dirección IP: ");
    if (ethConnected())
    {
        // Usar Ethernet
        IPAddress ip = Ethernet.localIP();
        // ...
    }
    else
    {
        // Usar WiFi
        IPAddress ip = WiFi.localIP();
        // ...
    }
#endif

    // Inicializar mDNS para acceso local a través de .local
    if (MDNS.begin(esp_hostname))
    {
#ifdef SerialMonitor
        Serial.println("mDNS iniciado\n");
        Serial.printf("Accede a la página web de ESP32 en: http://%s.local/\n", esp_hostname);
        Serial.println();
#endif
    }
    else
    {
#ifdef SerialMonitor
        Serial.println("Error al iniciar mDNS\n");
#endif
    }
}