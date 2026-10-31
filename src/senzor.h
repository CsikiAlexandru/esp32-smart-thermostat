#ifndef SENZOR_H
#define SENZOR_H
#include <iostream>
#include <Arduino.h>
#include <string>
#include <DHT.h>
using namespace std;
class senzor
{
    int pin = 0;
    DHT dht;

public:
    senzor(int);
    senzor() = delete;
    senzor(const senzor &sursa) = default;
    senzor &operator=(const senzor &) = default;
    ~senzor() = default;

    void begin();
    float citeste_temperatura();
};

#endif