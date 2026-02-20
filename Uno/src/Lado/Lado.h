#ifndef LADO_H
#define LADO_H

#include <string>
#include <iostream>

class Juego;

class Lado
{
private:
    /* data */
public:
    Lado();
    virtual ~Lado();

    virtual void aplicarEfecto(Juego& juego) = 0;

    virtual bool esCompatible(const Lado& otro) const = 0;

    virtual std::string toString() const = 0;
};
#endif // LADO_H