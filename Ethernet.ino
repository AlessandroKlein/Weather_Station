void Ethernet() {
  if (!wifiManager.autoConnect(DEVICE_NAME, "estacion1234")) {
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
  if (MDNS.begin(String(DEVICE_NAME))) {  // "esp32" es el nombre que se usará en la URL
    MonPrintf("mDNS iniciado \n");
    MonPrintf("Accede a la página web de ESP32 en: ");
    MonPrintf("http://"+ String(DEVICE_NAME) + ".local/ \n");  // Usa el nombre que has elegido para mDNS
  } else {
    MonPrintf("Error al iniciar mDNS\n");
  }
}

//===========================================
// MDNS
//===========================================
//MDNS setup
/*void nombre_red_stup() {
  if (!MDNS.begin("ecohaven")) {
    MonPrintf("Erro configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }
  MonPrintf("mDNS configurado");
  MonPrintf("Accede a la página web de ESP32 en: ");
  MonPrintf("http://estacion.local/ \n");
}*/