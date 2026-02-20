#ifndef JUEGO_H
#define JUEGO_H

#include "../Carta/Carta.h"
#include "../Jugador/Jugador.h"
#include "../Pila/Pila.h"
#include "../ListaCircularDoble/ListaCircularDoble.h"
#include "../Lado/Lado.h"
#include "../Lado/LadoNumero.h"

class Juego
{
private:

    ListaCircularDoble<Jugador*> jugadores;
    Pila<Carta*> mazo;
    Pila<Carta*> descarte;

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
    void crearMazo();
    void pedirConfiguracion();
    void pedirJugadores();
    void repartirCartas();
    void mostrarManos();
    void iniciarTurnos();

    void limpiarPantalla();
    int leerOpcionMenu();
    const char* boolTexto(bool valor);
    void mostrarMazo();

    void mostrarTopeDescarte();
    void mostrarCartasJugador(Jugador* jugador);
    bool jugadorTieneCartaCompatible(Jugador* jugador, Lado* tope);
    int pedirIndiceCarta(Jugador* jugador, const char* mensaje);
    void jugarCarta(Jugador* jugador, int indice);

};

#endif // JUEGO_H