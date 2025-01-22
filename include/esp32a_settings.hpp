// -------------------------------------------------------------------
// Declaración de funciones
// -------------------------------------------------------------------
boolean settingsRead();
void settingsReset();
boolean settingsSave();

// -------------------------------------------------------------------
// Leer settings.json
// -------------------------------------------------------------------
boolean settingsRead()
{

    DynamicJsonDocument jsonSettings(capacitySettings);

    File file = SPIFFS.open("/settings.json", "r");
    if (deserializeJson(jsonSettings, file))
    {
        settingsReset(); // llamar la función que formatea a fabrica                                                                  // Tomar los valores de Fábrica
        DeserializationError error = deserializeJson(jsonSettings, file);
        log("ERROR", "Falló la lectura de las configuraciones, tomando valores por defecto");
        if (error)
        {
            log("ERROR", String(error.c_str()));
        }
        return false;
    }
    else
    {
        // -------------------------------------------------------------------
        // Dispositivo settings.json
        // -------------------------------------------------------------------
        strlcpy(device_id, jsonSettings["device_id"], sizeof(device_id));
        strlcpy(device_name, jsonSettings["device_name"], sizeof(device_name));
        strlcpy(device_user, jsonSettings["device_user"], sizeof(device_user));
        strlcpy(device_password, jsonSettings["device_password"], sizeof(device_password));
        // -------------------------------------------------------------------
        // ThingSpeak settings.json
        // -------------------------------------------------------------------
        thingspeak_enabled = jsonSettings["thingspeak"]["thingspeak_enabled"];
        strlcpy(ts_server, jsonSettings["thingspeak"]["ts_server"], sizeof(ts_server));
        strlcpy(ts_api_key, jsonSettings["thingspeak"]["ts_api_key"], sizeof(ts_api_key));
        channelID = jsonSettings["thingspeak"]["channelID"];
        // -------------------------------------------------------------------
        // Weathercloud settings.json
        // -------------------------------------------------------------------
        weathercloud_enabled = jsonSettings["weathercloud"]["weathercloud_enabled"];
        strlcpy(wc_server, jsonSettings["weathercloud"]["wc_server"], sizeof(wc_server));
        strlcpy(wc_ID, jsonSettings["weathercloud"]["wc_ID"], sizeof(wc_ID));
        strlcpy(wc_Key, jsonSettings["weathercloud"]["wc_Key"], sizeof(wc_Key));
        // -------------------------------------------------------------------
        // windy settings.json
        // -------------------------------------------------------------------
        windy_enabled = jsonSettings["windy"]["windy_enabled"];
        strlcpy(wy_server, jsonSettings["windy"]["wy_server"], sizeof(wy_server));
        strlcpy(wy_serverurl, jsonSettings["windy"]["wy_serverurl"], sizeof(wy_serverurl));
        strlcpy(wy_WINDYPAGE, jsonSettings["windy"]["wy_WINDYPAGE"], sizeof(wy_WINDYPAGE));
        wy_serverPort = jsonSettings["windy"]["wy_serverPort"];
        // -------------------------------------------------------------------
        // pwsweather settings.json
        // -------------------------------------------------------------------
        pwsweather_enabled = jsonSettings["pwsweather"]["pwsweather_enabled"];
        strlcpy(pw_server, jsonSettings["pwsweather"]["pw_server"], sizeof(pw_server));
        strlcpy(pw_WEBPAGE, jsonSettings["pwsweather"]["pw_WEBPAGE"], sizeof(pw_WEBPAGE));
        strlcpy(pw_I5, jsonSettings["pwsweather"]["pw_I5"], sizeof(pw_I5));
        strlcpy(pw_Key, jsonSettings["pwsweather"]["pw_Key"], sizeof(pw_Key));

        // cerrar el archivo
        file.close();
        log("INFO", "Lectura de las configuraciones correctamente");
        return true;
    }
}
// -------------------------------------------------------------------
// Valores de Fábrica al settings.json
// -------------------------------------------------------------------
void settingsReset()
{
    // -------------------------------------------------------------------
    // Dispositivo settings.json
    // -------------------------------------------------------------------
    strlcpy(device_id, DeviceID().c_str(), sizeof(device_id)); // ESP32DC15B80C703E
    strlcpy(device_name, extractNumbers(DeviceID()).c_str(), sizeof(device_name));
    strlcpy(device_user, "admin", sizeof(device_user));
    strlcpy(device_password, "admin", sizeof(device_password));
    // -------------------------------------------------------------------
    // ThingSpeak settings.json
    // -------------------------------------------------------------------
    thingspeak_enabled = false;
    strlcpy(ts_server, "api.thingspeak.com", sizeof(ts_server));
    strlcpy(ts_api_key, "S492YTVXPSHGW3TX", sizeof(ts_api_key));
    channelID = 2801433;
    // -------------------------------------------------------------------
    // weathercloud settings.json
    // -------------------------------------------------------------------
    weathercloud_enabled = false;
    strlcpy(wc_server, "api.weathercloud.net", sizeof(wc_server));
    strlcpy(wc_ID, "00ecdb12ca8bbb52", sizeof(wc_ID));
    strlcpy(wc_Key, "f346309ef31340107c93550b46a32b0f", sizeof(wc_Key));
    // -------------------------------------------------------------------
    // windy settings.json
    // -------------------------------------------------------------------
    windy_enabled = false;
    strlcpy(wy_server, "stations.windy.com", sizeof(wy_server));
    strlcpy(wy_serverurl, "/pws/station/", sizeof(wy_serverurl));
    strlcpy(wy_WINDYPAGE, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjaSI6NDY2MTMxOSwiaWF0IjoxNzI5NzI3MTEwfQ.LRszCmJUyoklaUsg-F4TKQzVQeKvjSAA9Rk-m3HL3OA/f039ea10", sizeof(wy_WINDYPAGE));
    wy_serverPort = 443;
    // -------------------------------------------------------------------
    // Pwsweather settings.json
    // -------------------------------------------------------------------
    pwsweather_enabled = false;
    strlcpy(pw_server, "pwsupdate.pwsweather.com", sizeof(pw_server));
    strlcpy(pw_WEBPAGE, "GET /api/v1/submitwx?", sizeof(pw_WEBPAGE));
    strlcpy(pw_I5, "NFJNERJNRNRKOMER", sizeof(pw_I5));
    strlcpy(pw_Key, "7b6fe8e1230f656898424766a6283988", sizeof(pw_Key));

    log("INFO", "Se reiniciaron todos los valores por defecto");
}
// -------------------------------------------------------------------
// Guardar settings.json
// -------------------------------------------------------------------
boolean settingsSave()
{
    //StaticJsonDocument<capacitySettings> jsonSettings;
    DynamicJsonDocument jsonSettings(capacitySettings);

    File file = SPIFFS.open("/settings.json", "w+");

    if (file)
    {
        // -------------------------------------------------------------------
        // Dispositivo settings.json
        // -------------------------------------------------------------------
        jsonSettings["device_id"] = device_id;
        jsonSettings["device_name"] = device_name;
        jsonSettings["device_user"] = device_user;
        jsonSettings["device_password"] = device_password;
        // -------------------------------------------------------------------
        // ThingSpeak settings.json
        // -------------------------------------------------------------------
        JsonObject tsObj = jsonSettings["thingspeak"].to<JsonObject>();
        tsObj["thingspeak_enabled"] = thingspeak_enabled;
        tsObj["ts_server"] = ts_server;
        tsObj["ts_api_key"] = ts_api_key;
        tsObj["channelID"] = channelID;

        // -------------------------------------------------------------------
        // weathercloud settings.json
        // -------------------------------------------------------------------
        JsonObject wcObj = jsonSettings["weathercloud"].to<JsonObject>();
        wcObj["weathercloud_enabled"] = weathercloud_enabled;
        wcObj["wc_server"] = wc_server;
        wcObj["wc_ID"] = wc_ID;
        wcObj["wc_Key"] = wc_Key; // Corregido: la clave debería ir dentro de wcObj

        // -------------------------------------------------------------------
        // windy settings.json
        // -------------------------------------------------------------------
        JsonObject wyObj = jsonSettings["windy"].to<JsonObject>();
        wyObj["windy_enabled"] = windy_enabled;
        wyObj["wy_server"] = wy_server;
        wyObj["wy_serverurl"] = wy_serverurl;
        wyObj["wy_WINDYPAGE"] = wy_WINDYPAGE;
        wyObj["wy_serverPort"] = wy_serverPort;

        // -------------------------------------------------------------------
        // Pwsweather settings.json
        // -------------------------------------------------------------------
        JsonObject pwObj = jsonSettings["pwsweather"].to<JsonObject>();
        pwObj["pwsweather_enabled"] = pwsweather_enabled;
        pwObj["pw_server"] = pw_server;
        pwObj["pw_WEBPAGE"] = pw_WEBPAGE;
        pwObj["pw_I5"] = pw_I5;
        pwObj["pw_Key"] = pw_Key;

        jsonSettings["file_version"] = "3.0.0";

        serializeJsonPretty(jsonSettings, file);
        file.close();
        log("INFO", "Configuración guardada correctamente");
        serializeJsonPretty(jsonSettings, Serial);
        return true;
    }
    else
    {
        log("ERROR", "Falló el guardado de la configuración");
        return false;
    }
}