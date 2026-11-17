#include <iostream>
#include <string>
#include <Arduino.h>
#include "senzor.h"

float SenzorDHT::citeste_temperatura()
{
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Eroare la citirea senzorului DHT11!");
        return 0.0; 
    }
    return temp;
}
float SenzorDHT::citeste_umiditate() {
    float hum = dht.readHumidity();
    if (isnan(hum)) {
        Serial.println("Eroare la citirea umiditatii DHT11!");
        return 0.0;
    }
    return hum;
}