#ifndef CARTA_H
#define CARTA_H

#include "../Lado/Lado.h"

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
};

#endif // CARTA_H