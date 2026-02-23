#include "LadoSaltaTodos.h"
#include "../../Juego/Juego.h"

LadoSaltaTodos::LadoSaltaTodos(Color color) {
    setColor(color);
}

LadoSaltaTodos::~LadoSaltaTodos() = default;

void LadoSaltaTodos::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un Salta Todos (Flip)." << "\n";
    juego.aplicarSaltaTodosFlip();
}

bool LadoSaltaTodos::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
        return true;
    }

    if (getColor() == otro.getColor()) {
        return true;
    }

    return dynamic_cast<const LadoSaltaTodos*>(&otro) != nullptr;
}

std::string LadoSaltaTodos::toString() const {
    return "| Salta Todos " + std::string(colorToString(getColor())) + " (Flip) |";
}
