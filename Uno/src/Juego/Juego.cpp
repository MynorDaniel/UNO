#include "Juego.h"
#include <iostream>
#include <string>

Juego::Juego()
        : modoAcumulacion(false),
            modoRetoMasCuatro(false),
            modoRoboSinLimite(false),
            modoGritoDeUno(false),
            modoGanarConNegra(false)
{
}

Juego::~Juego()
{

}

void Juego::iniciarJuego()
{
    std::cout << "\n¡Bienvenido a UNO!\n";
    pedirConfiguracion();
    pedirJugadores();
    crearMazo();
    repartirCartas();
    mostrarManos();
    iniciarTurnos();
}

void Juego::crearMazo() {
    std::cout << "\nCreando el mazo de cartas...\n";
     
    Carta* carta1 = new Carta(new LadoNumero(1), new LadoNumero(2));
    mazo.insertar(carta1);

    Carta* carta2 = new Carta(new LadoNumero(3), new LadoNumero(4));
    mazo.insertar(carta2);

    Carta* carta3 = new Carta(new LadoNumero(5), new LadoNumero(6));
    mazo.insertar(carta3);

    Carta* carta4 = new Carta(new LadoNumero(7), new LadoNumero(8));
    mazo.insertar(carta4);

    mazo.barajear();

    mostrarMazo();
}

void Juego::pedirConfiguracion()
{
    bool configurando = true;
    while (configurando) {
        std::cout << "\nConfiguración actual:\n";
        std::cout << "1. Modo Acumulación: " << boolTexto(modoAcumulacion) << "\n";
        std::cout << "2. Modo Reto +4: " << boolTexto(modoRetoMasCuatro) << "\n";
        std::cout << "3. Modo Robo sin límite: " << boolTexto(modoRoboSinLimite) << "\n";
        std::cout << "4. Modo Grito de Uno: " << boolTexto(modoGritoDeUno) << "\n";
        std::cout << "5. Modo Ganar con Negra: " << boolTexto(modoGanarConNegra) << "\n";
        std::cout << "0. Terminar configuración\n";

    int opcion = leerOpcionMenu();
    limpiarPantalla();
        switch (opcion) {
            case 1:
                modoAcumulacion = !modoAcumulacion;
                break;
            case 2:
                modoRetoMasCuatro = !modoRetoMasCuatro;
                break;
            case 3:
                modoRoboSinLimite = !modoRoboSinLimite;
                break;
            case 4:
                modoGritoDeUno = !modoGritoDeUno;
                break;
            case 5:
                modoGanarConNegra = !modoGanarConNegra;
                break;
            case 0:
                configurando = false;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    }
}

void Juego::pedirJugadores()
{
    int cantidad = 0;
    while (cantidad < 2) {
        std::cout << "\nIngrese la cantidad de jugadores (mínimo 2): ";
        cantidad = leerOpcionMenu();
        if (cantidad < 2) {
            std::cout << "Debe ingresar al menos 2 jugadores.\n";
        }
    }

    for (int i = 1; i <= cantidad; i++) {
        std::string nombre;
        while (nombre.empty()) {
            std::cout << "Nombre del jugador " << i << ": ";
            std::getline(std::cin >> std::ws, nombre);
            if (nombre.empty()) {
                std::cout << "El nombre no puede estar vacío.\n";
            }
        }

        Jugador* jugador = new Jugador(nombre);
        jugadores.insertar(jugador);
    }

    std::cout << "\nJugadores registrados:\n";
    for (int i = 0; i < jugadores.getLongitud(); i++) {
        Jugador* jugador = jugadores.get(i);
        if (jugador != nullptr) {
            std::cout << i + 1 << ". " << jugador->getNombre() << "\n";
        }
    }
}   

void Juego::repartirCartas()
{
    int totalJugadores = jugadores.getLongitud();
    if (totalJugadores <= 0) {
        std::cout << "\nNo hay jugadores para repartir cartas.\n";
        return;
    }

    std::cout << "\nRepartiendo cartas...\n";

    int indiceJugador = 0;
    while (!mazo.isEmpty()) {
        Jugador* jugador = jugadores.get(indiceJugador);
        if (jugador != nullptr) {
            Carta* carta = mazo.sacar();
            jugador->tomarCarta(carta);
        }

        indiceJugador++;
        if (indiceJugador >= totalJugadores) {
            indiceJugador = 0;
        }
    }
}

void Juego::mostrarManos()
{    std::cout << "\nManos de los jugadores:\n";
    for (int i = 0; i < jugadores.getLongitud(); i++) {
        Jugador* jugador = jugadores.get(i);
        if (jugador != nullptr) {
            std::cout << "\n" << jugador->getNombre() << " tiene " << jugador->getCantidadCartas() << " cartas:\n";
            jugador->mostrarCartas();
        }
    }
}

void Juego::limpiarPantalla() {
    std::cout << "\033[2J\033[H";
}

int Juego::leerOpcionMenu() {
    while (true) {
        std::cout << "Seleccione una opción: ";
        std::string entrada;
        if (!std::getline(std::cin >> std::ws, entrada)) {
            std::cin.clear();
            return 0;
        }

        if (entrada.empty()) {
            std::cout << "Entrada vacía. Intente nuevamente.\n";
            continue;
        }

        try {
            size_t idx = 0;
            int opcion = std::stoi(entrada, &idx);
            if (idx != entrada.size()) {
                throw std::invalid_argument("Entrada inválida");
            }
            return opcion;
        } catch (const std::exception&) {
            std::cout << "Entrada inválida. Ingrese un número.\n";
        }
    }
}

const char* Juego::boolTexto(bool valor) {
    return valor ? "true" : "false";
}

void Juego::mostrarMazo() {
    
    std::cout << "\nCartas en el mazo:\n";
    int n = mazo.getLongitud();
    if (n <= 0) {
        return;
    }

    Carta** cartas = new Carta*[n];
    for (int i = 0; i < n; i++) {
        cartas[i] = mazo.sacar();
    }

    for (int i = 0; i < n; i++) {
        if (cartas[i] != nullptr) {
            std::cout << cartas[i]->getLadoActual()->toString() << "\n";
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        mazo.insertar(cartas[i]);
    }

    delete[] cartas;
}

void Juego::mostrarTopeDescarte() {
    Lado* ladoTope = descarte.verCima()->getLadoActual();
    std::cout << "\nTope del descarte: "
              << (ladoTope ? ladoTope->toString() : "(vacío)") << "\n";
}

void Juego::mostrarCartasJugador(Jugador* jugador) {
    if (jugador == nullptr) {
        return;
    }
    for (int i = 0; i < jugador->getCantidadCartas(); i++) {
        Carta* carta = jugador->getCartas().get(i);
        if (carta != nullptr) {
            std::cout << i + 1 << ". " << carta->getLadoActual()->toString() << "\n";
        }
    }
}

bool Juego::jugadorTieneCartaCompatible(Jugador* jugador, Lado* tope) {
    if (jugador == nullptr || tope == nullptr) {
        return false;
    }
    for (int i = 0; i < jugador->getCantidadCartas(); i++) {
        Carta* carta = jugador->getCartas().get(i);
        Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
        if (ladoActual != nullptr && ladoActual->esCompatible(*tope)) {
            return true;
        }
    }
    return false;
}

int Juego::pedirIndiceCarta(Jugador* jugador, const char* mensaje) {
    if (jugador == nullptr) {
        return -1;
    }
    int indice = -1;
    while (indice < 1 || indice > jugador->getCantidadCartas()) {
        std::cout << mensaje;
        indice = leerOpcionMenu();
        if (indice < 1 || indice > jugador->getCantidadCartas()) {
            std::cout << "Indice inválido.\n";
        }
    }
    return indice - 1;
}

void Juego::jugarCarta(Jugador* jugador, int indice) {
    Carta* carta = jugador->getCartas().get(indice);
    jugador->getCartas().eliminar(indice);
    descarte.insertar(carta);
    std::cout << jugador->getNombre() << " descarta: "
              << carta->getLadoActual()->toString() << "\n";
    carta->aplicarEfecto(*this);
}

void Juego::iniciarTurnos() {
    std::cout << "\nIniciando turnos...\n";
    int totalJugadores = jugadores.getLongitud();
    if (totalJugadores <= 0) {
        std::cout << "No hay jugadores para iniciar turnos.\n";
        return;
    }

    Jugador* jugadorInicial = jugadores.get(0);
    if (jugadorInicial == nullptr || jugadorInicial->getCantidadCartas() == 0) {
        std::cout << "No hay cartas suficientes para iniciar turnos.\n";
        return;
    }

    limpiarPantalla();
    std::cout << "\nTurno inicial de " << jugadorInicial->getNombre() << ":\n";
    mostrarCartasJugador(jugadorInicial);

    int indiceInicial = pedirIndiceCarta(jugadorInicial, "Seleccione la carta para iniciar el descarte: ");
    Carta* cartaInicial = jugadorInicial->getCartas().get(indiceInicial);
    jugadorInicial->getCartas().eliminar(indiceInicial);
    descarte.insertar(cartaInicial);
    std::cout << jugadorInicial->getNombre() << " descarta: "
              << cartaInicial->getLadoActual()->toString() << "\n";

    bool hayGanador = false;
    while (!hayGanador) {
        for (int i = 1; i < totalJugadores; i++) {
            Jugador* jugador = jugadores.get(i);
            if (jugador == nullptr) {
                continue;
            }
            if (jugador->getCantidadCartas() == 0) {
                std::cout << "\n" << jugador->getNombre() << " ha ganado.\n";
                hayGanador = true;
                break;
            }

            limpiarPantalla();
            mostrarTopeDescarte();
            Lado* ladoTope = descarte.verCima()->getLadoActual();
            std::cout << "\nTurno de " << jugador->getNombre() << ":\n";

            if (!jugadorTieneCartaCompatible(jugador, ladoTope)) {
                std::cout << jugador->getNombre() << " no tiene cartas compatibles.\n";
                continue;
            }

            mostrarCartasJugador(jugador);

            while (true) {
                int indice = pedirIndiceCarta(jugador, "Seleccione la carta a jugar: ");
                Carta* carta = jugador->getCartas().get(indice);
                Lado* ladoActual = carta ? carta->getLadoActual() : nullptr;
                if (ladoActual != nullptr && ladoTope != nullptr && ladoActual->esCompatible(*ladoTope)) {
                    jugarCarta(jugador, indice);
                    break;
                }

                std::cout << "Esa carta no es compatible con el tope.\n";
            }

            if (jugador->getCantidadCartas() == 0) {
                std::cout << "\n" << jugador->getNombre() << " ha ganado.\n";
                hayGanador = true;
                break;
            }
        }
    }
}

// TODO: implementar creacion del mazo completo, efectos de los lados en el juego,
// toma de cartas cuando no hay compatibles, modos especiales.





