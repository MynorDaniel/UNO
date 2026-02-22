#ifndef LADO_COMODIN_H
#define LADO_COMODIN_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoComodin : public Lado {
public:
	LadoComodin();
	~LadoComodin() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_COMODIN_H
