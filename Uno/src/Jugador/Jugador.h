#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "../Lista/Lista.h"
#include "../Carta/Carta.h"
#include "../Pila/Pila.h"

class Juego;

class Jugador
{
private:
    std::string nombre;
    Lista<Carta*> cartas;
    Juego* juego;
    Pila<Carta*>* mazo;
    Pila<Carta*>* descarte;

    void ordenarCartas();
    void mergeSort(Carta** cartas, int inicio, int fin);
    void mezclar(Carta** cartas, int inicio, int medio, int fin);
    bool compararCartas(const Carta* izquierda, const Carta* derecha);
    int obtenerNumeroOrden(const Carta* carta);
    int obtenerColorOrden(const Carta* carta);

public:
    Jugador(const std::string& nombre, Juego* juego, Pila<Carta*>* mazo, Pila<Carta*>* descarte);
    ~Jugador();

    void tomarCarta(Carta* carta);
    void mostrarCartas();
    int getCantidadCartas() const;
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);
    Lista<Carta*>& getCartas();

    bool tieneCartaCompatible(const Lado& tope);
    bool jugarCarta(int indice, const Lado& tope);
    void manejarSinCompatibles(const Lado& tope);
    void robarCartas(int cantidad);
    bool tieneCartaDeColor(Color color) const;
    bool tieneCartaNumero(int numero) const;
    bool tieneCartaAcumulable(const Lado& tope) const;
    void intercambiarCartasCon(Jugador& otro);
    void voltearCartas();
    Carta* extraerCarta(int indice);

};


#endif // JUGADOR_H