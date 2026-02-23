#ifndef COLOR_H
#define COLOR_H

enum class Color {
    Rojo,
    Verde,
    Azul,
    Amarillo,
    Rosa,
    Turquesa,
    Naranja,
    Violeta,
    Multicolor
};

inline const char* colorToString(Color color) {
    switch (color) {
        case Color::Rojo: return "Rojo";
        case Color::Verde: return "Verde";
        case Color::Azul: return "Azul";
        case Color::Amarillo: return "Amarillo";
        case Color::Rosa: return "Rosa";
        case Color::Turquesa: return "Turquesa";
        case Color::Naranja: return "Naranja";
        case Color::Violeta: return "Violeta";
        case Color::Multicolor: return "Multicolor";
        default: return "Desconocido";
    }
}

#endif // COLOR_H