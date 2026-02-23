#include "LadoColorEterno.h"
#include "../../Juego/Juego.h"

LadoColorEterno::LadoColorEterno() {
    setColor(Color::Multicolor);
}

LadoColorEterno::~LadoColorEterno() = default;

void LadoColorEterno::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un Color Eterno (Flip)." << "\n";
    Color colorElegido = juego.pedirColorOscuro(juego.getNombreJugadorActual());
    setColor(colorElegido);
    juego.aplicarColorEterno(colorElegido);
}

bool LadoColorEterno::esCompatible(const Lado& otro) const {
    if (getColor() == Color::Multicolor) {
        return true;
    }

    return otro.getColor() == getColor() || otro.getColor() == Color::Multicolor;
}

std::string LadoColorEterno::toString() const {
    return "| Color Eterno " + std::string(colorToString(getColor())) + " (Flip) |";
}
