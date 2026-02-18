#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre)
        : nombre(nombre)
{
}

Jugador::~Jugador()
{
}

void Jugador::tomarCarta(const Carta& carta)
{
    cartas.agregar(carta);
}

void Jugador::mostrarCartas()
{
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
