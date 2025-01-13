void Ethernet() {
  if (!wifiManager.autoConnect("ESTACION_AP", "estacion1234")) {
    #ifdef SerialMonitor
    Serial.println("Falló la conexión y expiró el tiempo de espera");
    #endif
    ESP.restart();
  }
  #ifdef SerialMonitor
  Serial.println("Conectado a WiFi: " + WiFi.SSID());
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  #endif

  // Inicializar mDNS para que puedas acceder a tu dispositivo usando una URL .local
  if (MDNS.begin("estacion")) {  // "esp32" es el nombre que se usará en la URL
    MonPrintf("mDNS iniciado \n");
    MonPrintf("Accede a la página web de ESP32 en: ");
    MonPrintf("http://estacion.local/ \n");  // Usa el nombre que has elegido para mDNS
  } else {
    MonPrintf("Error al iniciar mDNS\n");
  }
}