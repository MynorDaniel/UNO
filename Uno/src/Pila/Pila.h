#ifndef PILA_H
#define PILA_H

#include <stdexcept>
#include <cstdlib>
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
    void algoritmoBarajeado(T* arreglo, int n);
};

#include "Pila.tpp"

#endif // PILA_H