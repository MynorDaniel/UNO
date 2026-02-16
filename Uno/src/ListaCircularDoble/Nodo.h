#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T valor);

    T getDato() const;

    Nodo<T>* getSiguiente() const;

    Nodo<T>* getAnterior() const;

    void setDato(T valor);

    void setSiguiente(Nodo<T>* nodo);

    void setAnterior(Nodo<T>* nodo);
};

#include "Nodo.tpp"

#endif // NODO_H