#ifndef LADO_MAS_DOS_H
#define LADO_MAS_DOS_H

#include "Lado.h"
#include "../Color/Color.h"
#include <string>

class Juego;

class LadoMasDos : public Lado {
private:
	Color color;

public:
	LadoMasDos(Color color);
	~LadoMasDos() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_MAS_DOS_H
