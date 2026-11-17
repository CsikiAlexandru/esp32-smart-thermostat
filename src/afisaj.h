#ifndef AFISAJ_H
#define AFISAJ_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class afisaj {
private:
    Adafruit_SSD1306 display;

public:
    afisaj();
    bool begin();
    void afiseaza_mesaj(const String& linie1, const String& linie2 = "");
    void actualizeaza(float temp, float umiditate, float prag, bool stare_actuator, const String& ip);
};

#endif