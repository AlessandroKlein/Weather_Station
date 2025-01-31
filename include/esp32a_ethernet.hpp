#include <SPI.h>
//#include <ETH.h>
#include <Ethernet.h>

// Configuración W5500
#define ETH_CS_PIN 5  // Pin Chip Select (CS) para W5500 - ajustar según hardware
#define ETH_SPI_SPEED 14000000  // Velocidad SPI (14MHz)

// Dirección MAC - Puede ser cualquiera (debe ser única en la red)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void ethSetup() {
    SPI.begin();
    Ethernet.init(ETH_CS_PIN);  // Inicializar SPI con pin CS
    
    #ifdef SerialMonitor
    Serial.println("Iniciando Ethernet con W5500...");
    #endif

    Ethernet.begin(mac);  // Usar DHCP
    
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        #ifdef SerialMonitor
        Serial.println("Error: No se detectó el módulo Ethernet!");
        #endif
        return;
    }
    
    if (Ethernet.linkStatus() == LinkOFF) {
        #ifdef SerialMonitor
        Serial.println("Cable Ethernet no conectado!");
        #endif
    }

    #ifdef SerialMonitor
    Serial.print("Dirección IP: ");
    Serial.println(Ethernet.localIP());
    Serial.print("Máscara de subred: ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("DNS: ");
    Serial.println(Ethernet.dnsServerIP());
    #endif
}

bool ethConnected() {
    return Ethernet.linkStatus() == LinkON && 
           Ethernet.hardwareStatus() != EthernetNoHardware;
}