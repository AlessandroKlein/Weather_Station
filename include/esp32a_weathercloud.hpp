// Funciones auxiliares para formato numérico
inline float round1(float value) { return static_cast<int>(value * 10) / 10.0f; }
inline float round2(float value) { return static_cast<int>(value * 100) / 100.0f; }

void weathercloud()
{
  // 1. Verificar conexión de red primero
  if (!networkConnected())
  {
#ifdef SerialMonitor
    Serial.println("[WeatherCloud] Error: Sin conexión de red");
#endif
    return;
  }

  // 2. Buffer estático para URL
  char urlBuffer[256];
  snprintf(urlBuffer, sizeof(urlBuffer), "%s/v1/push/%s?key=%s",
           wc_server, wc_ID, wc_Key);

  // 3. Configuración HTTP optimizada
  WiFiClient client;
  HTTPClient http;

  http.setTimeout(15000);
  http.setReuse(false);
  http.setUserAgent("ESP32-WeatherStation/1.0");
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  // 4. Calcular tamaño JSON dinámicamente
  /*const size_t capacity = JSON_OBJECT_SIZE(15) +
                          JSON_OBJECT_SIZE(5) +
                          24 * JSON_ARRAY_SIZE(1) +
                          5 * JSON_ARRAY_SIZE(1) +
                          512;
  DynamicJsonDocument doc(capacity);*/
  JsonDocument doc;

  // 5. Datos principales con movimiento semántico
  JsonObject root = doc.to<JsonObject>();
  root["windDirectionADC"] = sensor.windDirectionADC;
  root["windDirectionGradient"] = sensor.windDirectionGradient;
  root["temperatureC"] = round2(sensor.temperatureC);
  root["temperatureAHT"] = round2(sensor.temperatureAHT);
  root["temperatureBMP"] = round2(sensor.temperatureBMP);
  root["windSpeed"] = round1(sensor.windSpeed);
  root["windSpeedMax"] = round1(sensor.windSpeedMax);
  root["barometricPressure"] = round2(sensor.barometricPressure);
  root["humidity"] = static_cast<uint8_t>(sensor.humidity);
  root["UVIndex"] = static_cast<uint8_t>(sensor.UVIndex);
  root["lux"] = static_cast<int>(sensor.lux);
  root["co2"] = static_cast<int>(sensor.co2);
  root["tvoc"] = static_cast<int>(sensor.tvoc);

  // 6. Datos de lluvia optimizados
  //JsonObject rainfall = root.createNestedObject("rainfall");
  JsonObject rainfall = root["rainfall"].to<JsonObject>();
  rainfall["intervalRainfall"] = round2(rainData.intervalRainfall);
  rainfall["hourlyCarryover"] = round2(rainData.hourlyCarryover);
  rainfall["priorHour"] = round2(rainData.priorHour);

  //JsonArray hourly = rainfall.createNestedArray("hourlyRainfall");
  JsonArray hourly = rainfall["hourlyRainfall"].to<JsonArray>();
  for (size_t i = 0; i < sizeof(rainData.hourlyRainfall) / sizeof(rainData.hourlyRainfall[0]); i++)
  {
    hourly.add(rainData.hourlyRainfall[i]);
  }

  //JsonArray current60 = rainfall.createNestedArray("current60MinRainfall");
  JsonArray current60 = rainfall["current60MinRainfall"].to<JsonArray>();
  for (size_t i = 0; i < sizeof(rainData.current60MinRainfall) / sizeof(rainData.current60MinRainfall[0]); i++)
  {
    current60.add(rainData.current60MinRainfall[i]);
  }

  // 7. Serialización eficiente
  String json;
  serializeJson(doc, json);

  // 8. Envío con reintentos y manejo de errores
  const uint8_t maxRetries = 2;
  int httpResponseCode = -1;
  bool success = false;

  for (uint8_t attempt = 0; attempt <= maxRetries; ++attempt)
  {
    if (http.begin(client, urlBuffer))
    {
      http.addHeader("Content-Type", "application/json");
      httpResponseCode = http.POST(json);

      if (httpResponseCode == HTTP_CODE_OK)
      {
        success = true;
#ifdef SerialMonitor
        String response = http.getString();
        Serial.printf("[WeatherCloud] Respuesta: %s\n", response.c_str());
#endif
        break;
      }

#ifdef SerialMonitor
      Serial.printf("[WeatherCloud] Intento %d - Código: %d\n",
                    attempt + 1, httpResponseCode);
#endif
      http.end();
      delay(500 * (attempt + 1)); // Backoff exponencial
    }
  }

  // 9. Logging detallado
#ifdef SerialMonitor
  if (!success)
  {
    Serial.printf("[WeatherCloud] Error final: %d - %s\n",
                  httpResponseCode, http.errorToString(httpResponseCode).c_str());
    Serial.println("JSON enviado:");
    serializeJsonPretty(doc, Serial);
    Serial.println();
  }
#endif

  // 10. Limpieza garantizada
  http.end();
  doc.clear();
}