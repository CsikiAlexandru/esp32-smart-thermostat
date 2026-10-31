#ifndef TERMOSTAT_H
#define TERMOSTAT_H
#include<Arduino.h>

using namespace std;

class termostat
{
    int pin=0;
    float prag_temperatura=20.0;
    bool stare_curenta=0;
public:
    termostat() = delete;
    termostat(int , float);
    termostat(const termostat &sursa) { *this = sursa; }
    termostat &operator=(const termostat &) = default;
    ~termostat();
    bool get_stare() const;
    float get_prag()const;
    void modificare_stare(float );
    void evaluare(float); 
    friend void acces_termostat(const termostat& );
};



#endif