#include "LadoFlip.h"
#include "../../Juego/Juego.h"

LadoFlip::LadoFlip(Color color) {
    setColor(color);
}

LadoFlip::~LadoFlip() = default;

void LadoFlip::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un Flip." << "\n";
    juego.aplicarFlip();
}

bool LadoFlip::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoFlip*>(&otro) != nullptr;
}

std::string LadoFlip::toString() const {
    return "| Flip " + std::string(colorToString(getColor())) + " |";
}
