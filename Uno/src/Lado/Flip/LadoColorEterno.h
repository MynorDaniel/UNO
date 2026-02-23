#ifndef LADO_COLOR_ETERNO_H
#define LADO_COLOR_ETERNO_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoColorEterno : public Lado {
public:
    LadoColorEterno();
    ~LadoColorEterno() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_COLOR_ETERNO_H
