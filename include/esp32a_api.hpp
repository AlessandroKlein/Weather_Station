bool security = false;
const char *dataType = "application/json";


// -------------------------------------------------------------------
// Manejo de la descarga del archivo setting.json
// url: "/api/device/download"
// Método: GET
// -------------------------------------------------------------------
void handleApiDownload(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }    
    log("INFO", "Descarga del archivo settings.json");
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/settings.json", dataType, true);
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de la carga del archivo settings.json
// url: "/api/device/upload"
// Método: POST
// -------------------------------------------------------------------
// Variables para la carga del archivo
File file;
bool opened = false;
void handleApiUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    } 

    if (!index){
        Serial.printf("INFO", "Upload Start: %s\n", filename.c_str());
    }
    // Validar el archivo si esta abierto settings.json
    if (opened == false){
        opened = true;
        file = SPIFFS.open(String("/") + filename, FILE_WRITE);
        if (!file){
            log("ERROR", "No se pudo abrir el archivo para escribir");
            request->send(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo abrir el archivo para escribir!\"}");
            return;
        }
    }

    // Escribir el archivo en la memoria
    if (file.write(data, len) != len){
        log("ERROR", "No se pudo escribir el archivo");
        request->send(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo escribir el archivo: " + filename + " !\"}");
        return;
    }

    // Finalizada la carga del archivo.
    if (final){
        AsyncWebServerResponse *response = request->beginResponse(201, dataType, "{ \"save\": true, \"msg\": \"¡Carga del archivo: " + filename + " completada!\"}");
        response->addHeader("Cache-Control", "no-cache");
        response->addHeader("Location", "/");
        request->send(response);
        file.close();
        opened = false;
        log("INFO", "Carga del archivo " + filename + " completada");
        // Esperar la transmisión de los datos seriales
        Serial.flush();
        // Reiniciar el ESP32
        ESP.restart();
    }
}
// -------------------------------------------------------------------
// Manejo de la actualización del Firmware a FileSystem
// url: /api/device/firmware
// Método: POST
// -------------------------------------------------------------------
void handleApiFirmware(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }

    // Si el nombre de archivo incluye ( spiffs ), actualiza la partición de spiffs
    int cmd = (filename.indexOf("spiffs") > -1) ? U_PART : U_FLASH;
    String updateSystem = cmd == U_PART ? "FileSystem" : "Firmware";

    if (!index){
        content_len = request->contentLength();
        log("INFO", "Actualización del " + updateSystem + " iniciada...");
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)){
            AsyncWebServerResponse *response = request->beginResponse(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo actualizar el " + updateSystem + " Index: " + filename + " !\"}");
            request->send(response);
            Update.printError(Serial);
            log("ERROR", "Update del " + updateSystem + " ternimado");
        }
    }
    // escribir e firmware o el filesystem
    if (Update.write(data, len) != len){
        Update.printError(Serial);
    }
    // Terminado
    if (final){
        if (!Update.end(true)){
            AsyncWebServerResponse *response = request->beginResponse(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo actualizar el " + updateSystem + " Final: " + filename + " !\"}");
            request->send(response);
            Update.printError(Serial);
        }else{
            AsyncWebServerResponse *response = request->beginResponse(201, dataType, "{ \"save\": true, \"type\": \"" + updateSystem + "\"}");
            response->addHeader("Cache-Control", "no-cache");
            response->addHeader("Location", "root@" + updateSystem + "");
            request->send(response);
            log("INFO", "Update del " + updateSystem + " completado");
            // Esperar la Transmisión de los datos seriales
            Serial.flush();
            ESP.restart();
        }
    }
}
// -------------------------------------------------------------------
// Función para reiniciar el dispositivo Global -> API, MQTT, WS
// Método: POST
// API o MQTT
// -------------------------------------------------------------------
void apiPostRestart(String origin){
    log("INFO", "Dispositivo reiniciado desde: "+origin);
    Serial.flush();
    ESP.restart();
}
// -------------------------------------------------------------------
// Manejo del reinicio del dispositivo
// url: /api/device/restart
// Método: POST
// -------------------------------------------------------------------
void handleApiPostRestart(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    } 
    // Retornamos la respuesta
    request->send(200, dataType, "{ \"restart\": true }");
    // Reiniciar el ESP32
    String origin = "API";
    apiPostRestart(origin);
}

// -------------------------------------------------------------------
// Función para restablecer el dispositivo Global -> API, MQTT, WS
// Método: POST
// API o MQTT
// -------------------------------------------------------------------
void apiPostRestore(String origin){
    settingsReset(); // Todo a fabrica
    if(settingsSave()){
        log("INFO", "Dispositivo restablecido desde: "+origin);
        // Esperar la transmisión de los datos seriales ( para agregar delay asyncrono antes del reinicio ) 
        Serial.flush();
        // Reinicia el ESP32
        ESP.restart();
    }    
}

// -------------------------------------------------------------------
// Manejo de la restauración del dispositivo
// url: /api/device/restore
// Método: POST
// -------------------------------------------------------------------
void handleApiPostRestore(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    } 
    // Retornamos la respuesta
    request->send(200, dataType, "{ \"restore\": true }");
    // Reiniciar el ESP32
    String origin = "API";
    apiPostRestore(origin);
}