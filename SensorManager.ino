//#pragma once
#include "config.h"
#include <functional>

class SensorManager {
private:
    SensorConfig config;
    ValidRanges ranges;
    
    // Buffers para filtrado
    CircularBuffer<float> tempBuffer;
    CircularBuffer<float> humidityBuffer;
    CircularBuffer<float> pressureBuffer;
    CircularBuffer<float> windSpeedBuffer;
    
    // Estado del último error
    struct SensorError {
        bool hasError;
        String message;
        unsigned long timestamp;
    } lastError;

    // Función auxiliar para validar lecturas
    template<typename T>
    bool isValidReading(T value, T min, T max, T lastValue, T maxDelta) {
        if (value < min || value > max) return false;
        if (lastValue != T() && abs(value - lastValue) > maxDelta) return false;
        return true;
    }

public:
    struct SensorData {
        float temperature;
        float humidity;
        float pressure;
        float windSpeed;
        float windDirection;
        float rain;
        float uvIndex;
        float light;
        unsigned long timestamp;
        bool isValid;
    };

    SensorData readSensors() {
        SensorData data = {};
        data.timestamp = millis();
        data.isValid = true;
        
        // Leer cada sensor con reintentos y validación
        for (int i = 0; i < config.maxRetries && data.isValid; i++) {
            // Temperatura
            float temp = temperatureSensor.getTempCByIndex(0);
            if (isValidReading(temp, ranges.minTemp, ranges.maxTemp, 
                             tempBuffer.getMedian(), config.maxTempDelta)) {
                data.temperature = temp;
                tempBuffer.push(temp);
            } else if (i == config.maxRetries - 1) {
                setError("Temperature reading invalid", data.timestamp);
                data.isValid = false;
            }
            
            // Similar para otros sensores...
        }
        
        return data;
    }

    bool hasError() const { return lastError.hasError; }
    String getLastError() const { return lastError.message; }
    
private:
    void setError(const String& message, unsigned long timestamp) {
        lastError = {true, message, timestamp};
    }
};

// Crear una instancia del gestor de sensores
SensorManager sensorManager;