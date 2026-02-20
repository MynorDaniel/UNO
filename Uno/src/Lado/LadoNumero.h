#ifndef LADONUMERO_H
#define LADONUMERO_H

#include "Lado.h"
#include <string>

class Juego;

class LadoNumero : public Lado
{
private:
    int numero;

public:
    LadoNumero(int num);
    virtual ~LadoNumero();

    virtual void aplicarEfecto(Juego& juego) override;

    virtual bool esCompatible(const Lado& otro) const override;

    virtual std::string toString() const override;
};

#endif // LADONUMERO_H