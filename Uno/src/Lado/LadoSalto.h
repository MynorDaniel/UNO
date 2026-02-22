#ifndef LADO_SALTO_H
#define LADO_SALTO_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoSalto : public Lado {
private:
	Color color;

public:
	LadoSalto(Color color);
	~LadoSalto() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_SALTO_H
