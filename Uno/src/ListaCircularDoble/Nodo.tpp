template <typename T>
Nodo<T>::Nodo(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}

template <typename T>
T Nodo<T>::getDato() const {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() const {
    return siguiente;
}

template <typename T>
Nodo<T>* Nodo<T>::getAnterior() const {
    return anterior;
}

template <typename T>
void Nodo<T>::setDato(T valor) {
    dato = valor;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* nodo) {
    siguiente = nodo;
}

template <typename T>
void Nodo<T>::setAnterior(Nodo<T>* nodo) {
    anterior = nodo;
}
