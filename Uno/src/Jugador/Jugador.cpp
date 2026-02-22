#include "Jugador.h"
#include "../Juego/Juego.h"
#include "../Lado/LadoComodin.h"
#include "../Lado/LadoMasCuatro.h"
#include "../Lado/LadoMasDos.h"
#include "../Lado/LadoNumero.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre, Juego* juego, Pila<Carta*>* mazo, Pila<Carta*>* descarte)
    : nombre(nombre), juego(juego), mazo(mazo), descarte(descarte)
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

bool Jugador::tieneCartaCompatible(const Lado& tope)
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
        if (ladoActual != nullptr && ladoActual->esCompatible(tope)) {
            return true;
        }
    }
    return false;
}

bool Jugador::jugarCarta(int indice, const Lado& tope)
{
    if (indice < 0 || indice >= cartas.getLongitud()) {
        return false;
    }

    Carta* carta = cartas.get(indice);
    Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
    if (ladoActual == nullptr || !ladoActual->esCompatible(tope)) {
        return false;
    }

    cartas.eliminar(indice);
    if (descarte != nullptr) {
        descarte->insertar(carta);
    }
    std::cout << nombre << " descarta: "
              << carta->getLadoActual()->toString() << "\n";
    if (juego != nullptr) {
        Lado* ladoActual = carta->getLadoActual();
        if (ladoActual != nullptr &&
            (dynamic_cast<LadoComodin*>(ladoActual) != nullptr ||
             dynamic_cast<LadoMasCuatro*>(ladoActual) != nullptr)) {
            Color colorElegido = juego->pedirColorCarta(nombre);
            ladoActual->setColor(colorElegido);
        }

        if (ladoActual != nullptr && dynamic_cast<LadoMasCuatro*>(ladoActual) != nullptr) {
            juego->registrarMasCuatro(this, tope);
        }

        carta->aplicarEfecto(*juego);
    }
    return true;
}

void Jugador::manejarSinCompatibles(const Lado& tope)
{
    std::cout << nombre << " no tiene cartas compatibles.\n";

    if (mazo == nullptr || mazo->isEmpty()) {
        std::cout << "El mazo está vacío. Se pasa el turno.\n";
        return;
    }

    bool roboSinLimite = juego != nullptr && juego->isModoRoboSinLimite();

    do {
        Carta* cartaRobada = mazo->sacar();
        tomarCarta(cartaRobada);
        std::cout << nombre << " roba: "
                  << cartaRobada->getLadoActual()->toString() << "\n";

        if (cartaRobada->getLadoActual()->esCompatible(tope)) {
            std::cout << "La carta robada es compatible y se juega automáticamente.\n";
            int indiceRobada = getCantidadCartas() - 1;
            jugarCarta(indiceRobada, tope);
            return;
        }
    } while (roboSinLimite && mazo != nullptr && !mazo->isEmpty());
}

void Jugador::robarCartas(int cantidad)
{
    if (mazo == nullptr) {
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (mazo->isEmpty()) {
            std::cout << "El mazo se quedó sin cartas.\n";
            break;
        }
        Carta* carta = mazo->sacar();
        tomarCarta(carta);
    }
}

bool Jugador::tieneCartaDeColor(Color color) const
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        Lado* lado = carta ? carta->getLadoActual() : nullptr;
        if (lado != nullptr && lado->getColor() == color) {
            return true;
        }
    }
    return false;
}

bool Jugador::tieneCartaNumero(int numero) const
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        LadoNumero* ladoNumero = carta ? dynamic_cast<LadoNumero*>(carta->getLadoActual()) : nullptr;
        if (ladoNumero != nullptr && ladoNumero->getNumero() == numero) {
            return true;
        }
    }
    return false;
}

bool Jugador::tieneCartaAcumulable(const Lado& tope) const
{
    const bool topeMasDos = dynamic_cast<const LadoMasDos*>(&tope) != nullptr;
    const bool topeMasCuatro = dynamic_cast<const LadoMasCuatro*>(&tope) != nullptr;

    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        Lado* lado = carta ? carta->getLadoActual() : nullptr;
        if (lado == nullptr) {
            continue;
        }

        if (topeMasDos && dynamic_cast<LadoMasDos*>(lado) != nullptr) {
            return true;
        }

        if (topeMasCuatro && dynamic_cast<LadoMasCuatro*>(lado) != nullptr) {
            return true;
        }
    }

    return false;
}

int Jugador::getCantidadCartas() const
{
    return cartas.getLongitud();
}

std::string Jugador::getNombre() const
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
