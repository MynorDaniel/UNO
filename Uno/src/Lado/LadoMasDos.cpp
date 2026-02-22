#include "LadoMasDos.h"
#include "../Color/Color.h"
#include "../Juego/Juego.h"

LadoMasDos::LadoMasDos(Color color) : color(color) {
	setColor(color);
}

LadoMasDos::~LadoMasDos() = default;

void LadoMasDos::aplicarEfecto(Juego& juego) {
	std::cout << "Se ha jugado un +2." << "\n";
	juego.aplicarMasDos();
}

bool LadoMasDos::esCompatible(const Lado& otro) const {
	if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
		return true;
	}

	if (getColor() == otro.getColor()) {
		return true;
	}

	return dynamic_cast<const LadoMasDos*>(&otro) != nullptr;
}

std::string LadoMasDos::toString() const {
	return "| +2 " + std::string(colorToString(getColor())) + " |";
}
