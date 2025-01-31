String getSensorDataJSON() {
    // Crear documento JSON
    JsonDocument doc;

    // Agregar datos principales
    JsonObject sensorData = doc["sensorData"].to<JsonObject>();
    sensorData["windDirectionADC"] = sensor.windDirectionADC;
    sensorData["windDirection"] = sensor.windDirectionGradient;
    sensorData["temperatureC"] = sensor.temperatureC;
    sensorData["temperatureAHT"] = sensor.temperatureAHT;
    sensorData["temperatureBMP"] = sensor.temperatureBMP;
    sensorData["windSpeed"] = sensor.windSpeed;
    sensorData["windGust"] = sensor.windSpeedMax;
    sensorData["pressure"] = sensor.barometricPressure;
    sensorData["humidity"] = sensor.humidity;
    sensorData["uvIndex"] = sensor.UVIndex;
    sensorData["illuminance"] = sensor.lux;
    sensorData["co2"] = sensor.co2;
    sensorData["tvoc"] = sensor.tvoc;

    // Agregar datos de lluvia
    JsonObject rainfall = doc["rainfall"].to<JsonObject>();
    rainfall["current"] = rainData.intervalRainfall;
    rainfall["hourly"] = rainData.hourlyCarryover;
    rainfall["lastHour"] = rainData.priorHour;
    
    JsonArray hourlyHistory = rainfall["hourlyHistory"].to<JsonArray>();
    for(int i = 0; i < 24; i++) {
        hourlyHistory.add(rainData.hourlyRainfall[i]);
    }

    // Serializar a String
    String json;
    serializeJson(doc, json);
    return json;
}

void sendToWindy() {
    if (!networkConnected()) {
#ifdef SerialMonitor
        Serial.println("[Windy] Error: Sin conexión de red");
#endif
        return;
    }

    // Configurar cliente seguro
    WiFiClientSecure client;
    HTTPClient http;
    
    // Construir URL
    char urlBuffer[256];
    snprintf(urlBuffer, sizeof(urlBuffer), 
            "https://%s%s%s", 
            wy_server, wy_serverurl, wy_WINDYPAGE);

    // Configurar HTTP
    client.setTimeout(15000);
    http.setReuse(true);
    http.setTimeout(15000);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    // Construir y enviar JSON
    String jsonData = getSensorDataJSON();
    
    int httpCode = -1;
    bool success = false;
    
    for (int attempt = 0; attempt <= 2; attempt++) {
        if (http.begin(client, urlBuffer)) {
            http.addHeader("Content-Type", "application/json");
            httpCode = http.POST(jsonData);
            
            if (httpCode == HTTP_CODE_OK) {
                success = true;
                break;
            }
            
            http.end();
            delay(500 * (attempt + 1)); // Backoff exponencial
        }
    }

    // Manejo de resultados
#ifdef SerialMonitor
    if (success) {
        Serial.printf("[Windy] Envío exitoso. Código: %d\n", httpCode);
        Serial.println("Respuesta del servidor:");
        Serial.println(http.getString());
    } else {
        Serial.printf("[Windy] Error final: %d - %s\n", 
                     httpCode, http.errorToString(httpCode).c_str());
    }
#endif

    http.end();
}