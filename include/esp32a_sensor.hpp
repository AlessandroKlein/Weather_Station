// Configuración de sensores
struct SensorConfig {
    uint8_t bmpAddress = 0x76;  // Dirección I2C por defecto
    uint16_t readInterval = 1000;  // Intervalo de lectura en ms
    float uvVoltageRef = 3.3f;    // Voltaje de referencia para UV
    uint16_t uvAdcResolution = 4095;  // Resolución ADC
};

SensorConfig sensorConfig;

// Clase wrapper para manejo de sensores
class SensorManager {
public:
    SensorManager() : oneWire(TEMP_PIN), temperatureSensor(&oneWire) {}

    void begin() {
        initializeI2C();
        setupDS18B20();
        setupAHTBMP();
        setupBH1750();
        setupCCS811();
    }

    void readAll() {
        static uint32_t lastRead = 0;
        if (millis() - lastRead >= sensorConfig.readInterval) {
            readDS18B20();
            readAHTBMP();
            readBH1750();
            readCCS811();
            readUV();
            lastRead = millis();
        }
    }

private:
    // Instancias de sensores
    OneWire oneWire;
    DallasTemperature temperatureSensor;

    void initializeI2C() {
#ifdef heltec
        Wire.begin(21, 22);
#else
        Wire.begin();
#endif
        Wire.setClock(400000);  // Fast mode
    }

    void setupDS18B20() {
        temperatureSensor.begin();
        temperatureSensor.setWaitForConversion(false);
#ifdef SerialMonitor
        Serial.println("DS18B20 inicializado");
#endif
    }

    void readDS18B20() {
        temperatureSensor.requestTemperatures();
        sensor.temperatureC = temperatureSensor.getTempCByIndex(0);
        
#ifdef SerialMonitor
        if (sensor.temperatureC != DEVICE_DISCONNECTED_C) {
            Serial.printf("Temperatura DS18B20: %.2f °C\n", sensor.temperatureC);
        } else {
            Serial.println("Error DS18B20");
        }
#endif
    }

    void setupAHTBMP() {
#ifdef AHTX0BMP280
        if (!aht.begin()) {
            handleSensorError("AHT20");
        }

        if (!bmp.begin(sensorConfig.bmpAddress)) {
            if (!bmp.begin(0x77)) {
                handleSensorError("BMP280");
            }
        }
#ifdef SerialMonitor
        Serial.println("Sensores AHT20 y BMP280 inicializados");
#endif
#endif
    }

    void readAHTBMP() {
#ifdef AHTX0BMP280
        sensors_event_t humidityEvent, tempEvent;
        if (aht.getEvent(&humidityEvent, &tempEvent)) {
            sensor.temperatureAHT = tempEvent.temperature;
            sensor.humidity = humidityEvent.relative_humidity;
            sensor.barometricPressure = bmp.readPressure() / 100.0F;
            sensor.temperatureBMP = bmp.readTemperature();

#ifdef SerialMonitor
            Serial.printf("AHT20: %.2f °C, %.2f %%\n", sensor.temperatureAHT, sensor.humidity);
            Serial.printf("BMP280: %.2f °C, %.2f hPa\n", sensor.temperatureBMP, sensor.barometricPressure);
#endif
        }
#endif
    }

    void setupBH1750() {
#ifdef BH1750
        if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
            handleSensorError("BH1750");
        }
#ifdef SerialMonitor
        Serial.println("BH1750 inicializado");
#endif
#endif
    }

    void readBH1750() {
#ifdef BH1750
        sensor.lux = lightMeter.readLightLevel();
#ifdef SerialMonitor
        if (sensor.lux >= 0) {
            Serial.printf("Luz: %.2f lux\n", sensor.lux);
        } else {
            Serial.println("Error BH1750");
        }
#endif
#endif
    }

    void setupCCS811() {
#ifdef CCS811
        if (!ccs.begin()) {
            handleSensorError("CCS811");
        }
        if (ccs.checkForStatusError()) {
            handleSensorError("CCS811 status");
        }
#ifdef SerialMonitor
        Serial.println("CCS811 inicializado");
#endif
#endif
    }

    void readCCS811() {
#ifdef CCS811
        if (ccs.available() && !ccs.readData()) {
            sensor.co2 = ccs.geteCO2();
            sensor.tvoc = ccs.getTVOC();
#ifdef SerialMonitor
            Serial.printf("CO2: %.0f ppm, TVOC: %.0f ppb\n", sensor.co2, sensor.tvoc);
#endif
        }
#endif
    }

    void readUV() {
        int uvValue = analogRead(S12SD);
        sensor.UVIndex = convertToUVIndex(uvValue);
#ifdef SerialMonitor
        Serial.printf("UV Index: %.1f\n", sensor.UVIndex);
#endif
    }

    float convertToUVIndex(int adcValue) {
        const float voltage = (adcValue * sensorConfig.uvVoltageRef) / sensorConfig.uvAdcResolution;
        static const float uvThresholds[] = {0.05, 0.227, 0.318, 0.408, 0.503, 
                                           0.606, 0.696, 0.795, 0.881, 0.976, 1.079};
        
        for (uint8_t i = 0; i < sizeof(uvThresholds)/sizeof(uvThresholds[0]); i++) {
            if (voltage < uvThresholds[i]) {
                return i;
            }
        }
        return 11;
    }

    void handleSensorError(const char* sensorName) {
#ifdef SerialMonitor
        Serial.printf("Error inicializando %s\n", sensorName);
#endif
        // Aquí podrías implementar un sistema de reintentos o notificaciones
    }
};

// Instancia global del manejador de sensores
SensorManager sensorManager;

void initializeSensors() {
    sensorManager.begin();
}

void loopSensors() {
    sensorManager.readAll();
}