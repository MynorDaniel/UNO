#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre)
        : nombre(nombre)
{
}

Jugador::~Jugador()
{
    int total = cartas.getLongitud();
    for (int i = 0; i < total; i++) {
        Carta* carta = cartas.get(i);
        delete carta;
    }
}

void Jugador::tomarCarta(Carta* carta)
{
    cartas.agregar(carta);
}

void Jugador::mostrarCartas()
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        if (carta != nullptr && carta->getLadoActual() != nullptr) {
            std::cout << carta->getLadoActual()->toString() << "\n";
        }
    }
}

int Jugador::getCantidadCartas()
{
    return cartas.getLongitud();
}

std::string Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre(const std::string& nuevoNombre)
{
    nombre = nuevoNombre;
}

Lista<Carta*>& Jugador::getCartas()
{
    return cartas;
}
