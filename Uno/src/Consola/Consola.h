#ifndef CONSOLA_H
#define CONSOLA_H

#include <string>
#include "../Color/Color.h"

class Consola {
public:
    void limpiarPantalla();
    void esperarContinuar();
    int leerOpcionMenu(const std::string& mensaje = "Seleccione una opción: ");
    std::string pedirTextoNoVacio(const std::string& mensaje);
    int pedirEnteroMinimo(const std::string& mensaje, int minimo);
    int pedirIndiceCarta(int totalCartas, const std::string& mensaje);
    const char* boolTexto(bool valor);
    Color pedirColorClaro(const std::string& nombreJugador);
    Color pedirColorOscuro(const std::string& nombreJugador);
};

#endif // CONSOLA_H
