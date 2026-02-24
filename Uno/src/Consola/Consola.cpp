#include "Consola.h"
#include <iostream>

void Consola::limpiarPantalla() {
    std::cout << "\033[2J\033[H";
}

void Consola::esperarContinuar() {
    std::cout << "Presione Enter para continuar...";
    std::string linea;
    std::getline(std::cin, linea);
}

int Consola::leerOpcionMenu(const std::string& mensaje) {
    while (true) {
        std::cout << mensaje;
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

std::string Consola::pedirTextoNoVacio(const std::string& mensaje) {
    std::string texto;
    while (texto.empty()) {
        std::cout << mensaje;
        std::getline(std::cin >> std::ws, texto);
        if (texto.empty()) {
            std::cout << "El texto no puede estar vacío.\n";
        }
    }
    return texto;
}

int Consola::pedirEnteroMinimo(const std::string& mensaje, int minimo) {
    int valor = 0;
    while (valor < minimo) {
        std::cout << mensaje;
        valor = leerOpcionMenu();
        if (valor < minimo) {
            std::cout << "Debe ingresar al menos " << minimo << ".\n";
        }
    }
    return valor;
}

int Consola::pedirIndiceCarta(int totalCartas, const std::string& mensaje) {
    int indice = -1;
    while (indice < 1 || indice > totalCartas) {
        std::cout << mensaje;
        indice = leerOpcionMenu();
        if (indice < 1 || indice > totalCartas) {
            std::cout << "Indice inválido.\n";
        }
    }
    return indice - 1;
}

const char* Consola::boolTexto(bool valor) {
    return valor ? "true" : "false";
}

Color Consola::pedirColorClaro(const std::string& nombreJugador) {
    while (true) {
        std::cout << "\n" << nombreJugador << ", elige el color del comodín:\n";
        std::cout << "1. Rojo\n";
        std::cout << "2. Verde\n";
        std::cout << "3. Azul\n";
        std::cout << "4. Amarillo\n";

        int opcion = leerOpcionMenu();
        switch (opcion) {
            case 1:
                return Color::Rojo;
            case 2:
                return Color::Verde;
            case 3:
                return Color::Azul;
            case 4:
                return Color::Amarillo;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    }
}

Color Consola::pedirColorOscuro(const std::string& nombreJugador) {
    while (true) {
        std::cout << "\n" << nombreJugador << ", elige el color oscuro:\n";
        std::cout << "1. Rosa\n";
        std::cout << "2. Turquesa\n";
        std::cout << "3. Naranja\n";
        std::cout << "4. Violeta\n";

        int opcion = leerOpcionMenu();
        switch (opcion) {
            case 1:
                return Color::Rosa;
            case 2:
                return Color::Turquesa;
            case 3:
                return Color::Naranja;
            case 4:
                return Color::Violeta;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    }
}
