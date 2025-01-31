// Índice de calor (Heat Index)
float calculateHeatIndex(float tempC, float humidity) {
    float tempF = (tempC * 9.0 / 5.0) + 32;
    float hiF = -42.379 + 2.04901523 * tempF + 10.14333127 * humidity 
              - 0.22475541 * tempF * humidity - 6.83783e-3 * tempF * tempF 
              - 5.481717e-2 * humidity * humidity + 1.22874e-3 * tempF * tempF * humidity 
              + 8.5282e-4 * tempF * humidity * humidity - 1.99e-6 * tempF * tempF * humidity * humidity;
    return (hiF - 32) * 5.0 / 9.0; // Convertir a Celsius
}

// Sensación térmica (Wind Chill)
float calculateWindChill(float tempC, float windSpeed) {
    return 13.12 + 0.6215 * tempC - 11.37 * pow(windSpeed, 0.16) 
         + 0.3965 * tempC * pow(windSpeed, 0.16);
}

// Punto de rocío (Dew Point)
float calculateDewPoint(float tempC, float humidity) {
    float a = 17.27;
    float b = 237.7;
    float alpha = (a * tempC) / (b + tempC) + log(humidity / 100.0);
    return (b * alpha) / (a - alpha);
}

// Altitud Barométrica
float calculateAltitude(float pressure) {
    return 44330 * (1.0 - pow(pressure / 1013.25, 1 / 5.255));
}

// Índice de Calidad del Aire (AQI)
int calculateAQI(float co, float eco2, float tvoc) {
    // Implementar lógica AQI según estándares locales
    int aqiCo = map(co, 0, 50, 0, 100);       // Ejemplo simplificado
    int aqiEco2 = map(eco2, 400, 2000, 0, 100);
    int aqiTvoc = map(tvoc, 0, 500, 0, 100);
    return max(aqiCo, max(aqiEco2, aqiTvoc));
}

// Evapotranspiración (ET0)
float calculateET0(float temp, float humidity, float pressure, float solarRad) {
    // Implementación simplificada de Penman-Monteith
    float netRad = solarRad * 0.0864; // Conversión W/m² a MJ/m²/día
    float ea = 0.6108 * exp((17.27 * temp) / (temp + 237.3)) * (humidity / 100);
    float es = 0.6108 * exp((17.27 * temp) / (temp + 237.3));
    float vpd = es - ea;
    return (0.408 * netRad + 37 * vpd) / (temp + 273) * 0.0023;
}

// -------------------------------------------------------------------
// En loop principal
// -------------------------------------------------------------------
void updateCalculations() {
    sensor.heatIndex = calculateHeatIndex(sensor.temperatureAHT, sensor.humidity);
    sensor.windChill = calculateWindChill(sensor.temperatureC, sensor.windSpeed);
    sensor.dewPoint = calculateDewPoint(sensor.temperatureAHT, sensor.humidity);
    sensor.aqi = calculateAQI(analogRead(MQ_7), sensor.co2, sensor.tvoc);
    sensor.et0 = calculateET0(sensor.temperatureAHT, sensor.humidity, 
                            sensor.barometricPressure, sensor.lux);
    sensor.altitude = calculateAltitude(sensor.barometricPressure);
    sensor.cloudIndex = (sensor.lux / 120000.0) * 100; // Ejemplo simplificado
}