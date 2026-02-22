#include "LadoMasCuatro.h"
#include "../Color/Color.h"
#include "../Juego/Juego.h"

LadoMasCuatro::LadoMasCuatro() {
	setColor(Color::Multicolor);
}

LadoMasCuatro::~LadoMasCuatro() = default;

void LadoMasCuatro::aplicarEfecto(Juego& juego) {
	std::cout << "Se ha jugado un +4." << "\n";
	juego.aplicarMasCuatro();
}

bool LadoMasCuatro::esCompatible(const Lado& otro) const {
	if (getColor() == Color::Multicolor) {
		return true;
	}

	return otro.getColor() == getColor() || otro.getColor() == Color::Multicolor;
}

std::string LadoMasCuatro::toString() const {
	return "| +4 " + std::string(colorToString(getColor())) + " |";
}
