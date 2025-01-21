/* -------------------------------------------------------------------
 ;* AdminESP - ElectronicIOT 2023
 ;* Sitio WEB: https://electroniciot.com
 ;* Correo: admin@electroniciot.com
 ;* Cel_WSP: +591 71243395
 ;* Plataforma: ESP32
 ;* Framework:  Arduino - Platformio - VSC
 ;* Proyecto: Panel Administrativo para el ESP32 con JavaScript
 ;* Nombre: ESP32 Admin Tool v3
 ;* Autor: Ing. Yamir Hidalgo Peña
 ;* -------------------------------------------------------------------
;*/

WiFiManager wifiManager;
WiFiClient client;
WiFiManager wm;
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", -10800, 7200);  // -10800 segundos para UTC-3, 3600 es el intervalo de actualización en segundos

// e.j http://adminesp32.local
const char *esp_hostname = device_name;

// -------------------------------------------------------------------
// Declaración de funciones
// -------------------------------------------------------------------
void wifi_setup();

// -------------------------------------------------------------------
// Iniciar WIFI Modo Estación
// -------------------------------------------------------------------
void wifi_setup() {
    // Intentar conectar a WiFi
    if (!wifiManager.autoConnect(esp_hostname, "estacion1234"))
    {
#ifdef SerialMonitor
        Serial.println("Falló la conexión y expiró el tiempo de espera");
#endif
        ESP.restart(); // Reiniciar el dispositivo si no se conecta
    }

#ifdef SerialMonitor
    // Imprimir información sobre la conexión WiFi
    Serial.println("Conectado a WiFi: " + WiFi.SSID());
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
#endif

    // Inicializar mDNS para acceso local a través de .local
    if (MDNS.begin(esp_hostname))
    {
#ifdef SerialMonitor
        Serial.println("mDNS iniciado\n");
        Serial.printf("Accede a la página web de ESP32 en: http://%s.local/\n", DEVICE_NAME);
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