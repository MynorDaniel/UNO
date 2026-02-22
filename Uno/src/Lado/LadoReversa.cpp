#include "LadoReversa.h"
#include "../Color/Color.h"
#include "../Juego/Juego.h"

LadoReversa::LadoReversa(Color color) : color(color) {
	setColor(color);
}

LadoReversa::~LadoReversa() = default;

void LadoReversa::aplicarEfecto(Juego& juego) {
	std::cout << "Se ha jugado una Reversa." << "\n";
	juego.aplicarReversa();
}

bool LadoReversa::esCompatible(const Lado& otro) const {
	if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
		return true;
	}

	if (getColor() == otro.getColor()) {
		return true;
	}

	return dynamic_cast<const LadoReversa*>(&otro) != nullptr;
}

std::string LadoReversa::toString() const {
	return "| Reversa " + std::string(colorToString(getColor())) + " |";
}
