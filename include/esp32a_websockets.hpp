/*
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
*/

// Función para manejar mensajes WebSocket
void onWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                        void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_DATA)
    {
        String message = String((char *)data).substring(0, len);
        Serial.printf("Mensaje recibido: %s\n", message.c_str());
    }
}

void setupwebsocket()
{
    ws.onEvent(onWebSocketMessage);
    server.addHandler(&ws);
}

// -------------------------------------------------------------------
// Función enviar JSON por Websocket 
// -------------------------------------------------------------------
void wsMessageSend(String msg, String icon, String Type){
	if(strcmp(Type.c_str(), "info") == 0){
		String response;
		DynamicJsonDocument doc(300);
		doc["type"] = Type;
		doc["msg"] = msg;
		doc["icon"] = icon;
		serializeJson(doc, response);
		ws.textAll(response);
	}else{
		ws.textAll(msg);
	}
}
// -------------------------------------------------------------------
// Empaquetar el JSON para enviar por WS Datos para Index cada 1s
// -------------------------------------------------------------------
// Función para enviar datos de los sensores a los clientes WebSocket
void sendSensorData()
{ // Loop
    String json = "{";
    json += "\"reboots\":" + String(device_restart) + ",";
    json += "\"cpuTemp\":" + String(temp_cpu) + ",";
    json += "\"activeTime\":" + longTimeStr(millis() / 1000) + ",";
    json += "\"ramAvailable\":" + String(ESP.getFreeHeap()) + ",";
    json += "\"RAM_SIZE_KB\":" + String(ESP.getHeapSize()) + ",";
    if (WiFi.status() == WL_CONNECTED)
    {
        json += "\"wifiStatus\":true,";
        json += "\"rssiStatus\":" + String(WiFi.RSSI()) + ",";
        json += "\"wifiQuality\":" + String(getRSSIasQuality(WiFi.RSSI())) + ",";
    }
    else
    {
        json += "\"wifiStatus\":false,";
        json += "\"rssiStatus\":0,";
        json += "\"wifiQuality\":0,";
    }

    json += "\"tempind\":" + String(sensor.temperatureAHT) + ",";
    json += "\"humedadin\":" + String(sensor.humidity) + ",";
    json += "\"presionad\":" + String(sensor.barometricPressure) + ",";
    json += "\"uvindex\":" + String(sensor.UVIndex) + ",";
    json += "\"windspeed\":" + String(sensor.windSpeed) + ",";
    json += "\"windspeedmax\":" + String(sensor.windSpeedMax) + ",";
    json += "\"luxind\":" + String(sensor.lux) + ",";
    json += "\"co2\":" + String(sensor.co2) + ",";
    json += "\"tvoc\":" + String(sensor.tvoc) + ",";
    json += "\"windDirectiongradient\":" + String(sensor.windDirectionGradient) + ",";
    json += "\"intervalrainfall\":" + String(rainData.intervalRainfall) + ",";

    json += "\"hourlycarryover\":" + String(rainData.hourlyCarryover);
    json += "}";
    ws.textAll(json);
}