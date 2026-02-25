#ifndef LISTA_H
#define LISTA_H

#include <stdexcept>
#include "Nodo.h"

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int longitud;

public:
    Lista();

    ~Lista();

    bool estaVacia() const;

    int getLongitud() const;

    void agregar(const T& dato);

    T get(int indice) const;

    void eliminar(int indice);

    void intercambiar(Lista<T>& otra);

    Nodo<T>* getCabeza() const;
};

#include "Lista.tpp"

#endif // LISTA_H