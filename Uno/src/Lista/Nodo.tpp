#include "Nodo.h"

template <typename T>
Nodo<T>::Nodo(T dato) : dato(dato), siguiente(nullptr) {}

template <typename T>
T Nodo<T>::getDato() {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* siguiente) {
    this->siguiente = siguiente;
}