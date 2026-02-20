#ifndef CARTA_H
#define CARTA_H

#include "../Lado/Lado.h"

class Juego;

class Carta
{
private:
    Lado* ladoClaro;
    Lado* ladoOscuro;
    Lado* ladoActual;

public:
    Carta(Lado* claro, Lado* oscuro);
    ~Carta();
    void voltear();
    void aplicarEfecto(Juego& juego);
    Lado* getLadoActual() const;
};

#endif // CARTA_H