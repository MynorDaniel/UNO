#include "LadoRayosX.h"
#include "../Juego/Juego.h"

LadoRayosX::LadoRayosX(Color color) {
    setColor(color);
}

LadoRayosX::~LadoRayosX() = default;

void LadoRayosX::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un Rayos X." << "\n";
    juego.revelarCartasSiguiente();
}

bool LadoRayosX::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoRayosX*>(&otro) != nullptr;
}

std::string LadoRayosX::toString() const {
    return "| Rayos X " + std::string(colorToString(getColor())) + " |";
}
