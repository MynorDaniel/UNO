#include "Validador.h"

bool Validador::validarJugadoresParaRepartir(int totalJugadores) const {
    if (totalJugadores <= 0) {
        std::cout << "No hay jugadores para repartir cartas." << std::endl;
        return false;
    }
    return true;
}

bool Validador::validarInicioTurnos(int totalJugadores, Jugador* jugadorInicial) const {
    if (totalJugadores <= 0) {
        std::cout << "No hay jugadores para iniciar la partida." << std::endl;
        return false;
    }
    if (jugadorInicial == nullptr) {
        std::cout << "No se pudo determinar el jugador inicial." << std::endl;
        return false;
    }
    return true;
}

bool Validador::validarJugadorConCartas(Jugador* jugador, const std::string& mensaje) const {
    if (jugador == nullptr || jugador->getCantidadCartas() == 0) {
        std::cout << mensaje << std::endl;
        return false;
    }
    return true;
}

bool Validador::validarMazoNoVacio(const Pila<Carta*>& mazo, const std::string& mensaje) const {
    if (mazo.isEmpty()) {
        std::cout << mensaje << std::endl;
        return false;
    }
    return true;
}
