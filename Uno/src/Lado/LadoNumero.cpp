#include "LadoNumero.h"

LadoNumero::LadoNumero(int num) : numero(num) {}

LadoNumero::~LadoNumero() {}

void LadoNumero::aplicarEfecto(Juego& juego) {
    std::cout << "Se ha jugado un número: " << numero << "\n";
}

bool LadoNumero::esCompatible(const Lado& otro) const {
    return true;
}

std::string LadoNumero::toString() const {
    return "| Carta Numero: " + std::to_string(numero) + "|";
}