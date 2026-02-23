#include "LadoMasDosFlip.h"
#include "../../Juego/Juego.h"

LadoMasDosFlip::LadoMasDosFlip(Color color) {
    setColor(color);
}

LadoMasDosFlip::~LadoMasDosFlip() = default;

void LadoMasDosFlip::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un +2 (Flip)." << "\n";
    juego.aplicarMasDosFlip();
}

bool LadoMasDosFlip::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoMasDosFlip*>(&otro) != nullptr;
}

std::string LadoMasDosFlip::toString() const {
    return "| +2 " + std::string(colorToString(getColor())) + " (Flip) |";
}
