//===================================================
// Función para guardar configuración
//===================================================
void saveConfig() {
  EEPROM.begin(512);

  // Guardar configuración
  EEPROM.put(0, ts_api_key);
  EEPROM.put(34, ID2);
  EEPROM.put(68, Key2);
  EEPROM.put(102, WINDYPAGE);
  EEPROM.put(242, ID5);
  EEPROM.put(276, Key5);
  EEPROM.write(310, weathercloud_enabled);
  EEPROM.write(311, thingspeak_enabled);
  EEPROM.write(312, windy_enabled);
  EEPROM.write(313, pwsweather_enabled);

  EEPROM.commit();
  EEPROM.end();

  // Mensajes de depuración
#ifdef SerialMonitor
  Serial.println("Configuración guardada en EEPROM\n");
  Serial.println("weathercloud: " + String(weathercloud_enabled) + "\n");
  Serial.println("thingspeak: " + String(thingspeak_enabled) + "\n");
  Serial.println("windy: " + String(windy_enabled) + "\n");
  Serial.println("pwsweather: " + String(pwsweather_enabled) + "\n");
#endif
}

//===================================================
// Función para leer configuración
//===================================================

void readConfig() {
  EEPROM.begin(512);

  // Cargar configuración desde EEPROM
  EEPROM.get(0, ts_api_key);
  EEPROM.get(34, ID2);
  EEPROM.get(68, Key2);
  EEPROM.get(102, WINDYPAGE);
  EEPROM.get(242, ID5);
  EEPROM.get(276, Key5);
  EEPROM.get(310, weathercloud_enabled);
  EEPROM.get(311, thingspeak_enabled);
  EEPROM.get(312, windy_enabled);
  EEPROM.get(313, pwsweather_enabled);
  EEPROM.get(314, channelID);  // Cargar channelID desde EEPROM

  EEPROM.end();

  // Convertir channelID a String
  sprintf(channelIDStr, "%lu", channelID);

  // Impresión de los valores leídos
#ifdef SerialMonitor
  Serial.println("Configuración cargada desde EEPROM:");
  Serial.println("ts_api_key: " + String(ts_api_key));
  Serial.println("channelID: " + String(channelID));
  Serial.println("ID2: " + String(ID2));
  Serial.println("Key2: " + String(Key2));
  Serial.println("WINDYPAGE: " + String(WINDYPAGE));
  Serial.println("ID5: " + String(ID5));
  Serial.println("Key5: " + String(Key5));
  Serial.println("weathercloud_enabled: " + String(weathercloud_enabled));
  Serial.println("thingspeak_enabled: " + String(thingspeak_enabled));
  Serial.println("windy_enabled: " + String(windy_enabled));
  Serial.println("pwsweather_enabled: " + String(pwsweather_enabled));
#endif
}
