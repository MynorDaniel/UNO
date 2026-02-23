#ifndef LADO_MAS_SEIS_FLIP_H
#define LADO_MAS_SEIS_FLIP_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoMasSeisFlip : public Lado {
public:
    LadoMasSeisFlip(Color color);
    ~LadoMasSeisFlip() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_MAS_SEIS_FLIP_H
