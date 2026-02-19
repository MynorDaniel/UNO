#include "LadoNumero.h"

LadoNumero::LadoNumero(int num) : numero(num) {}

LadoNumero::~LadoNumero() {}

void LadoNumero::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un número: " << numero << "\n";
}