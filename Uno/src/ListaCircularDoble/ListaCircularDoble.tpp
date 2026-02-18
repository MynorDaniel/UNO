template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() : cabeza(nullptr), longitud(0) {}

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    if (cabeza == nullptr) return;

    NodoCircularDoble<T>* actual = cabeza->getSiguiente();

    while (actual != cabeza) {
    NodoCircularDoble<T>* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }

    delete cabeza;
    cabeza = nullptr;
}

template <typename T>
void ListaCircularDoble<T>::insertar(T valor) {
    NodoCircularDoble<T>* nuevoNodo = new NodoCircularDoble<T>(valor);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
    NodoCircularDoble<T>* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(ultimo);
        nuevoNodo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevoNodo);
    }
    longitud++;
}

template <typename T>
void ListaCircularDoble<T>::eliminar(int indice) {
    if (indice < 0 || indice >= longitud) {
        throw std::out_of_range("Indice fuera de rango");
    }

    if (cabeza == nullptr) {
        return;
    }

    NodoCircularDoble<T>* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == actual) {
        delete actual;
        cabeza = nullptr;
    } else {
                NodoCircularDoble<T>* anterior = actual->getAnterior();
                NodoCircularDoble<T>* siguiente = actual->getSiguiente();

        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);

        if (actual == cabeza) {
            cabeza = siguiente;
        }

        delete actual;
    }

    longitud--;
}

template <typename T>
T ListaCircularDoble<T>::get(int indice) const {
    if (indice < 0 || indice >= longitud) {
        throw std::out_of_range("Indice fuera de rango");
    }
    if (cabeza == nullptr) {
        throw std::out_of_range("Lista vacía");
    }

    NodoCircularDoble<T>* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->getSiguiente();
    }
    return actual->getDato();
}

template <typename T>
bool ListaCircularDoble<T>::buscar(T valor) const {
    if (cabeza == nullptr) {
        return false;
    }
    NodoCircularDoble<T>* actual = cabeza;
    do {
        if (actual->getDato() == valor) {
            return true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return false;
}

template <typename T>
int ListaCircularDoble<T>::getLongitud() const {
    return longitud;
}

template <typename T>
bool ListaCircularDoble<T>::isEmpty() const {
    return cabeza == nullptr;
}

template <typename T>
void ListaCircularDoble<T>::imprimir() const {
    if (cabeza == nullptr) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }
    NodoCircularDoble<T>* actual = cabeza;
    do {
        std::cout << actual->getDato() << " ";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    std::cout << std::endl;
}
