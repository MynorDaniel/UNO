#ifndef LADO_MAS_UNO_FLIP_H
#define LADO_MAS_UNO_FLIP_H

#include "../Lado.h"
#include "../../Color/Color.h"
#include <string>

class Juego;

class LadoMasUnoFlip : public Lado {
public:
	LadoMasUnoFlip(Color color);
	~LadoMasUnoFlip() override;

	void aplicarEfecto(Juego& juego) override;
	bool esCompatible(const Lado& otro) const override;
	std::string toString() const override;
};

#endif // LADO_MAS_UNO_FLIP_H
