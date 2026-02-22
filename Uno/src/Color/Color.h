#ifndef COLOR_H
#define COLOR_H

enum class Color {
    Rojo,
    Verde,
    Azul,
    Amarillo,
    Multicolor
};

inline const char* colorToString(Color color) {
    switch (color) {
        case Color::Rojo: return "Rojo";
        case Color::Verde: return "Verde";
        case Color::Azul: return "Azul";
        case Color::Amarillo: return "Amarillo";
        case Color::Multicolor: return "Multicolor";
        default: return "Desconocido";
    }
}

#endif // COLOR_H