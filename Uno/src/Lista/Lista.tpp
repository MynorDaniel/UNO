template <typename T>
Lista<T>::Lista () : cabeza(nullptr), longitud(0) {}

template <typename T>
Lista<T>::~Lista() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

template <typename T>
bool Lista<T>::estaVacia() const {
    return cabeza == nullptr;
}

template <typename T>
int Lista<T>::getLongitud() const {
    return longitud;
}   

template <typename T>
void Lista<T>::agregar(const T& dato) {
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

template <typename T>
T Lista<T>::get(int indice) const {
    if (indice < 0 || indice >= longitud) {
        throw std::out_of_range("Índice fuera de rango");
    }
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->getSiguiente();
    }
    return actual->getDato();
}

template <typename T>
void Lista<T>::eliminar(int indice) {
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

