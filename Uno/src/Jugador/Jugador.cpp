#include "Jugador.h"
#include "../Juego/Juego.h"
#include "../Lado/LadoComodin.h"
#include "../Lado/LadoMasCuatro.h"
#include "../Lado/LadoMasDos.h"
#include "../Lado/LadoNumero.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre, Juego* juego, Pila<Carta*>* mazo, Pila<Carta*>* descarte)
    : nombre(nombre), juego(juego), mazo(mazo), descarte(descarte)
{
}

Jugador::~Jugador()
{
    int total = cartas.getLongitud();
    for (int i = 0; i < total; i++) {
        Carta* carta = cartas.get(i);
        delete carta;
    }
}

void Jugador::tomarCarta(Carta* carta)
{
    cartas.agregar(carta);
    ordenarCartas();
}

void Jugador::mostrarCartas()
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        if (carta != nullptr && carta->getLadoActual() != nullptr) {
            std::cout << carta->getLadoActual()->toString() << "\n";
        }
    }
}

bool Jugador::tieneCartaCompatible(const Lado& tope)
{
    Nodo<Carta*>* actual = cartas.getCabeza();
    while (actual != nullptr) {
        Carta* carta = actual->getDato();
        Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
        if (ladoActual != nullptr && ladoActual->esCompatible(tope)) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Jugador::jugarCarta(int indice, const Lado& tope)
{
    if (indice < 0 || indice >= cartas.getLongitud()) {
        return false;
    }

    Carta* carta = cartas.get(indice);
    Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
    if (ladoActual == nullptr || !ladoActual->esCompatible(tope)) {
        return false;
    }

    cartas.eliminar(indice);
    ordenarCartas();
    if (descarte != nullptr) {
        descarte->insertar(carta);
    }
    std::cout << nombre << " descarta: "
              << carta->getLadoActual()->toString() << "\n";
    if (juego != nullptr) {
        Lado* ladoActual = carta->getLadoActual();
        if (ladoActual != nullptr &&
            (dynamic_cast<LadoComodin*>(ladoActual) != nullptr ||
             dynamic_cast<LadoMasCuatro*>(ladoActual) != nullptr)) {
            Color colorElegido = juego->pedirColorCarta(nombre);
            ladoActual->setColor(colorElegido);
        }

        if (ladoActual != nullptr && dynamic_cast<LadoMasCuatro*>(ladoActual) != nullptr) {
            juego->registrarMasCuatro(this, tope);
        }

        carta->aplicarEfecto(*juego);
    }
    return true;
}

void Jugador::manejarSinCompatibles(const Lado& tope)
{
    std::cout << nombre << " no tiene cartas compatibles.\n";

    if (juego != nullptr && mazo != nullptr && mazo->isEmpty()) {
        juego->recargarMazoDesdeDescarte();
    }

    if (mazo == nullptr || mazo->isEmpty()) {
        std::cout << "El mazo está vacío. Se pasa el turno.\n";
        return;
    }

    bool roboSinLimite = juego != nullptr && juego->isModoRoboSinLimite();

    do {
        if (juego != nullptr && mazo != nullptr && mazo->isEmpty()) {
            juego->recargarMazoDesdeDescarte();
        }
        if (mazo == nullptr || mazo->isEmpty()) {
            std::cout << "El mazo está vacío. Se pasa el turno.\n";
            return;
        }
        Carta* cartaRobada = mazo->sacar();
        tomarCarta(cartaRobada);
        std::cout << nombre << " roba: "
                  << cartaRobada->getLadoActual()->toString() << "\n";

        if (cartaRobada->getLadoActual()->esCompatible(tope)) {
            std::cout << "La carta robada es compatible y se juega automáticamente.\n";
            int indiceRobada = getCantidadCartas() - 1;
            jugarCarta(indiceRobada, tope);
            return;
        }
    } while (roboSinLimite && mazo != nullptr && !mazo->isEmpty());
}

void Jugador::robarCartas(int cantidad)
{
    if (mazo == nullptr) {
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (juego != nullptr && mazo != nullptr && mazo->isEmpty()) {
            juego->recargarMazoDesdeDescarte();
        }
        if (mazo->isEmpty()) {
            std::cout << "El mazo se quedó sin cartas.\n";
            break;
        }
        Carta* carta = mazo->sacar();
        tomarCarta(carta);
    }
}

bool Jugador::tieneCartaDeColor(Color color) const
{
    Nodo<Carta*>* actual = cartas.getCabeza();
    while (actual != nullptr) {
        Carta* carta = actual->getDato();
        Lado* lado = carta ? carta->getLadoActual() : nullptr;
        if (lado != nullptr && lado->getColor() == color) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Jugador::tieneCartaNumero(int numero) const
{
    Nodo<Carta*>* actual = cartas.getCabeza();
    while (actual != nullptr) {
        Carta* carta = actual->getDato();
        LadoNumero* ladoNumero = carta ? dynamic_cast<LadoNumero*>(carta->getLadoActual()) : nullptr;
        if (ladoNumero != nullptr && ladoNumero->getNumero() == numero) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Jugador::tieneCartaAcumulable(const Lado& tope) const
{
    const bool topeMasDos = dynamic_cast<const LadoMasDos*>(&tope) != nullptr;
    const bool topeMasCuatro = dynamic_cast<const LadoMasCuatro*>(&tope) != nullptr;

    Nodo<Carta*>* actual = cartas.getCabeza();
    while (actual != nullptr) {
        Carta* carta = actual->getDato();
        Lado* lado = carta ? carta->getLadoActual() : nullptr;
        if (lado != nullptr) {
            if (topeMasDos && dynamic_cast<LadoMasDos*>(lado) != nullptr) {
                return true;
            }

            if (topeMasCuatro && dynamic_cast<LadoMasCuatro*>(lado) != nullptr) {
                return true;
            }
        }
        actual = actual->getSiguiente();
    }

    return false;
}

void Jugador::intercambiarCartasCon(Jugador& otro)
{
    cartas.intercambiar(otro.cartas);
    ordenarCartas();
    otro.ordenarCartas();
}

void Jugador::voltearCartas()
{
    for (int i = 0; i < cartas.getLongitud(); i++) {
        Carta* carta = cartas.get(i);
        if (carta != nullptr) {
            carta->voltear();
        }
    }
    ordenarCartas();
}

Carta* Jugador::extraerCarta(int indice)
{
    if (indice < 0 || indice >= cartas.getLongitud()) {
        return nullptr;
    }

    Carta* carta = cartas.get(indice);
    cartas.eliminar(indice);
    ordenarCartas();
    return carta;
}

int Jugador::obtenerNumeroOrden(const Carta* carta) {
    if (carta == nullptr) {
        return 100;
    }

    Lado* lado = carta->getLadoActual();
    if (lado == nullptr) {
        return 100;
    }

    LadoNumero* ladoNumero = dynamic_cast<LadoNumero*>(lado);
    if (ladoNumero != nullptr) {
        return ladoNumero->getNumero();
    }

    return 100;
}

int Jugador::obtenerColorOrden(const Carta* carta) {
    if (carta == nullptr) {
        return 100;
    }

    Lado* lado = carta->getLadoActual();
    if (lado == nullptr) {
        return 100;
    }

    switch (lado->getColor()) {
        case Color::Rojo: return 0;
        case Color::Amarillo: return 1;
        case Color::Verde: return 2;
        case Color::Azul: return 3;
        case Color::Rosa: return 4;
        case Color::Turquesa: return 5;
        case Color::Naranja: return 6;
        case Color::Violeta: return 7;
        case Color::Multicolor: return 8;
        default: return 100;
    }
}

bool Jugador::compararCartas(const Carta* izquierda, const Carta* derecha) {
    int numeroIzquierda = obtenerNumeroOrden(izquierda);
    int numeroDerecha = obtenerNumeroOrden(derecha);
    if (numeroIzquierda != numeroDerecha) {
        return numeroIzquierda < numeroDerecha;
    }

    int colorIzquierda = obtenerColorOrden(izquierda);
    int colorDerecha = obtenerColorOrden(derecha);
    return colorIzquierda < colorDerecha;
}

void Jugador::mezclar(Carta** cartasArray, int inicio, int medio, int fin) {
    int izquierda = inicio;
    int derecha = medio + 1;
    int total = fin - inicio + 1;
    Carta** resultado = new Carta*[total];
    int indiceResultado = 0;

    while (izquierda <= medio && derecha <= fin) {
        if (compararCartas(cartasArray[izquierda], cartasArray[derecha])) {
            resultado[indiceResultado++] = cartasArray[izquierda++];
        } else {
            resultado[indiceResultado++] = cartasArray[derecha++];
        }
    }

    while (izquierda <= medio) {
        resultado[indiceResultado++] = cartasArray[izquierda++];
    }

    while (derecha <= fin) {
        resultado[indiceResultado++] = cartasArray[derecha++];
    }

    for (int i = 0; i < total; i++) {
        cartasArray[inicio + i] = resultado[i];
    }

    delete[] resultado;
}

void Jugador::mergeSort(Carta** cartasArray, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;
    mergeSort(cartasArray, inicio, medio);
    mergeSort(cartasArray, medio + 1, fin);
    mezclar(cartasArray, inicio, medio, fin);
}

void Jugador::ordenarCartas() {
    int total = cartas.getLongitud();
    if (total <= 1) {
        return;
    }

    Carta** cartasArray = new Carta*[total];
    for (int i = 0; i < total; i++) {
        cartasArray[i] = cartas.get(i);
    }

    mergeSort(cartasArray, 0, total - 1);

    while (cartas.getLongitud() > 0) {
        cartas.eliminar(0);
    }

    for (int i = 0; i < total; i++) {
        cartas.agregar(cartasArray[i]);
    }

    delete[] cartasArray;
}

int Jugador::getCantidadCartas() const
{
    return cartas.getLongitud();
}

std::string Jugador::getNombre() const
{
    return nombre;
}

void Jugador::setNombre(const std::string& nuevoNombre)
{
    nombre = nuevoNombre;
}

Lista<Carta*>& Jugador::getCartas()
{
    return cartas;
}
