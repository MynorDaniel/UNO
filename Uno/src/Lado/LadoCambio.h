#ifndef LADO_CAMBIO_H
#define LADO_CAMBIO_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoCambio : public Lado {
public:
    LadoCambio(Color color);
    ~LadoCambio() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_CAMBIO_H
