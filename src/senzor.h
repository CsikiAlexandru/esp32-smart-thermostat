#ifndef SENZOR_H
#define SENZOR_H
#include <iostream>
#include <Arduino.h>
#include <string>
#include <DHT.h>
using namespace std;
class Senzor {
protected:
    int pin;
public:
    Senzor(int pin_ales) : pin(pin_ales) {}
    virtual void begin() = 0;
    virtual ~Senzor() = default;
};

// Clasa derivată pentru DHT11
class SenzorDHT : public Senzor {
private:
    DHT dht;
public:
    SenzorDHT(int pin_ales) : Senzor(pin_ales), dht(pin_ales, DHT11) {}
    void begin() override { dht.begin(); }
    float citeste_temperatura();
    float citeste_umiditate();
};

// Clasa derivată pentru senzor de mișcare PIR
class SenzorPIR : public Senzor {
public:
    SenzorPIR(int pin_ales) : Senzor(pin_ales) {}
    void begin() override { pinMode(pin, INPUT); }
    bool detecteaza_miscare() const { return digitalRead(pin) == HIGH; }
};

#endif