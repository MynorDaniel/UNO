#ifndef NODO_CIRCULAR_DOBLE_H
#define NODO_CIRCULAR_DOBLE_H

template <typename T>
class NodoCircularDoble {
public:
    T dato;
    NodoCircularDoble<T>* siguiente;
    NodoCircularDoble<T>* anterior;

    NodoCircularDoble(T valor);

    T getDato() const;

    NodoCircularDoble<T>* getSiguiente() const;

    NodoCircularDoble<T>* getAnterior() const;

    void setDato(T valor);

    void setSiguiente(NodoCircularDoble<T>* nodo);

    void setAnterior(NodoCircularDoble<T>* nodo);
};

#include "Nodo.tpp"

#endif // NODO_CIRCULAR_DOBLE_H