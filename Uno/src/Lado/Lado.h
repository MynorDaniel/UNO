#ifndef LADO_H
#define LADO_H

#include <string>
#include <iostream>
#include "../Color/Color.h"

class Juego;

class Lado
{
private:
    Color color;
public:
    Lado();
    virtual ~Lado();

    virtual void aplicarEfecto(Juego& juego) = 0;

    virtual bool esCompatible(const Lado& otro) const = 0;

    virtual std::string toString() const = 0;

    Color getColor() const;
    void setColor(Color nuevoColor);
};
#endif // LADO_H