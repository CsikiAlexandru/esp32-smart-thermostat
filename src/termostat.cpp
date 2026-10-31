#include <Arduino.h>

#include "termostat.h"
using namespace std;

termostat::termostat(int pin, float prag_temperatura)
{
    this->pin = pin;
    this->prag_temperatura = prag_temperatura;
    this->stare_curenta = 0;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}
termostat::~termostat()
{
    digitalWrite(pin, LOW);
}
bool termostat::get_stare() const
{
    return this->stare_curenta;
}
void termostat::modificare_stare(float prag_nou)
{
    this->prag_temperatura = prag_nou;
}
void termostat::evaluare(float temperatura_citia)
{
    if (temperatura_citia >= this->prag_temperatura)
    {
        this->stare_curenta = 1;
        digitalWrite(this->pin, HIGH);
    }
    else
    {
        this->stare_curenta = 0;
        digitalWrite(this->pin, LOW);
    }
}
void acces_termostat(const termostat& ob)
{
Serial.println(ob.pin);
Serial.println(ob.prag_temperatura);
Serial.println(ob.stare_curenta);

}
float termostat::get_prag() const
{
    return this->prag_temperatura;
}





