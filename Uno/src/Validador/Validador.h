#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <iostream>
#include <string>
#include "../Pila/Pila.h"
#include "../Carta/Carta.h"
#include "../Jugador/Jugador.h"

class Validador {
public:
    bool validarJugadoresParaRepartir(int totalJugadores) const;
    bool validarInicioTurnos(int totalJugadores, Jugador* jugadorInicial) const;
    bool validarJugadorConCartas(Jugador* jugador, const std::string& mensaje) const;
    bool validarMazoNoVacio(const Pila<Carta*>& mazo, const std::string& mensaje) const;
};

#endif // VALIDADOR_H
