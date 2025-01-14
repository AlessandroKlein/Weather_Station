# Estación Meteorológica con ESP32

Este proyecto implementa una estación meteorológica diseñada con un **ESP32**, capaz de medir diversas variables climáticas utilizando una variedad de sensores y configurar parámetros mediante una página web intuitiva. La estación es compatible con varias APIs para el envío de datos a servicios en la nube como **ThingSpeak**, **Weathercloud**, **Windy**, y **Pwsweather**. 

## Características Principales

- **Sensores Integrados**:
  - **WH-SP-WD**: Sensor de dirección del viento.
  - **WH-SP-WS01**: Sensor de velocidad del viento.
  - **WH-SP-RG**: Sensor de lluvia.
  - **DS18B20**: Sensor de temperatura.
  - **AHT20 + BMP280**: Sensores de temperatura, humedad y presión atmosférica.
  - **BH1750**: Sensor de luz.
  - **CCS811**: Sensor de calidad del aire.
  - **S12SD**: Módulo para lectura de tarjetas SD.
  - **MQ_7**: Sensor de monóxido de carbono.

- **Interfaz Web**:
  - Configuración en tiempo real de los sensores y parámetros de calibración.
  - Configuración de servicios en la nube mediante switches para activar/desactivar:
    - ThingSpeak
    - Weathercloud
    - Windy
    - Pwsweather
  - Ajustes avanzados como dirección I2C y multiplicadores/divisores de los sensores.

- **Conectividad**:
  - Compatible con servicios **MQTT** para la transmisión de datos.
  - Configuración y conexión WiFi mediante **WiFiManager**.

## Uso

1. Conecte los sensores al ESP32 según el esquema provisto.
2. Acceda a la página web desde un navegador para configurar los parámetros.
3. Active los servicios deseados y configure las claves de las APIs.
4. Visualice los datos en tiempo real desde la interfaz web o en las plataformas configuradas.

Este proyecto es ideal para aplicaciones domésticas y profesionales de monitoreo climático. 

Para más información, consulte la [documentación completa](#) o los diagramas incluidos.

---

## Configuración de Pines

La siguiente tabla describe la asignación de pines para los sensores y componentes utilizados en la estación meteorológica:

| **Componente**         | **Pin GPIO** | **Descripción**                                                                                      |
|-------------------------|--------------|------------------------------------------------------------------------------------------------------|
| **WIND_SPD_PIN**        | GPIO 32      | Contador de anemómetro basado en interruptor de láminas.                                             |
| **RAIN_PIN**            | GPIO 25      | Contador de ticks del sensor de lluvia basado en interruptor de láminas en el cubo basculante.       |
| **WIND_DIR_PIN**        | GPIO 35      | Salida de divisor de voltaje variable basada en la variación de la red R con interruptores de láminas. |
| **TEMP_PIN**            | GPIO 4       | Sensor de temperatura DS18B20.                                                                      |
| **LED_BUILTIN**         | GPIO 2/12    | LED integrado para diagnóstico (GPIO 12 para placas más nuevas que no usan zócalos devkit).         |
| **S12SD**               | GPIO 34      | Sensor UV S12SD.                                                                                    |
| **MQ_7**                | GPIO 13      | Sensor de monóxido de carbono MQ7.                                                                  |

### Notas:
- **LED_BUILTIN**: Puede configurarse en **GPIO 12** para placas ESP32 más recientes.
- **S12SD**: Sensor UV conectado al **GPIO 34**.
- Los pines pueden ajustarse según las necesidades del proyecto o la disposición del hardware.

--- 
