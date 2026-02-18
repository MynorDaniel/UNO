template <typename T>
NodoCircularDoble<T>::NodoCircularDoble(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}

template <typename T>
T NodoCircularDoble<T>::getDato() const {
    return dato;
}

template <typename T>
NodoCircularDoble<T>* NodoCircularDoble<T>::getSiguiente() const {
    return siguiente;
}

template <typename T>
NodoCircularDoble<T>* NodoCircularDoble<T>::getAnterior() const {
    return anterior;
}

template <typename T>
void NodoCircularDoble<T>::setDato(T valor) {
    dato = valor;
}

template <typename T>
void NodoCircularDoble<T>::setSiguiente(NodoCircularDoble<T>* nodo) {
    siguiente = nodo;
}

template <typename T>
void NodoCircularDoble<T>::setAnterior(NodoCircularDoble<T>* nodo) {
    anterior = nodo;
}
