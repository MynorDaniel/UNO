#ifndef LADO_RAYOSX_H
#define LADO_RAYOSX_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoRayosX : public Lado {
public:
    LadoRayosX(Color color);
    ~LadoRayosX() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_RAYOSX_H
