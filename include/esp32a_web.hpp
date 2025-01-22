#ifdef webactivation
// CSS
#include "./webh/bootstrap.css.gz.h"
#include "./webh/icons.css.gz.h"
#include "./webh/style.css.gz.h"
#include "./webh/sweetalert.css.gz.h"
// Fonts
#include "./webh/icons.woff.gz.h"
#include "./webh/icons.woff2.gz.h"
// JS
#include "./webh/admin.js.gz.h"
#include "./webh/app.js.gz.h"
#include "./webh/bundle.min.js.gz.h"
#include "./webh/apexcharts.min.js.gz.h"
#include "./webh/firmware.js.gz.h"
#include "./webh/index.js.gz.h"
#include "./webh/mqtt.js.gz.h"
#include "./webh/restart.js.gz.h"
#include "./webh/restore.js.gz.h"
#include "./webh/scripts.js.gz.h"
#include "./webh/sweetalert.js.gz.h"
#include "./webh/template.js.gz.h"
#include "./webh/wifi.js.gz.h"
// HTML
#include "./webh/firmware.html.gz.h"
#include "./webh/index.html.gz.h"
#include "./webh/mqtt.html.gz.h"
#include "./webh/page404.html.gz.h"
#include "./webh/restart.html.gz.h"
#include "./webh/restore.html.gz.h"
#include "./webh/user.html.gz.h"
#include "./webh/wifi.html.gz.h"
// IMG
#include "./webh/logo.png.gz.h"
#include "./webh/favicon.png.gz.h"
#include "./webh/loader.png.gz.h"


// Definir tipos de datos para la respuesta a la solicitud del navegador
const char* dataTypeHTML            = "text/html";
const char* dataTypeCSS             = "text/css";
const char* dataTypeWOFF            = "font/woff";
const char* dataTypeWOFF2           = "font/woff2";
const char* dataTypePNG             = "image/png";
const char* dataTypeJavaScripts     = "application/javascript";

// -------------------------------------------------------------------
// Cargar página index.html
// url: /
// Método: GET
// -------------------------------------------------------------------
void handleIndex(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }
    AsyncWebServerResponse *response = request->beginResponse_P(200, dataTypeHTML, index_html_gz, index_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los archivos del servidor web restart.html
// -------------------------------------------------------------------
void handleRestart(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeHTML, restart_html_gz, restart_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los archivos del servidor web restore.html
// -------------------------------------------------------------------
void handleRestore(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeHTML, restore_html_gz, restore_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los archivos del servidor web firmware.html
// -------------------------------------------------------------------
void handleFirmware(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeHTML, firmware_html_gz, firmware_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}

void handleUser(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeHTML, user_html_gz, user_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web bootstrap.css
// -------------------------------------------------------------------
void handleBootstrapCss(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeCSS, bootstrap_css_gz, bootstrap_css_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web icons.css
// -------------------------------------------------------------------
void handleIconsCss(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeCSS, icons_css_gz, icons_css_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos del Servidor Web icons.woff
// -------------------------------------------------------------------
void handleIconsWoff(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeWOFF, icons_woff_gz, icons_woff_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos del Servidor Web icons.woff2
// -------------------------------------------------------------------
void handleIconsWoff2(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeWOFF2, icons_woff2_gz, icons_woff2_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web style.css
// -------------------------------------------------------------------
void handleStyleCss(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeCSS, style_css_gz, style_css_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web sweetalert.css
// -------------------------------------------------------------------
void handleSweetalertCss(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeCSS, sweetalert_css_gz, sweetalert_css_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web apexcharts.min.js
// -------------------------------------------------------------------
void handleApexChartsJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, apexcharts_min_js_gz, apexcharts_min_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
} 
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web bundle.min.js
// -------------------------------------------------------------------
void handleBundleJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, bundle_min_js_gz, bundle_min_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web sweetalert.js
// -------------------------------------------------------------------
void handleSweetAlertJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, sweetalert_js_gz, sweetalert_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web app.js
// -------------------------------------------------------------------
void handleAppJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, app_js_gz, app_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}

// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web scripts.js
// -------------------------------------------------------------------
void handleScriptsJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, scripts_js_gz, scripts_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web index.js
// -------------------------------------------------------------------
void handleIndexJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, index_js_gz, index_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web wifi.js
// -------------------------------------------------------------------
void handleWifiJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, wifi_js_gz, wifi_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web mqtt.js
// -------------------------------------------------------------------
void handleMqttJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, mqtt_js_gz, mqtt_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web firmware.js
// -------------------------------------------------------------------
void handleFirmwareJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, firmware_js_gz, firmware_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web restart.js
// -------------------------------------------------------------------
void handleRestartJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, restart_js_gz, restart_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web restore.js
// -------------------------------------------------------------------
void handleRestoreJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, restore_js_gz, restore_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web admin.js
// -------------------------------------------------------------------
void handleAdminJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, admin_js_gz, admin_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
// -------------------------------------------------------------------
// Manejo de los Archivos estáticos del Servidor Web template.js
// -------------------------------------------------------------------
void handleTemplateJs(AsyncWebServerRequest *request){
    if (security){
        if (!request->authenticate(device_user, device_password))
            return request->requestAuthentication();
    }   
    AsyncWebServerResponse *response = request->beginResponse_P(200,dataTypeJavaScripts, template_js_gz, template_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Access-Control-Max-Age","600");
    request->send(response);
}
#endif