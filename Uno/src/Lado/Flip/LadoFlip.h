#ifndef LADO_FLIP_H
#define LADO_FLIP_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoFlip : public Lado {
public:
    LadoFlip(Color color);
    ~LadoFlip() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_FLIP_H
