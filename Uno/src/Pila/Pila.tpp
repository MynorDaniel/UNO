template <typename T>
Pila<T>::Pila() : cima(nullptr), longitud(0) {}

template <typename T>
Pila<T>::~Pila() {
    while (cima != nullptr) {
        Nodo<T>* nodoEliminar = cima;
        cima = cima->getSiguiente();
        delete nodoEliminar;
    }
}

template <typename T>
void Pila<T>::insertar(T valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    nuevoNodo->setSiguiente(cima);
    cima = nuevoNodo;
    longitud++;
}

template <typename T>
T Pila<T>::sacar() {
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

template <typename T>
T Pila<T>::verCima() const {
    if (cima == nullptr) {
        throw std::out_of_range("La pila está vacía");
    }
    return cima->getDato();
}

template <typename T>
bool Pila<T>::isEmpty() const {
    return cima == nullptr;
}

template <typename T>
int Pila<T>::getLongitud() const {
    return longitud;
}

template <typename T>
void Pila<T>::barajear() {
    if (longitud <= 1) {
        return;
    }

    T* arreglo = new T[longitud];
    int n = longitud;

    for (int i = 0; i < n; i++) {
        Nodo<T>* nodoEliminar = cima;
        arreglo[i] = nodoEliminar->getDato();
        cima = cima->getSiguiente();
        delete nodoEliminar;
    }

    longitud = 0;

    algoritmoBarajeado(arreglo, n);

    for (int i = n - 1; i >= 0; i--) {
        insertar(arreglo[i]);
    }

    delete[] arreglo;
}

template <typename T>
void Pila<T>::algoritmoBarajeado(T* arreglo, int n) {
    if (n <= 1) {
        return;
    }

    for (int i = 0; i < n; i++) {
    int j = std::rand() % n;
        T temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}