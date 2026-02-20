#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "../Lista/Lista.h"
#include "../Carta/Carta.h"

class Jugador
{
private:
    std::string nombre;
    Lista<Carta*> cartas;

public:
    Jugador(const std::string& nombre);
    ~Jugador();

    void tomarCarta(Carta* carta);
    void mostrarCartas();
    int getCantidadCartas();
    std::string getNombre();
    void setNombre(const std::string& nuevoNombre);
    Lista<Carta*>& getCartas();

};


#endif // JUGADOR_H