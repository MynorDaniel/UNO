#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int longitud;

public:
    Lista(): cabeza(nullptr), longitud(0) {}

    ~Lista() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    int getLongitud() const {
        return longitud;
    }

    void agregar(const T& dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if (estaVacia()) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente() != nullptr) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        longitud++;
    }

    T get(int indice) const {
        if (indice < 0 || indice >= longitud) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->getSiguiente();
        }
        return actual->getDato();
    }

    void eliminar(int indice) {
        if (indice < 0 || indice >= longitud) {
            throw std::out_of_range("Indice fuera de rango");
        }

        if (indice == 0) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->getSiguiente();
            delete temp;
        } 
        else {
            Nodo<T>* anterior = cabeza;

            for (int i = 0; i < indice - 1; i++) {
                anterior = anterior->getSiguiente();
            }

            Nodo<T>* actual = anterior->getSiguiente();
            anterior->setSiguiente(actual->getSiguiente());
            delete actual;
        }

        longitud--;
    }


};

#endif // LISTA_H