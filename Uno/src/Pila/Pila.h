#ifndef PILA_H
#define PILA_H

#include "Nodo.h"

template <typename T>
class Pila {
private:

    Nodo<T>* cima;
    int longitud;

public:

    Pila() : cima(nullptr), longitud(0) {}
    ~Pila() {
        while (cima != nullptr) {
            Nodo<T>* nodoEliminar = cima;
            cima = cima->getSiguiente();
            delete nodoEliminar;
        }
    }
    
    void insertar(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        nuevoNodo->setSiguiente(cima);
        cima = nuevoNodo;
        longitud++;
    }

    T sacar() {
        if (cima == nullptr) {
            throw std::out_of_range("La pila está vacía");
        }
        Nodo<T>* nodoEliminar = cima;
        T valor = nodoEliminar->getDato();
        cima = cima->getSiguiente();
        delete nodoEliminar;
        longitud--;
        return valor;
    }

    T verCima() const {
        if (cima == nullptr) {
            throw std::out_of_range("La pila está vacía");
        }
        return cima->getDato();
    }

    bool isEmpty() const {
        return cima == nullptr;
    }

    int getLongitud() const {
        return longitud;
    }
};

#endif // PILA_H