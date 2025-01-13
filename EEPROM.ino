//===================================================
// Función para guardar configuración
//===================================================
void saveConfig() {
  EEPROM.begin(512);
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
  //Serial.println("Configuración guardada en EEPROM");

  MonPrintf(String("weathercloud ") + String(weathercloud_enabled) + "\n");
  MonPrintf(String("thingspeak ") + String(thingspeak_enabled) + "\n");
  MonPrintf(String("windy ") + String(windy_enabled) + "\n");
  MonPrintf(String("pwsweather ") + String(pwsweather_enabled) + "\n");
}

//===================================================
// Función para leer configuración
//===================================================

void readConfig() {
  EEPROM.begin(512);
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
  EEPROM.end();
}