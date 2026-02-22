#include "LadoSalto.h"
#include "../Color/Color.h"
#include "../Juego/Juego.h"

LadoSalto::LadoSalto(Color color) : color(color) {
	setColor(color);
}

LadoSalto::~LadoSalto() = default;

void LadoSalto::aplicarEfecto(Juego& juego) {
	std::cout << "Se ha jugado un Salto." << "\n";
	juego.aplicarSalto();
}

bool LadoSalto::esCompatible(const Lado& otro) const {
	if (getColor() == Color::Multicolor || otro.getColor() == Color::Multicolor) {
		return true;
	}

	if (getColor() == otro.getColor()) {
		return true;
	}

	return dynamic_cast<const LadoSalto*>(&otro) != nullptr;
}

std::string LadoSalto::toString() const {
	return "| Salto " + std::string(colorToString(getColor())) + " |";
}
