#include "LadoComodin.h"
#include "../Color/Color.h"
#include "../Juego/Juego.h"

LadoComodin::LadoComodin() {
	setColor(Color::Multicolor);
}

LadoComodin::~LadoComodin() = default;

void LadoComodin::aplicarEfecto(Juego& juego) {
	std::cout << "Se ha jugado un Comodín." << "\n";
}

bool LadoComodin::esCompatible(const Lado& otro) const {
	if (getColor() == Color::Multicolor) {
		return true;
	}

	return otro.getColor() == getColor() || otro.getColor() == Color::Multicolor;
}

std::string LadoComodin::toString() const {
	return "| Comodín " + std::string(colorToString(getColor())) + " |";
}
