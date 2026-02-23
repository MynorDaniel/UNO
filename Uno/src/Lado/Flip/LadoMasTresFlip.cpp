#include "LadoMasTresFlip.h"
#include "../../Juego/Juego.h"

LadoMasTresFlip::LadoMasTresFlip(Color color) {
    setColor(color);
}

LadoMasTresFlip::~LadoMasTresFlip() = default;

void LadoMasTresFlip::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un +3 (Flip)." << "\n";
    juego.aplicarMasTresFlip();
}

bool LadoMasTresFlip::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoMasTresFlip*>(&otro) != nullptr;
}

std::string LadoMasTresFlip::toString() const {
    return "| +3 " + std::string(colorToString(getColor())) + " (Flip) |";
}
