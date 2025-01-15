// Función para simular la lectura de datos de los sensores
void readSensors() {
#ifdef demo
  sensor.windDirectionADC = random(0, 360);
  sensor.windDirectiongradiant = random(0, 360);
  sensor.rainTicks24h = random(0, 100);
  sensor.rainTicks60m = random(0, 50);
  sensor.temperatureC = random(15, 30);
  sensor.temperatureAHT = random(15, 30);
  sensor.temperatureBMP = random(15, 30);
  sensor.windSpeed = random(0, 50);
  sensor.windSpeedMax = random(0, 100);
  sensor.barometricPressure = random(1000, 1020);
  sensor.humidity = random(30, 80);
  sensor.UVIndex = random(0, 10);
  sensor.lux = random(0, 1000);
  sensor.c02 = random(300, 500);
  sensor.tvoc = random(0, 100);
#endif
#ifdef webSocket
  // Convertir los datos a JSON y enviarlos a los clientes WebSocket conectados
  String jsonData = sensorDataToJson();
  webSocket.broadcastTXT(jsonData);  // Enviar el JSON a todos los clientes conectados
#endif
}

void sensordemoprint() {
#ifdef demo
#ifdef SerialMonitor
  Serial.println(sensor.windDirectionADC);
  Serial.println(sensor.windDirectiongradiant);
  Serial.println(sensor.rainTicks24h);
  Serial.println(sensor.rainTicks60m);
  Serial.println(sensor.temperatureC);
  Serial.println(sensor.temperatureAHT);
  Serial.println(sensor.temperatureBMP);
  Serial.println(sensor.windSpeed);
  Serial.println(sensor.windSpeedMax);
  Serial.println(sensor.barometricPressure);
  Serial.println(sensor.humidity);
  Serial.println(sensor.UVIndex);
  Serial.println(sensor.lux);
  Serial.println(sensor.c02);
  Serial.println(sensor.tvoc);
#endif
#endif
}