#pragma once
#include <Arduino.h>

// Configuración optimizada para IRAM
#define WIND_SPD_PIN 32
#define WIND_DIR_PIN 35

namespace WindConfig {
    constexpr uint8_t DEBOUNCE_MS = 50;
    constexpr float ANEM_FACTOR = 2.4f;
    constexpr uint16_t ADC_SAMPLES = 5;
    constexpr uint16_t DIR_THRESHOLDS[] = {100, 200, 300, 400, 500, 600, 700, 800};
}

class Anemometer {
public:
    static void IRAM_ATTR isrHandler();

    static void begin() {
        pinMode(WIND_SPD_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN), isrHandler, RISING);
    }

    static void measure() {
        noInterrupts();
        uint32_t currentCount = pulseCount;
        pulseCount = 0;
        interrupts();

        uint32_t currentTime = millis();
        float elapsed = (currentTime - lastMeasure) / 1000.0f;
        
        if(elapsed > 0) {
            currentSpeed = currentCount * WindConfig::ANEM_FACTOR / elapsed;
            if(currentSpeed > maxSpeed) maxSpeed = currentSpeed;
        }
        lastMeasure = currentTime;
    }

    static float getSpeed() { return currentSpeed; }
    static float getMaxSpeed() { return maxSpeed; }

private:
    static volatile uint32_t pulseCount;
    static uint32_t lastMeasure;
    static float currentSpeed;
    static float maxSpeed;
};

// Inicialización de miembros estáticos
volatile uint32_t Anemometer::pulseCount = 0;
uint32_t Anemometer::lastMeasure = 0;
float Anemometer::currentSpeed = 0;
float Anemometer::maxSpeed = 0;

// Implementación del ISR fuera de la clase
void IRAM_ATTR Anemometer::isrHandler() {
    static uint32_t lastInterrupt = 0;
    uint32_t now = xTaskGetTickCountFromISR() * portTICK_PERIOD_MS;
    
    if(now - lastInterrupt > WindConfig::DEBOUNCE_MS) {
        pulseCount++;
        lastInterrupt = now;
    }
}

class WindVane {
public:
    void begin() {
        pinMode(WIND_DIR_PIN, INPUT);
        for(uint8_t i = 0; i < WindConfig::ADC_SAMPLES; i++) {
            updateSamples();
        }
    }

    void update() {
        static uint32_t lastUpdate = 0;
        if(millis() - lastUpdate >= 100) {
            updateSamples();
            lastUpdate = millis();
        }
    }

    float getDirection() const {
        const float DIR_ANGLES[] = {0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f, 360.0f};
        return DIR_ANGLES[getDirectionIndex()];
    }

    int getRawADC() const { return filteredADC; }

private:
    int samples[WindConfig::ADC_SAMPLES] = {0};
    uint8_t sampleIndex = 0;
    int filteredADC = 0;

    void updateSamples() {
        samples[sampleIndex] = analogRead(WIND_DIR_PIN);
        sampleIndex = (sampleIndex + 1) % WindConfig::ADC_SAMPLES;
        
        int sum = 0;
        for(uint8_t i = 0; i < WindConfig::ADC_SAMPLES; i++) {
            sum += samples[i];
        }
        filteredADC = sum / WindConfig::ADC_SAMPLES;
    }

    uint8_t getDirectionIndex() const {
        for(uint8_t i = 0; i < sizeof(WindConfig::DIR_THRESHOLDS)/sizeof(WindConfig::DIR_THRESHOLDS[0]); i++) {
            if(filteredADC < WindConfig::DIR_THRESHOLDS[i]) {
                return i;
            }
        }
        return sizeof(WindConfig::DIR_THRESHOLDS)/sizeof(WindConfig::DIR_THRESHOLDS[0]);
    }
};

WindVane windVane;

void initWindSensors() {
    Anemometer::begin();
    windVane.begin();
}

void updateWindSensors() {
    Anemometer::measure();
    windVane.update();
}