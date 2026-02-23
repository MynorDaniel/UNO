#include "LadoMasSeisFlip.h"
#include "../../Juego/Juego.h"

LadoMasSeisFlip::LadoMasSeisFlip(Color color) {
    setColor(color);
}

LadoMasSeisFlip::~LadoMasSeisFlip() = default;

void LadoMasSeisFlip::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un +6 (Flip)." << "\n";
    juego.aplicarMasSeisFlip();
}

bool LadoMasSeisFlip::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoMasSeisFlip*>(&otro) != nullptr;
}

std::string LadoMasSeisFlip::toString() const {
    return "| +6 " + std::string(colorToString(getColor())) + " (Flip) |";
}
