#ifndef LADO_H
#define LADO_H

#include "../Juego/Juego.h"

class Lado
{
private:
    /* data */
public:
    Lado();
    virtual ~Lado();

    virtual void aplicarEfecto(Juego& juego) = 0;
};
#endif // LADO_H