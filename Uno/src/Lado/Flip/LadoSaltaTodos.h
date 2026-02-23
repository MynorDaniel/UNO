#ifndef LADO_SALTA_TODOS_H
#define LADO_SALTA_TODOS_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoSaltaTodos : public Lado {
public:
    LadoSaltaTodos(Color color);
    ~LadoSaltaTodos() override;

    void aplicarEfecto(Juego& juego) override;
    bool esCompatible(const Lado& otro) const override;
    std::string toString() const override;
};

#endif // LADO_SALTA_TODOS_H
