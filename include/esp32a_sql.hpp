#ifdef SQL
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);
const char* mqttServer = "mqtt.tudominio.com";
const int mqttPort = 1883;
const char* mqttUser = "usuario";
const char* mqttPassword = "contraseña";

void mqttReconnect() {
    while (!mqttClient.connected()) {
        if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
            mqttClient.publish("estacion/status", "connected");
        } else {
            delay(5000);
        }
    }
}

void publishSensorData() {
    StaticJsonDocument<512> doc;
    doc["temp"] = sensor.temperatureAHT;
    doc["humidity"] = sensor.humidity;
    doc["pressure"] = sensor.barometricPressure;
    // ... agregar todos los parámetros
    
    char buffer[512];
    serializeJson(doc, buffer);
    mqttClient.publish("estacion/sensores", buffer);
}
#endif