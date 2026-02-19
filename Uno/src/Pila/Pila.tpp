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

    std::vector<T> arreglo;
    arreglo.reserve(longitud);

    while (cima != nullptr) {
        Nodo<T>* nodoEliminar = cima;
        arreglo.push_back(nodoEliminar->getDato());
        cima = cima->getSiguiente();
        delete nodoEliminar;
    }

    longitud = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arreglo.begin(), arreglo.end(), gen);

    for (const T& valor : arreglo) {
        insertar(valor);
    }
}