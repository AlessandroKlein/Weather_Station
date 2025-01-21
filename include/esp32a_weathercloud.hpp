#include <HTTPClient.h>
#include <ArduinoJson.h>

void weathercloud(void) {
  HTTPClient http;

  // Construir URL de la API
  //String url = "http://api.weathercloud.net/v1/push/" + String(ID2) + "?key=" + String(Key2);
  String url = String(wc_server) + "/v1/push/" + String(wc_ID) + "?key=" + String(wc_Key);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // Crear el documento JSON para enviar
  StaticJsonDocument<capacitySettings> doc;

  // Agregar datos de los sensores al JSON
  doc["windDirectionADC"] = sensor.windDirectionADC;
  doc["windDirectionGradient"] = sensor.windDirectionGradient;
  doc["rainTicks24h"] = sensor.rainTicks24h;
  doc["rainTicks60m"] = sensor.rainTicks60m;
  doc["temperatureC"] = sensor.temperatureC;
  doc["temperatureAHT"] = sensor.temperatureAHT;
  doc["temperatureBMP"] = sensor.temperatureBMP;
  doc["windSpeed"] = sensor.windSpeed;
  doc["windSpeedMax"] = sensor.windSpeedMax;
  doc["barometricPressure"] = sensor.barometricPressure;
  doc["humidity"] = sensor.humidity;
  doc["UVIndex"] = sensor.UVIndex;
  doc["lux"] = sensor.lux;
  doc["co2"] = sensor.co2;
  doc["tvoc"] = sensor.tvoc;

  // Agregar datos de lluvia como objeto anidado
  JsonObject rainfall = doc.createNestedObject("rainfall");
  rainfall["intervalRainfall"] = rainData.intervalRainfall;

  JsonArray hourlyRainfallArray = rainfall.createNestedArray("hourlyRainfall");
  for (int i = 0; i < 24; i++) {
    hourlyRainfallArray.add(rainData.hourlyRainfall[i]);
  }

  JsonArray current60MinRainfallArray = rainfall.createNestedArray("current60MinRainfall");
  for (int i = 0; i < 5; i++) {
    current60MinRainfallArray.add(rainData.current60MinRainfall[i]);
  }

  rainfall["hourlyCarryover"] = rainData.hourlyCarryover;
  rainfall["priorHour"] = rainData.priorHour;
  rainfall["minuteCarryover"] = rainData.minuteCarryover;
  rainfall["priorMinute"] = rainData.priorMinute;

  // Serializar JSON a una cadena
  String json;
  serializeJson(doc, json);

#ifdef SerialMonitor
  Serial.println("Enviando JSON:");
  Serial.println(json);
#endif

  // Enviar el JSON a la API
  int httpResponseCode = http.POST(json);

#ifdef SerialMonitor
  if (httpResponseCode > 0) {
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Respuesta del servidor:");
      Serial.println(payload);
    }
  } else {
    Serial.print("Error al enviar la petición: ");
    Serial.println(http.errorToString(httpResponseCode));
  }
#endif

  http.end();  // Cerrar la conexión HTTP
}
