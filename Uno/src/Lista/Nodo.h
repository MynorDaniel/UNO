#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {

private:
    T dato;
    Nodo<T>* siguiente;

public:
    Nodo(T dato) : dato(dato), siguiente(nullptr) {}

    T getDato() const {
        return dato;
    }

    Nodo<T>* getSiguiente() const {
        return siguiente;
    }

    void setSiguiente(Nodo<T>* siguiente) {
        this->siguiente = siguiente;
    }
};

#endif
