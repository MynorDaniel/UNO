#ifndef LADO_MAS_TRES_FLIP_H
#define LADO_MAS_TRES_FLIP_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoMasTresFlip : public Lado {
public:
    LadoMasTresFlip(Color color);
    ~LadoMasTresFlip() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_MAS_TRES_FLIP_H
