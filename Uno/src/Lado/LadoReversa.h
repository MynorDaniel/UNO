#ifndef LADO_REVERSA_H
#define LADO_REVERSA_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoReversa : public Lado {
private:
	Color color;

public:
	LadoReversa(Color color);
	~LadoReversa() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_REVERSA_H
