#ifndef LADONUMERO_H
#define LADONUMERO_H

#include "Lado.h"

class LadoNumero : public Lado
{
private:
    int numero;

public:
    LadoNumero(int num);
    virtual ~LadoNumero();

    virtual void aplicarEfecto(Juego& juego) override;
};

#endif // LADONUMERO_H