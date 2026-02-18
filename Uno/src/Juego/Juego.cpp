#include "Juego.h"
#include <iostream>
#include <string>

Juego::Juego(/* args */)
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
    repartirCartas();
    mostrarManos();
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
}

void Juego::mostrarManos()
{
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
