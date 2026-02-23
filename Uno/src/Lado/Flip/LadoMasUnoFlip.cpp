#include "LadoMasUnoFlip.h"
#include "../../Juego/Juego.h"

LadoMasUnoFlip::LadoMasUnoFlip(Color color) {
    setColor(color);
}

LadoMasUnoFlip::~LadoMasUnoFlip() = default;

void LadoMasUnoFlip::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un +1 (Flip)." << "\n";
    juego.aplicarMasUnoFlip();
}

bool LadoMasUnoFlip::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoMasUnoFlip*>(&otro) != nullptr;
}

std::string LadoMasUnoFlip::toString() const {
    return "| +1 " + std::string(colorToString(getColor())) + " (Flip) |";
}
