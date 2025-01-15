void Ethernet() {
  // Intentar conectar a WiFi
  if (!wifiManager.autoConnect(DEVICE_NAME, "estacion1234")) {
#ifdef SerialMonitor
    Serial.println("Falló la conexión y expiró el tiempo de espera");
#endif
    ESP.restart();  // Reiniciar el dispositivo si no se conecta
  }

#ifdef SerialMonitor
  // Imprimir información sobre la conexión WiFi
  Serial.println("Conectado a WiFi: " + WiFi.SSID());
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
#endif

  // Inicializar mDNS para acceso local a través de .local
  if (MDNS.begin(DEVICE_NAME)) {
#ifdef SerialMonitor
    Serial.println("mDNS iniciado\n");
    Serial.printf("Accede a la página web de ESP32 en: http://%s.local/\n", DEVICE_NAME);
    Serial.println();
#endif
  } else {
#ifdef SerialMonitor
    Serial.println("Error al iniciar mDNS\n");
#endif
  }
}
