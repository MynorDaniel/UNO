#ifndef LISTA_NODO_H
#define LISTA_NODO_H

template <typename T>
class Nodo {

private:
    T dato;
    Nodo<T>* siguiente;

public:
    Nodo(T dato);

    T getDato();

    Nodo<T>* getSiguiente();

    void setSiguiente(Nodo<T>* siguiente);
};

#include "Nodo.tpp"

#endif // LISTA_NODO_H
