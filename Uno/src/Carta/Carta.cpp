#include "Carta.h"

Carta::Carta(Lado* claro, Lado* oscuro) : ladoClaro(claro), ladoOscuro(oscuro), ladoActual(claro)
{
}

Carta::~Carta()
{
	delete ladoClaro;
	delete ladoOscuro;
}

void Carta::voltear() {
	if (ladoActual == ladoClaro) {
		ladoActual = ladoOscuro;
	} else {
		ladoActual = ladoClaro;
	}
}

void Carta::aplicarEfecto(Juego& juego) {
	if (ladoActual != nullptr) {
		ladoActual->aplicarEfecto(juego);
	}
}