#ifndef JUEGO_H
#define JUEGO_H

#include "../Carta/Carta.h"
#include "../Jugador/Jugador.h"
#include "../Pila/Pila.h"
#include "../ListaCircularDoble/ListaCircularDoble.h"

class Juego
{
private:

    ListaCircularDoble<Jugador*> jugadores;

    bool modoAcumulacion;
    bool modoRetoMasCuatro;
    bool modoRoboSinLimite;
    bool modoGritoDeUno;
    bool modoGanarConNegra;

public:
    Juego(/* args */);
    ~Juego();

    void iniciarJuego();

private:
    void pedirConfiguracion();
    void pedirJugadores();
    void repartirCartas();
    void mostrarManos();

    void limpiarPantalla();
    int leerOpcionMenu();
    const char* boolTexto(bool valor);

};

#endif // JUEGO_H