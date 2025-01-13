#pragma once

//Hardware build target: ESP32
#define VERSION "0.0.4"
#define DEVICE_NAME "Weather_Station"

// Intervalos de tiempo (ms)
const unsigned long MEASUREMENT_INTERVAL = 300000;  // 5 minutos
const unsigned long RETRY_DELAY = 1000;            // 1 segundo entre reintentos
const unsigned long WDT_TIMEOUT = 30000;           // 30 segundos timeout watchdog

// Configuración de sensores
struct SensorConfig {
    const int maxRetries = 3;             // Máximo número de reintentos por sensor
    const float maxTempDelta = 5.0;       // Máximo cambio de temperatura permitido entre lecturas
    const float maxHumidityDelta = 10.0;  // Máximo cambio de humedad permitido
    const float maxPressureDelta = 5.0;   // Máximo cambio de presión permitido
    const float windSpeedThreshold = 200.0; // Velocidad máxima del viento razonable
    
    // Calibración
    const float windSpeedCalibration = 2.4;  // Factor de calibración anemómetro
    const float rainCalibration = 0.27945;   // mm por tick del pluviómetro
};

// Rangos válidos para las mediciones
struct ValidRanges {
    const float minTemp = -40.0;
    const float maxTemp = 60.0;
    const float minHumidity = 0.0;
    const float maxHumidity = 100.0;
    const float minPressure = 800.0;
    const float maxPressure = 1200.0;
    const float minWindSpeed = 0.0;
    const float maxWindSpeed = 200.0;
};

// Buffer circular para filtrado de datos
template<typename T>
class CircularBuffer {
    static const int SIZE = 5;
    T buffer[SIZE];
    int head = 0;
    int count = 0;

public:
    void push(T value) {
        buffer[head] = value;
        head = (head + 1) % SIZE;
        if (count < SIZE) count++;
    }

    T getMedian() {
        if (count == 0) return T();
        
        // Copiar valores para ordenar
        T temp[SIZE];
        for(int i = 0; i < count; i++) {
            temp[i] = buffer[i];
        }
        
        // Ordenar
        for(int i = 0; i < count-1; i++) {
            for(int j = 0; j < count-i-1; j++) {
                if(temp[j] > temp[j+1]) {
                    T t = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = t;
                }
            }
        }
        
        return temp[count/2];
    }
};