template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() : cabeza(nullptr), longitud(0) {}

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
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

template <typename T>
void ListaCircularDoble<T>::insertar(T valor) {
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

template <typename T>
void ListaCircularDoble<T>::eliminar(int indice) {
    if (indice < 0 || indice >= longitud) {
        throw std::out_of_range("Indice fuera de rango");
    }

    if (cabeza == nullptr) {
        return;
    }

    Nodo<T>* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->getSiguiente();
    }

    if (actual->getSiguiente() == actual) {
        delete actual;
        cabeza = nullptr;
    } else {
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
}

template <typename T>
bool ListaCircularDoble<T>::buscar(T valor) const {
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
    Nodo<T>* actual = cabeza;
    do {
        std::cout << actual->getDato() << " ";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    std::cout << std::endl;
}
