#include "LadoNumero.h"

LadoNumero::LadoNumero(int num, Color color) : numero(num) {
    setColor(color);
}

LadoNumero::~LadoNumero() {}

void LadoNumero::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un número: " << numero << "\n";
}

bool LadoNumero::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor) {
        return true;
    }

    if (otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    const LadoNumero* otroNumero = dynamic_cast<const LadoNumero*>(&otro);
    return otroNumero != nullptr && otroNumero->numero == numero;
}

std::string LadoNumero::toString() const {
    return "| " + std::to_string(numero) + " " + colorToString(getColor()) + " |";
}

int LadoNumero::getNumero() const {
    return numero;
}