// Constantes para mejor legibilidad y mantenimiento
constexpr uint32_t ONE_HOUR_MS = 3600000UL;
constexpr uint32_t ONE_MINUTE_MS = 60000UL;

// Configuración de lluvia y tiempo
struct RainConfig {
    float mmPerTick = 0.27945f;
    uint32_t debounceTime = 300;
    uint8_t resetHour = 0;
    uint8_t resetMinute = 9;
};

RainConfig rainConfig;  // Instancia de configuración

// Mutex para manejo de la ISR
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

// Función ISR optimizada con protección crítica
void IRAM_ATTR contadorLitros() {
    portENTER_CRITICAL_ISR(&mux);
    static uint32_t lastInterruptTime = 0;
    uint32_t currentTime = millis();

    // Debounce mecánico y temporal
    if (currentTime - lastInterruptTime > rainConfig.debounceTime) {
        ISRContador++;
        lastInterruptTime = currentTime;
        lastRainTime = currentTime;  // Para detección de bloqueo
    }
    portEXIT_CRITICAL_ISR(&mux);
}

// Función para manejo de arrays circular
template<typename T, size_t N>
void shiftArrayRight(T (&arr)[N]) {
    for (size_t i = N - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    arr[0] = 0;
}

void rainloop() {
    uint32_t currentMillis = millis();
    static uint32_t lastHourCheck = currentMillis;
    static uint32_t lastMinuteCheck = currentMillis;

    // Detección de bloqueo del pluviómetro
    if (currentMillis - lastMaintenanceCheck >= ONE_HOUR_MS) {
        if (currentMillis - lastRainTime > ONE_HOUR_MS) {
#ifdef SerialMonitor
            Serial.println("Alerta: Pluviómetro posiblemente bloqueado");
#endif
        }
        lastMaintenanceCheck = currentMillis;
    }

    // Procesamiento horario
    if (currentMillis - lastHourCheck >= ONE_HOUR_MS) {
        // Calcular lluvia en la última hora
        rainData.intervalRainfall = ISRContador * rainConfig.mmPerTick;
        
        // Actualizar histórico horario
        shiftArrayRight(rainData.hourlyRainfall);
        rainData.hourlyRainfall[0] = rainData.intervalRainfall;
        
        // Actualizar acumulados
        rainData.hourlyCarryover += rainData.intervalRainfall;
        rainData.priorHour = rainData.intervalRainfall;
        
        // Actualizar sensores
        // Actualizar sensores aquí como sensor.rainTicks24h si es necesario
        
#ifdef SerialMonitor
        Serial.printf("Lluvia última hora: %.2f mm\n", rainData.intervalRainfall);
        Serial.printf("Lluvia total día: %.2f mm\n", rainData.hourlyCarryover);
#endif

        // Reiniciar contadores
        ISRContador = 0;
        lastHourCheck = currentMillis;
    }

    // Procesamiento por minuto
    if (currentMillis - lastMinuteCheck >= ONE_MINUTE_MS) {
        // Actualizar histórico de minutos
        shiftArrayRight(rainData.current60MinRainfall);
        rainData.current60MinRainfall[0] = rainData.intervalRainfall;
        
        // Actualizar acumulados por minuto
        rainData.minuteCarryover = rainData.intervalRainfall + rainData.priorMinute;
        rainData.priorMinute = rainData.intervalRainfall;
        
        lastMinuteCheck = currentMillis;
    }

    // Reinicio diario a las 00:09
    if (timeClient.getHours() == rainConfig.resetHour && timeClient.getMinutes() == rainConfig.resetMinute) {
        memset(rainData.hourlyRainfall, 0, sizeof(rainData.hourlyRainfall));
        rainData.intervalRainfall = 0;
        rainData.hourlyCarryover = 0;
        rainData.priorHour = 0;
        rainData.minuteCarryover = 0;
        rainData.priorMinute = 0;

#ifdef SerialMonitor
        Serial.println("Datos de lluvia reiniciados para nuevo día");
#endif
    }
}