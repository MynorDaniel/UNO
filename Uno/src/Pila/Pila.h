#ifndef PILA_H
#define PILA_H

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include "../Lista/Nodo.h"

template <typename T>
class Pila {
private:

    Nodo<T>* cima;
    int longitud;

public:

    Pila();
    ~Pila();
    
    void insertar(T valor);
    T sacar();
    T verCima() const;
    bool isEmpty() const;
    int getLongitud() const;
    void barajear();
};

#include "Pila.tpp"

#endif // PILA_H