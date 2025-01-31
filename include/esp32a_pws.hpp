void pws(void) {
    // 1. Validar conexión de red primero
    if (!networkConnected()) {
#ifdef SerialMonitor
        Serial.println("PWS: Error - Sin conexión de red");
#endif
        return;
    }

    // 2. Usar buffer estático para mejor performance
    static char urlBuffer[512];
    char* ptr = urlBuffer;
    size_t remaining = sizeof(urlBuffer);

    // 3. Construir URL de forma más eficiente
    int written = snprintf(ptr, remaining, "%s%s?ID=%s&PASSWORD=%s",
                          pw_server, pw_WEBPAGE, pw_I5, pw_Key);
                          
    if (written < 0 || written >= remaining) {
#ifdef SerialMonitor
        Serial.println("PWS: Error - Buffer URL demasiado pequeño");
#endif
        return;
    }
    ptr += written;
    remaining -= written;

    // 4. Pre-calcular valores numéricos
    const float tempF = sensor.temperatureC * 1.8f + 32.0f;
    const float pressureInHg = sensor.barometricPressure * 0.02953f;
    const float windSpeedMph = sensor.windSpeed * 1.60934f;
    const float windGustMph = sensor.windSpeedMax * 1.60934f;
    const float rainIn = rainData.intervalRainfall * 0.0393701f;

    // 5. Añadir parámetros con formato seguro
    written = snprintf(ptr, remaining,
                      "&tempf=%.1f"
                      "&humidity=%.1f"
                      "&baromin=%.2f"
                      "&windspeedmph=%.1f"
                      "&windgustmph=%.1f"
                      "&winddir=%.0f"
                      "&rainin=%.2f"
                      "&UV=%.1f"
                      "&solar=%.0f"
                      "&co2=%.0f",
                      tempF,
                      sensor.humidity,
                      pressureInHg,
                      windSpeedMph,
                      windGustMph,
                      sensor.windDirectionGradient,
                      rainIn,
                      sensor.UVIndex,
                      sensor.lux,
                      sensor.co2);

    if (written < 0 || written >= remaining) {
#ifdef SerialMonitor
        Serial.println("PWS: Error - Buffer URL excedido");
#endif
        return;
    }

    // 6. Configurar cliente HTTP con timeout
    HTTPClient http;
    WiFiClient client;
    
    http.setTimeout(10000); // 10 segundos de timeout
    http.setUserAgent("ESP32-Weather-Station/1.0");
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    // 7. Manejo mejorado de errores con reintentos
    const int maxRetries = 2;
    int httpResponseCode = -1;
    
    for (int attempt = 0; attempt <= maxRetries; attempt++) {
        if (!http.begin(client, urlBuffer)) {
#ifdef SerialMonitor
            Serial.println("PWS: Error - Fallo al iniciar conexión HTTP");
#endif
            break;
        }

        httpResponseCode = http.GET();
        
        if (httpResponseCode == HTTP_CODE_OK) {
            // Éxito, salir del loop
            break;
        }
        
#ifdef SerialMonitor
        Serial.printf("PWS: Intento %d - Código: %d\n", attempt + 1, httpResponseCode);
#endif
        
        if (attempt < maxRetries) {
            delay(500 * (attempt + 1)); // Backoff progresivo
        }
    }

    // 8. Procesar respuesta
    if (httpResponseCode == HTTP_CODE_OK) {
#ifdef SerialMonitor
        Serial.println("PWS: Datos enviados exitosamente");
        const String& response = http.getString();
        Serial.printf("Respuesta del servidor: %s\n", response.c_str());
#endif
    } else {
#ifdef SerialMonitor
        Serial.printf("PWS: Error final - Código: %d\n", httpResponseCode);
        if (httpResponseCode < 0) {
            Serial.printf("Error interno: %s\n", http.errorToString(httpResponseCode).c_str());
        }
#endif
    }

    // 9. Limpieza garantizada
    http.end();
}