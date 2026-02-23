#include "LadoCambio.h"
#include "../Juego/Juego.h"

LadoCambio::LadoCambio(Color color) {
    setColor(color);
}

LadoCambio::~LadoCambio() = default;

void LadoCambio::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un Cambio." << "\n";
    juego.intercambiarCartasConAnterior();
}

bool LadoCambio::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoCambio*>(&otro) != nullptr;
}

std::string LadoCambio::toString() const {
    return "| Cambio " + std::string(colorToString(getColor())) + " |";
}
