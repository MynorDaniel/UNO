#include "Lado.h"

Lado::Lado(/* args */)
{
}

Lado::~Lado() = default;

Color Lado::getColor() const {
    return color;
}

void Lado::setColor(Color nuevoColor) {
    color = nuevoColor;
}