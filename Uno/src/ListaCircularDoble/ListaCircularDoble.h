#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include "Nodo.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;
    int longitud;

public:
    ListaCircularDoble();
    
    ~ListaCircularDoble();

    void insertar(T valor);

    void eliminar(int indice);

    bool buscar(T valor) const;

    int getLongitud() const;

    bool isEmpty() const;

    void imprimir() const;
};

#include "ListaCircularDoble.tpp"

#endif // LISTA_CIRCULAR_DOBLE_H