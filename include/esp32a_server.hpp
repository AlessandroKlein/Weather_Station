#pragma once

#include "ESPAsyncWebServer.h"
#include <Update.h>

#include "esp32a_api.hpp"
#ifdef webactivation
#include "esp32a_web.hpp"
#endif

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

void initServer()
{

    // -------------------------------------------------------------------
    // Manejo de la descarga del archivo setting.json
    // url: "/api/device/download"
    // Método: GET
    // -------------------------------------------------------------------
    server.on("/api/device/download", HTTP_GET, handleApiDownload);
    // -------------------------------------------------------------------
    // Manejo de la carga del archivo settings.json
    // url: "/api/device/upload"
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/device/upload", HTTP_POST, [](AsyncWebServerRequest *request)
              { opened = false; }, [](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final)
              { handleApiUpload(request, filename, index, data, len, final); });

    // -------------------------------------------------------------------
    // Manejo de la actualización del Firmware a FileSystem
    // url: /api/device/firmware
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/device/firmware", HTTP_POST, [](AsyncWebServerRequest *request) {}, [](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final)
              { handleApiFirmware(request, filename, index, data, len, final); });
    // -------------------------------------------------------------------
    // Manejo del reinicio
    // url: "/api/device/restart"
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/device/restart", HTTP_POST, handleApiPostRestart);
    // -------------------------------------------------------------------
    // Manejo de la restauración
    // url: "/api/device/restore"
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/device/restore", HTTP_POST, handleApiPostRestore);
    // -------------------------------------------------------------------
    // cerrar sesión
    // url: /api/perfil/logout TODO: Modificar en el front
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/perfil/logout", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (security){
            if (!request->authenticate(device_user, device_password))
                return request->requestAuthentication();
        } 
        request->send(401, dataType, "{ \"session\": false, \"msg\": \"Sesión cerrada correctamente\"}"); });

#ifdef webactivation
    // -------------------------------------------------------------------
    // Zona Servidor WEB
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // Cargar página index.html
    // url: /
    // Método: GET
    // -------------------------------------------------------------------
    server.on("/", HTTP_GET, handleIndex);
    // -------------------------------------------------------------------
    // Cargar de la ruta /esp-restart
    // -------------------------------------------------------------------
    server.on("/esp-restart", HTTP_GET, handleRestart);
    // -------------------------------------------------------------------
    // Cargar de la ruta /esp-restore
    // -------------------------------------------------------------------
    server.on("/esp-restore", HTTP_GET, handleRestore);
    // -------------------------------------------------------------------
    // Cargar de la ruta /esp-device
    // -------------------------------------------------------------------
    server.on("/esp-device", HTTP_GET, handleFirmware);
    // -------------------------------------------------------------------
    // Cargar de la ruta /esp-admin
    // -------------------------------------------------------------------
    server.on("/esp-admin", HTTP_GET, handleUser);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/bootstrap.css
    // ------------------------------------------------------------------- 
    server.on("/assets/css/bootstrap.css",HTTP_GET, handleBootstrapCss);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/icons.css
    // ------------------------------------------------------------------- 
    server.on("/assets/css/icons.css",HTTP_GET, handleIconsCss);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/style.css
    // ------------------------------------------------------------------- 
    server.on("/assets/css/style.css",HTTP_GET, handleStyleCss);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/sweetalert.css
    // ------------------------------------------------------------------- 
    server.on("/assets/css/sweetalert.css",HTTP_GET, handleSweetalertCss);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/fonts/icons.woff
    // ------------------------------------------------------------------- 
    server.on("/assets/css/fonts/icons.woff",HTTP_GET, handleIconsWoff);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/css/fonts/icons.woff2
    // ------------------------------------------------------------------- 
    server.on("/assets/css/fonts/icons.woff2",HTTP_GET, handleIconsWoff2);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/apexcharts.min.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/apexcharts.min.js",HTTP_GET, handleApexChartsJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/bundle.min.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/bundle.min.js",HTTP_GET, handleBundleJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/sweetalert.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/sweetalert.js",HTTP_GET, handleSweetAlertJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/app.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/app.js",HTTP_GET, handleAppJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/scripts.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/scripts.js",HTTP_GET, handleScriptsJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/index.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/index.js",HTTP_GET, handleIndexJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/wifi.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/wifi.js",HTTP_GET, handleWifiJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/mqtt.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/mqtt.js",HTTP_GET, handleMqttJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/firmware.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/firmware.js",HTTP_GET, handleFirmwareJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/restart.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/restart.js",HTTP_GET, handleRestartJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/restore.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/restore.js",HTTP_GET, handleRestoreJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/admin.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/admin.js",HTTP_GET, handleAdminJs);
    // -------------------------------------------------------------------
    // Cargar de Archivos complementarios /assets/js/template.js
    // ------------------------------------------------------------------- 
    server.on("/assets/js/template.js",HTTP_GET, handleTemplateJs);
#endif
}