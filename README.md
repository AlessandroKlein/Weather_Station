# Estación Meteorológica con ESP32

Este proyecto es una estación meteorológica basada en el microcontrolador ESP32, diseñada para medir y registrar diversas variables ambientales como temperatura, humedad, presión atmosférica, velocidad y dirección del viento, lluvia, índice UV, luminosidad, y niveles de CO2 y TVOC. Los datos recopilados se pueden enviar a servicios en la nube como ThingSpeak, WeatherCloud, Windy y PWSWeather.

## Características Principales

- **Sensores integrados**: 
  - Temperatura (DS18B20, AHT20, BMP280)
  - Humedad (AHT20)
  - Presión atmosférica (BMP280)
  - Velocidad y dirección del viento (anemómetro y veleta)
  - Lluvia (pluviómetro)
  - Índice UV (S12SD)
  - Luminosidad (BH1750)
  - Calidad del aire (CCS811 para CO2 y TVOC)

- **Conexión a Internet**: 
  - WiFi y Ethernet (W5500) para enviar datos a servicios en la nube.
  - Soporte para OTA (Actualización inalámbrica del firmware).

- **Interfaz Web**: 
  - Servidor web integrado para visualizar datos en tiempo real.
  - Interfaz gráfica con gráficos y estadísticas.

- **Almacenamiento local**: 
  - Uso de SPIFFS para almacenar configuraciones y datos.

- **Deep Sleep**: 
  - Modo de bajo consumo para ahorrar energía cuando no hay actividad.

## Estructura del Proyecto

```
alessandroklein-weather_station/
├── partitions_ota.csv
├── platformio.ini
├── include/
│   ├── README
│   ├── esp32a_api.hpp
│   ├── esp32a_definitions_variables.hpp
│   ├── esp32a_environmental.hpp
│   ├── esp32a_ethernet.hpp
│   ├── esp32a_functions.hpp
│   ├── esp32a_pws.hpp
│   ├── esp32a_rainfall.hpp
│   ├── esp32a_sensor.hpp
│   ├── esp32a_server.hpp
│   ├── esp32a_settings.hpp
│   ├── esp32a_sql.hpp
│   ├── esp32a_task.hpp
│   ├── esp32a_thingspeak.hpp
│   ├── esp32a_weathercloud.hpp
│   ├── esp32a_web.hpp
│   ├── esp32a_websockets.hpp
│   ├── esp32a_wifi.hpp
│   ├── esp32a_wind.hpp
│   └── esp32a_windy.hpp
├── lib/
│   └── README
├── src/
│   └── main.cpp
└── test/
    └── README
```

## Configuración

### platformio.ini

El archivo `platformio.ini` contiene la configuración del proyecto, incluyendo las dependencias de librerías, el entorno de compilación y las opciones de compilación. Aquí se definen las versiones de las librerías utilizadas, como `ArduinoJson`, `PubSubClient`, `DallasTemperature`, entre otras.

### partitions_ota.csv

Este archivo define las particiones de la memoria flash del ESP32, permitiendo la actualización OTA (Over-The-Air) del firmware. Se incluyen particiones para el firmware, SPIFFS y datos OTA.

### Archivos de Código

- **main.cpp**: Contiene el código principal del proyecto, incluyendo las funciones `setup()` y `loop()`.
- **include/**: Contiene los archivos de cabecera (.hpp) que dividen el código en módulos para una mejor organización.
- **lib/**: Directorio para bibliotecas específicas del proyecto.
- **test/**: Directorio para pruebas unitarias.

## Dependencias

El proyecto utiliza varias librerías de Arduino y ESP32, que se pueden instalar a través de PlatformIO. Algunas de las principales dependencias incluyen:

- **ArduinoJson**: Para manejar datos en formato JSON.
- **PubSubClient**: Para la comunicación MQTT.
- **DallasTemperature**: Para leer datos del sensor de temperatura DS18B20.
- **Adafruit AHTX0**: Para el sensor de temperatura y humedad AHT20.
- **Adafruit BMP280**: Para el sensor de presión atmosférica y temperatura BMP280.
- **BH1750**: Para el sensor de luminosidad.
- **Adafruit CCS811**: Para el sensor de calidad del aire (CO2 y TVOC).

## Uso

1. **Clonar el repositorio**:
   ```bash
   git clone https://github.com/tu-usuario/alessandroklein-weather_station.git
   cd alessandroklein-weather_station
   ```

2. **Abrir el proyecto en PlatformIO**:
   - Abre el proyecto en Visual Studio Code con la extensión PlatformIO instalada.

3. **Compilar y subir el firmware**:
   - Selecciona el entorno de compilación `esp32doit-devkit-v1` en PlatformIO.
   - Compila y sube el firmware al ESP32.

4. **Configurar la estación**:
   - Accede a la interfaz web de la estación a través de la dirección IP asignada o mediante `http://estacion.local`.
   - Configura los servicios en la nube (ThingSpeak, WeatherCloud, Windy, PWSWeather) y los sensores.

5. **Visualizar datos**:
   - Los datos de los sensores se pueden visualizar en la interfaz web o en los servicios en la nube configurados.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas mejorar el proyecto, por favor crea un fork del repositorio y envía un pull request con tus cambios.

## Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.

---

**Nota**: Este proyecto es un trabajo en progreso y puede contener errores. Si encuentras algún problema, por favor abre un issue en el repositorio.
