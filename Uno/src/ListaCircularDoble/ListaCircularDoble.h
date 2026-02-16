#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include "Nodo.h"

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;
    int longitud;

public:
    ListaCircularDoble() : cabeza(nullptr), longitud(0) {}
    ~ListaCircularDoble() {
        if (cabeza == nullptr) return;

        Nodo<T>* actual = cabeza->getSiguiente();

        while (actual != cabeza) {
            Nodo<T>* temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        }

        delete cabeza;
        cabeza = nullptr;
    }


    void insertar(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            cabeza->setSiguiente(cabeza);
            cabeza->setAnterior(cabeza);
        } else {
            Nodo<T>* ultimo = cabeza->getAnterior();
            ultimo->setSiguiente(nuevoNodo);
            nuevoNodo->setAnterior(ultimo);
            nuevoNodo->setSiguiente(cabeza);
            cabeza->setAnterior(nuevoNodo);
        }
        longitud++;
    }

    void eliminar(T valor) {
        if (cabeza == nullptr) return;

        Nodo<T>* actual = cabeza;

        do {
            if (actual->getDato() == valor) {

                if (actual->getSiguiente() == actual) {
                    delete actual;
                    cabeza = nullptr;
                } 
                else {
                    Nodo<T>* anterior = actual->getAnterior();
                    Nodo<T>* siguiente = actual->getSiguiente();

                    anterior->setSiguiente(siguiente);
                    siguiente->setAnterior(anterior);

                    if (actual == cabeza) {
                        cabeza = siguiente;
                    }

                    delete actual;
                }

                longitud--;
                return;
            }

            actual = actual->getSiguiente();

        } while (actual != cabeza);
    }


    bool buscar(T valor) const {
        if (cabeza == nullptr) {
            return false;
        }
        Nodo<T>* actual = cabeza;
        do {
            if (actual->getDato() == valor) {
                return true;
            }
            actual = actual->getSiguiente();
        } while (actual != cabeza);
        return false;
    }

    int getLongitud() const {
        return longitud;
    }

    bool isEmpty() const {
        return cabeza == nullptr;
    }

    void imprimir() const {
        if (cabeza == nullptr) {
            std::cout << "La lista está vacía." << std::endl;
            return;
        }
        Nodo<T>* actual = cabeza;
        do {
            std::cout << actual->getDato() << " ";
            actual = actual->getSiguiente();
        } while (actual != cabeza);
        std::cout << std::endl;
    }

};

#endif // LISTA_CIRCULAR_DOBLE_H