#ifndef JUEGO_H
#define JUEGO_H

#include "../Carta/Carta.h"
#include "../Jugador/Jugador.h"
#include "../Pila/Pila.h"
#include "../ListaCircularDoble/ListaCircularDoble.h"
#include "../Lado/Lado.h"
#include "../Lado/LadoNumero.h"
#include "../Lado/LadoSalto.h"
#include "../Lado/LadoReversa.h"
#include "../Lado/LadoMasDos.h"
#include "../Lado/LadoComodin.h"
#include "../Lado/LadoMasCuatro.h"
#include "../ListaCircularDoble/Nodo.h"

class Juego
{
private:

    ListaCircularDoble<Jugador*> jugadores;
    Pila<Carta*> mazo;
    Pila<Carta*> descarte;

    int direccionTurno;
    int saltosPendientes;
    int cartasRoboPendientes;
    bool retoMasCuatroPendiente;
    Jugador* jugadorMasCuatro;
    Color colorAnteriorMasCuatro;
    int numeroAnteriorMasCuatro;
    bool numeroAnteriorValido;
    Jugador* jugadorPendienteUno;

    bool modoAcumulacion;
    bool modoRetoMasCuatro;
    bool modoRoboSinLimite;
    bool modoGritoDeUno;
    bool modoGanarConNegra;

public:
    Juego(/* args */);
    ~Juego();

    void iniciarJuego();
    Color pedirColorCarta(const std::string& nombreJugador);
    void aplicarReversa();
    void aplicarSalto();
    void aplicarMasDos();
    void aplicarMasCuatro();
    void registrarMasCuatro(Jugador* jugador, const Lado& topeAntes);
    bool isModoRoboSinLimite() const;

private:
    int calcularCantidadDeMazos(int cantidadJugadores);
    void crearMazoCompleto();
    void crearMazo();
    void pedirConfiguracion();
    void pedirJugadores();
    void repartirCartas();
    void mostrarManos();
    bool iniciarTurnos();
    bool preguntarReinicio();
    void limpiarEstado();
    bool aplicarEfectosInicioTurno(Jugador* jugador);
    int avanzarIndiceJugador(int indiceActual, int pasos) const;
    bool validarJugada(const Jugador* jugador, const Carta* carta, const Lado& tope, bool acumulacionActiva) const;
    bool manejarRetoMasCuatro(Jugador* jugadorActual);
    void manejarGritoUno(Jugador* jugador);
    void manejarReporteUno(Jugador* jugadorReportador);
    bool esCartaNegra(const Carta* carta) const;

    void limpiarPantalla();
    void esperarContinuar();
    int leerOpcionMenu();
    const char* boolTexto(bool valor);
    void mostrarMazo();

    void mostrarTopeDescarte();
    void mostrarCartasJugador(Jugador* jugador);
    int pedirIndiceCarta(Jugador* jugador, const char* mensaje);
    

};

#endif // JUEGO_H