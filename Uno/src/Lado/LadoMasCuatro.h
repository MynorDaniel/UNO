#ifndef LADO_MAS_CUATRO_H
#define LADO_MAS_CUATRO_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoMasCuatro : public Lado {
public:
	LadoMasCuatro();
	~LadoMasCuatro() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_MAS_CUATRO_H
