#include <iostream>
#include <string>
#include <Arduino.h>
#include "senzor.h"

senzor::senzor(int pin_ales) : pin(pin_ales), dht(pin_ales, DHT11) {}
void senzor::begin() {
    dht.begin();
}
float senzor::citeste_temperatura()
{
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Eroare la citirea senzorului DHT11!");
        return 0.0; 
    }
    return temp;
}