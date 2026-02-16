#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}

    T getDato() const {
        return dato;
    }

    Nodo<T>* getSiguiente() const {
        return siguiente;
    }

    Nodo<T>* getAnterior() const {
        return anterior;
    }

    void setDato(T valor) {
        dato = valor;
    }

    void setSiguiente(Nodo<T>* nodo) {
        siguiente = nodo;
    }

    void setAnterior(Nodo<T>* nodo) {
        anterior = nodo;
    }
};

#endif // NODO_H