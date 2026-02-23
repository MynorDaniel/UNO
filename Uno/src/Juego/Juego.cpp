#include "Juego.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

Juego::Juego()
        : modoAcumulacion(false),
            modoRetoMasCuatro(false),
            modoRoboSinLimite(false),
            modoGritoDeUno(false),
            modoGanarConNegra(false),
            modoFlip(false),
            colorEternoPendiente(false),
            colorEternoObjetivo(Color::Multicolor),
            repetirTurnoActual(false),
            direccionTurno(1),
            saltosPendientes(0),
            cartasRoboPendientes(0),
            retoMasCuatroPendiente(false),
            jugadorMasCuatro(nullptr),
            colorAnteriorMasCuatro(Color::Multicolor),
            numeroAnteriorMasCuatro(0),
            numeroAnteriorValido(false),
            jugadorPendienteUno(nullptr),
            jugadorActual(nullptr),
            nodoActualTurno(nullptr)
{
}

Juego::~Juego()
{

}

void Juego::iniciarJuego()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    bool jugarDeNuevo = true;

    while (jugarDeNuevo) {
        direccionTurno = 1;
        saltosPendientes = 0;
        cartasRoboPendientes = 0;
        retoMasCuatroPendiente = false;
        jugadorMasCuatro = nullptr;
        jugadorPendienteUno = nullptr;
        jugadorActual = nullptr;
        nodoActualTurno = nullptr;
        colorEternoPendiente = false;
        repetirTurnoActual = false;

        std::cout << "\n¡Bienvenido a UNO!\n";
        pedirModoJuego();
        if (!modoFlip) {
            pedirConfiguracion();
        } else {
            modoGritoDeUno = false;
            modoRetoMasCuatro = false;
        }
        pedirJugadores();
        if (modoFlip) {
            crearMazoFlip();
        } else {
            crearMazoCompleto();
        }
        repartirCartas();
        mostrarManos();
        jugarDeNuevo = iniciarTurnos();

        if (jugarDeNuevo) {
            limpiarEstado();
        }
    }
}

int Juego::calcularCantidadDeMazos(int cantidadJugadores) {
    if (cantidadJugadores <= 0) {
        return 1;
    }

    return ((cantidadJugadores - 1) / 6) + 1;
}

void Juego::crearMazoCompleto() {
    std::cout << "\nCreando el mazo completo de cartas...\n";

    int cantidadMazos = calcularCantidadDeMazos(jugadores.getLongitud());
    for (int i = 0; i < cantidadMazos; i++) {
        crearMazo();
    }

    mazo.barajear();
    mostrarMazo();
}

void Juego::crearMazo() {

    // Cartas numerica
    Color colores[] = { Color::Rojo, Color::Amarillo, Color::Verde, Color::Azul };

    auto agregarCarta = [this](int numero, Color color) {
        Carta* carta = new Carta(new LadoNumero(numero, color), nullptr);
        mazo.insertar(carta);
    };
    
    // Cartas de acción
    auto agregarAccionColor = [this](Color color) {
        mazo.insertar(new Carta(new LadoSalto(color), nullptr));
        mazo.insertar(new Carta(new LadoSalto(color), nullptr));

        mazo.insertar(new Carta(new LadoReversa(color), nullptr));
        mazo.insertar(new Carta(new LadoReversa(color), nullptr));

        mazo.insertar(new Carta(new LadoMasDos(color), nullptr));
        mazo.insertar(new Carta(new LadoMasDos(color), nullptr));
    };

    for (Color color : colores) {
        agregarCarta(0, color);
        for (int numero = 1; numero <= 9; numero++) {
            agregarCarta(numero, color);
            agregarCarta(numero, color);
        }

        agregarAccionColor(color);
    }

    // Cartas comodín y más cuatro
    for (int i = 0; i < 4; i++) {
        mazo.insertar(new Carta(new LadoComodin(), nullptr));
        mazo.insertar(new Carta(new LadoMasCuatro(), nullptr));
    }

    // Cartas especiales (Rayos X y Cambio) - 4 de cada tipo por mazo
    for (int i = 0; i < 4; i++) {
        Color color = colores[i % 4];
        mazo.insertar(new Carta(new LadoRayosX(color), nullptr));
        mazo.insertar(new Carta(new LadoCambio(color), nullptr));
    }
}

void Juego::crearMazoFlip() {
    std::cout << "\nCreando el mazo de cartas Flip...\n";

    int cantidadMazos = calcularCantidadDeMazos(jugadores.getLongitud());
    for (int indiceMazo = 0; indiceMazo < cantidadMazos; indiceMazo++) {
        std::cout << "\nMazo Flip " << indiceMazo + 1 << " de " << cantidadMazos << ":\n";

        Color coloresClaros[] = { Color::Rojo, Color::Amarillo, Color::Azul, Color::Verde };
        Color coloresOscuros[] = { Color::Rosa, Color::Turquesa, Color::Naranja, Color::Violeta };

        const int totalBase = 108;
        const int totalLados = totalBase + 8;

        Lado** ladosClaros = new Lado*[totalLados];
        Lado** ladosOscuros = new Lado*[totalLados];
        int indiceClaro = 0;
        int indiceOscuro = 0;

        auto agregarClaro = [&ladosClaros, &indiceClaro](Lado* lado) {
            ladosClaros[indiceClaro++] = lado;
        };

        auto agregarOscuro = [&ladosOscuros, &indiceOscuro](Lado* lado) {
            ladosOscuros[indiceOscuro++] = lado;
        };

        for (int i = 0; i < 4; i++) {
            Color color = coloresClaros[i];
            agregarClaro(new LadoNumero(0, color));
            for (int numero = 1; numero <= 9; numero++) {
                agregarClaro(new LadoNumero(numero, color));
                agregarClaro(new LadoNumero(numero, color));
            }

            agregarClaro(new LadoMasUnoFlip(color));
            agregarClaro(new LadoMasUnoFlip(color));

            agregarClaro(new LadoSalto(color));
            agregarClaro(new LadoSalto(color));

            agregarClaro(new LadoReversa(color));
            agregarClaro(new LadoReversa(color));
        }

        for (int i = 0; i < 4; i++) {
            agregarClaro(new LadoMasDosFlip(Color::Multicolor));
            agregarClaro(new LadoComodin());
        }

        for (int i = 0; i < 4; i++) {
            Color color = coloresOscuros[i];
            agregarOscuro(new LadoNumero(0, color));
            for (int numero = 1; numero <= 9; numero++) {
                agregarOscuro(new LadoNumero(numero, color));
                agregarOscuro(new LadoNumero(numero, color));
            }

            agregarOscuro(new LadoMasTresFlip(color));
            agregarOscuro(new LadoMasTresFlip(color));

            agregarOscuro(new LadoSaltaTodos(color));
            agregarOscuro(new LadoSaltaTodos(color));

            agregarOscuro(new LadoReversa(color));
            agregarOscuro(new LadoReversa(color));
        }

        for (int i = 0; i < 4; i++) {
            agregarOscuro(new LadoMasSeisFlip(Color::Multicolor));
            agregarOscuro(new LadoColorEterno());
        }

        for (int i = 0; i < 4; i++) {
            Color colorClaro = coloresClaros[i];
            agregarClaro(new LadoFlip(colorClaro));
            agregarClaro(new LadoFlip(colorClaro));

            Color colorOscuro = coloresOscuros[i];
            agregarOscuro(new LadoFlip(colorOscuro));
            agregarOscuro(new LadoFlip(colorOscuro));
        }

        if (indiceClaro != totalLados || indiceOscuro != totalLados) {
            std::cout << "Error: cantidad de lados claros y oscuros no coincide.\n";
        }

        for (int i = totalLados - 1; i > 0; i--) {
            int j = std::rand() % (i + 1);
            Lado* temp = ladosClaros[i];
            ladosClaros[i] = ladosClaros[j];
            ladosClaros[j] = temp;
        }

        for (int i = totalLados - 1; i > 0; i--) {
            int j = std::rand() % (i + 1);
            Lado* temp = ladosOscuros[i];
            ladosOscuros[i] = ladosOscuros[j];
            ladosOscuros[j] = temp;
        }

        int totalCartas = (indiceClaro < indiceOscuro) ? indiceClaro : indiceOscuro;
        for (int i = 0; i < totalCartas; i++) {
            Carta* carta = new Carta(ladosClaros[i], ladosOscuros[i]);
            mazo.insertar(carta);

            std::cout << "Carta " << i + 1 << ":\n";
            std::cout << "Claro: " << ladosClaros[i]->toString() << "\n";
            std::cout << "Oscuro: " << ladosOscuros[i]->toString() << "\n";
        }

        std::cout << "\nTotal de cartas creadas: " << totalCartas << "\n";

        delete[] ladosClaros;
        delete[] ladosOscuros;
    }

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

    Jugador* jugador = new Jugador(nombre, this, &mazo, &descarte);
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

    for (int i = 0; i < totalJugadores; i++)
    {
        Jugador* jugador = jugadores.get(i);
        if (jugador != nullptr) {
            for (int j = 0; j < 7; j++) {
                Carta* carta = mazo.sacar();
                jugador->tomarCarta(carta);
            }
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

void Juego::esperarContinuar() {
    std::cout << "Presione Enter para continuar...";
    std::string linea;
    std::getline(std::cin, linea);
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
    
    int n = mazo.getLongitud();
    std::cout << "\nCartas en el mazo de longitud " << n << ":\n";
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

Color Juego::pedirColorCarta(const std::string& nombreJugador) {
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

Color Juego::pedirColorOscuro(const std::string& nombreJugador) {
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

void Juego::aplicarReversa() {
    direccionTurno *= -1;
    std::cout << "El orden de turnos ha cambiado.\n";
}

void Juego::aplicarSalto() {
    saltosPendientes++;
}

void Juego::aplicarMasDos() {
    cartasRoboPendientes += 2;
    if (!modoAcumulacion) {
        saltosPendientes++;
    }
}

void Juego::aplicarMasCuatro() {
    cartasRoboPendientes += 4;
    if (modoRetoMasCuatro) {
        retoMasCuatroPendiente = true;
    } else if (!modoAcumulacion) {
        saltosPendientes++;
    }
}

void Juego::aplicarMasUnoFlip() {
    cartasRoboPendientes += 1;
    saltosPendientes++;
}

void Juego::aplicarMasDosFlip() {
    cartasRoboPendientes += 2;
    saltosPendientes++;
}

void Juego::aplicarMasTresFlip() {
    cartasRoboPendientes += 3;
    saltosPendientes++;
}

void Juego::aplicarMasSeisFlip() {
    cartasRoboPendientes += 6;
    saltosPendientes++;
}

void Juego::aplicarSaltaTodosFlip() {
    repetirTurnoActual = true;
}

void Juego::aplicarFlip() {
    int totalMazo = mazo.getLongitud();
    if (totalMazo > 0) {
        Carta** cartasMazo = new Carta*[totalMazo];
        for (int i = 0; i < totalMazo; i++) {
            cartasMazo[i] = mazo.sacar();
            if (cartasMazo[i] != nullptr) {
                cartasMazo[i]->voltear();
            }
        }
        for (int i = totalMazo - 1; i >= 0; i--) {
            mazo.insertar(cartasMazo[i]);
        }
        delete[] cartasMazo;
    }

    int totalDescarte = descarte.getLongitud();
    if (totalDescarte > 0) {
        Carta** cartasDescarte = new Carta*[totalDescarte];
        for (int i = 0; i < totalDescarte; i++) {
            cartasDescarte[i] = descarte.sacar();
            if (cartasDescarte[i] != nullptr) {
                cartasDescarte[i]->voltear();
            }
        }
        for (int i = totalDescarte - 1; i >= 0; i--) {
            descarte.insertar(cartasDescarte[i]);
        }
        delete[] cartasDescarte;
    }

    NodoCircularDoble<Jugador*>* nodo = jugadores.getCabeza();
    if (nodo != nullptr) {
        NodoCircularDoble<Jugador*>* actual = nodo;
        do {
            Jugador* jugador = actual->getDato();
            if (jugador != nullptr) {
                jugador->voltearCartas();
            }
            actual = actual->getSiguiente();
        } while (actual != nodo);
    }

    std::cout << "Todas las cartas fueron volteadas.\n";
}

void Juego::aplicarColorEterno(Color colorElegido) {
    colorEternoPendiente = true;
    colorEternoObjetivo = colorElegido;
}

void Juego::registrarMasCuatro(Jugador* jugador, const Lado& topeAntes) {
    jugadorMasCuatro = jugador;
    colorAnteriorMasCuatro = topeAntes.getColor();
    const LadoNumero* numero = dynamic_cast<const LadoNumero*>(&topeAntes);
    if (numero != nullptr) {
        numeroAnteriorMasCuatro = numero->getNumero();
        numeroAnteriorValido = true;
    } else {
        numeroAnteriorValido = false;
    }
}

bool Juego::isModoRoboSinLimite() const {
    return modoRoboSinLimite;
}

void Juego::revelarCartasSiguiente() {
    NodoCircularDoble<Jugador*>* nodoSiguiente = obtenerNodoSiguiente();
    if (nodoSiguiente == nullptr) {
        return;
    }
    Jugador* siguiente = nodoSiguiente->getDato();
    if (siguiente == nullptr) {
        return;
    }

    std::cout << "\nCartas de " << siguiente->getNombre() << ":\n";
    mostrarCartasJugador(siguiente);
}

void Juego::intercambiarCartasConAnterior() {
    if (jugadorActual == nullptr) {
        return;
    }

    NodoCircularDoble<Jugador*>* nodoAnterior = obtenerNodoAnterior();
    if (nodoAnterior == nullptr) {
        return;
    }

    Jugador* anterior = nodoAnterior->getDato();
    if (anterior == nullptr) {
        return;
    }

    jugadorActual->intercambiarCartasCon(*anterior);
    std::cout << jugadorActual->getNombre() << " intercambió cartas con " << anterior->getNombre() << ".\n";
}

std::string Juego::getNombreJugadorActual() const {
    return jugadorActual != nullptr ? jugadorActual->getNombre() : "Jugador";
}

bool Juego::preguntarReinicio() {
    while (true) {
        std::cout << "\n¿Desea jugar otra vez?\n";
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";

        int opcion = leerOpcionMenu();
        if (opcion == 1) {
            return true;
        }
        if (opcion == 2) {
            return false;
        }

        std::cout << "Opción inválida. Intente nuevamente.\n";
    }
}

void Juego::pedirModoJuego() {
    while (true) {
        std::cout << "\nSeleccione el modo de juego:\n";
        std::cout << "1. UNO\n";
        std::cout << "2. UNO Flip\n";

        int opcion = leerOpcionMenu();
        if (opcion == 1) {
            modoFlip = false;
            return;
        }
        if (opcion == 2) {
            modoFlip = true;
            return;
        }

        std::cout << "Opción inválida. Intente nuevamente.\n";
    }
}

void Juego::limpiarEstado() {
    while (!mazo.isEmpty()) {
        Carta* carta = mazo.sacar();
        delete carta;
    }

    while (!descarte.isEmpty()) {
        Carta* carta = descarte.sacar();
        delete carta;
    }

    while (jugadores.getLongitud() > 0) {
        Jugador* jugador = jugadores.get(0);
        delete jugador;
        jugadores.eliminar(0);
    }
}

bool Juego::aplicarEfectosInicioTurno(Jugador* jugador) {
    if (jugador == nullptr) {
        return false;
    }

    if (colorEternoPendiente) {
        std::cout << jugador->getNombre() << " debe robar hasta encontrar " << colorToString(colorEternoObjetivo) << ".\n";
        while (!mazo.isEmpty()) {
            Carta* carta = mazo.sacar();
            jugador->tomarCarta(carta);
            if (carta != nullptr && carta->getLadoActual()->getColor() == colorEternoObjetivo) {
                break;
            }
        }
        colorEternoPendiente = false;
        saltosPendientes++;
    }

    if (retoMasCuatroPendiente && modoRetoMasCuatro) {
        return manejarRetoMasCuatro(jugador);
    }

    if (modoAcumulacion && cartasRoboPendientes > 0) {
        return false;
    }

    if (cartasRoboPendientes > 0) {
        std::cout << jugador->getNombre() << " debe robar " << cartasRoboPendientes << " carta(s).\n";
        jugador->robarCartas(cartasRoboPendientes);
        cartasRoboPendientes = 0;
        if (saltosPendientes < 1) {
            saltosPendientes = 1;
        }
    }

    if (saltosPendientes > 0) {
        std::cout << jugador->getNombre() << " pierde el turno.\n";
        saltosPendientes--;
        return true;
    }

    return false;
}

NodoCircularDoble<Jugador*>* Juego::obtenerNodoSiguiente() const {
    if (nodoActualTurno == nullptr) {
        return nullptr;
    }
    return (direccionTurno == 1) ? nodoActualTurno->getSiguiente() : nodoActualTurno->getAnterior();
}

NodoCircularDoble<Jugador*>* Juego::obtenerNodoAnterior() const {
    if (nodoActualTurno == nullptr) {
        return nullptr;
    }
    return (direccionTurno == 1) ? nodoActualTurno->getAnterior() : nodoActualTurno->getSiguiente();
}

int Juego::avanzarIndiceJugador(int indiceActual, int pasos) const {
    int total = jugadores.getLongitud();
    if (total <= 0) {
        return 0;
    }

    int nuevoIndice = (indiceActual + pasos) % total;
    if (nuevoIndice < 0) {
        nuevoIndice += total;
    }
    return nuevoIndice;
}

bool Juego::validarJugada(const Jugador* jugador, const Carta* carta, const Lado& tope, bool acumulacionActiva) const {
    if (jugador == nullptr || carta == nullptr) {
        return false;
    }

    Lado* lado = carta->getLadoActual();
    if (lado == nullptr || !lado->esCompatible(tope)) {
        return false;
    }

    if (!modoGanarConNegra && jugador->getCantidadCartas() == 1 && esCartaNegra(carta)) {
        std::cout << "No puedes ganar con una carta negra.\n";
        return false;
    }

    if (acumulacionActiva) {
        bool topeMasDos = dynamic_cast<const LadoMasDos*>(&tope) != nullptr;
        bool topeMasCuatro = dynamic_cast<const LadoMasCuatro*>(&tope) != nullptr;
        bool cartaMasDos = dynamic_cast<LadoMasDos*>(lado) != nullptr;
        bool cartaMasCuatro = dynamic_cast<LadoMasCuatro*>(lado) != nullptr;

        if (topeMasDos && !cartaMasDos) {
            return false;
        }
        if (topeMasCuatro && !cartaMasCuatro) {
            return false;
        }
        if (topeMasDos && cartaMasCuatro) {
            return false;
        }
        if (topeMasCuatro && cartaMasDos) {
            return false;
        }
    }

    return true;
}

bool Juego::manejarRetoMasCuatro(Jugador* jugadorActual) {
    if (!retoMasCuatroPendiente || jugadorActual == nullptr) {
        return false;
    }

    limpiarPantalla();
    std::cout << "\n" << jugadorActual->getNombre() << ", ¿Deseas retar el +4?\n";
    std::cout << "1. Sí\n";
    std::cout << "2. No\n";

    int opcion = leerOpcionMenu();
    bool reto = (opcion == 1);

    if (reto) {
        bool teniaColor = jugadorMasCuatro != nullptr && jugadorMasCuatro->tieneCartaDeColor(colorAnteriorMasCuatro);
        bool teniaNumero = jugadorMasCuatro != nullptr && numeroAnteriorValido && jugadorMasCuatro->tieneCartaNumero(numeroAnteriorMasCuatro);

        if (teniaColor || teniaNumero) {
            std::cout << "El reto fue exitoso. " << jugadorMasCuatro->getNombre() << " roba 4.\n";
            jugadorMasCuatro->robarCartas(4);
            retoMasCuatroPendiente = false;
            cartasRoboPendientes = 0;
            return false;
        }

        std::cout << "El reto falló. " << jugadorActual->getNombre() << " roba 6 y pierde el turno.\n";
        jugadorActual->robarCartas(6);
        retoMasCuatroPendiente = false;
        cartasRoboPendientes = 0;
        return true;
    }

    std::cout << jugadorActual->getNombre() << " roba 4 y pierde el turno.\n";
    jugadorActual->robarCartas(4);
    retoMasCuatroPendiente = false;
    cartasRoboPendientes = 0;
    return true;
}

void Juego::manejarGritoUno(Jugador* jugador) {
    if (jugador == nullptr || !modoGritoDeUno) {
        return;
    }

    if (jugador->getCantidadCartas() == 1) {
        std::cout << "\n" << jugador->getNombre() << ", escribe UNO para declararlo: ";
        std::string entrada;
        std::getline(std::cin >> std::ws, entrada);
        if (entrada != "UNO" && entrada != "uno") {
            std::cout << "No se declaró UNO. Puedes ser reportado.\n";
            jugadorPendienteUno = jugador;
        } else {
            jugadorPendienteUno = nullptr;
        }
    }
}

void Juego::manejarReporteUno(Jugador* jugadorReportador) {
    if (!modoGritoDeUno || jugadorReportador == nullptr) {
        return;
    }

    std::cout << "\n" << jugadorReportador->getNombre() << ", ¿Deseas reportar un UNO?\n";
    std::cout << "1. Sí\n";
    std::cout << "2. No\n";

    int opcion = leerOpcionMenu();
    bool reporta = (opcion == 1);

    if (!reporta) {
        jugadorPendienteUno = nullptr;
        return;
    }

    if (jugadorPendienteUno != nullptr) {
        std::cout << jugadorPendienteUno->getNombre() << " es penalizado con 2 cartas.\n";
        jugadorPendienteUno->robarCartas(2);
    } else {
        std::cout << "Reporte incorrecto. " << jugadorReportador->getNombre() << " roba 2 cartas.\n";
        jugadorReportador->robarCartas(2);
    }

    jugadorPendienteUno = nullptr;
}

bool Juego::esCartaNegra(const Carta* carta) const {
    if (carta == nullptr) {
        return false;
    }

    Lado* lado = carta->getLadoActual();
    return dynamic_cast<LadoComodin*>(lado) != nullptr || dynamic_cast<LadoMasCuatro*>(lado) != nullptr;
}

bool Juego::iniciarTurnos() {
    std::cout << "\nIniciando turnos...\n";

    // Verificar que haya jugadores y cartas para iniciar el juego
    int totalJugadores = jugadores.getLongitud();
    if (totalJugadores <= 0) {
        std::cout << "No hay jugadores para iniciar turnos.\n";
        return false;
    }

    // Verificar que el primer jugador tenga cartas para iniciar el juego
    NodoCircularDoble<Jugador*>* nodoInicial = jugadores.getCabeza();
    if (nodoInicial == nullptr) {
        std::cout << "No hay cartas suficientes para iniciar turnos.\n";
        return false;
    }

    Jugador* jugadorInicial = nodoInicial->getDato();
    if (jugadorInicial == nullptr || jugadorInicial->getCantidadCartas() == 0) {
        std::cout << "No hay cartas suficientes para iniciar turnos.\n";
        return false;
    }

    // Seleccionar la carta inicial para el descarte
    limpiarPantalla();
    std::cout << "\nTurno inicial de " << jugadorInicial->getNombre() << ":\n";
    mostrarCartasJugador(jugadorInicial);

    // Pedir al jugador inicial que seleccione una carta para iniciar el descarte
    int indiceInicial = pedirIndiceCarta(jugadorInicial, "Seleccione la carta para iniciar el descarte: ");
    Carta* cartaInicial = jugadorInicial->getCartas().get(indiceInicial);
    jugadorInicial->getCartas().eliminar(indiceInicial);
    descarte.insertar(cartaInicial);
    std::cout << jugadorInicial->getNombre() << " descarta: "
              << cartaInicial->getLadoActual()->toString() << "\n";

    bool hayGanador = false;
    std::string nombreGanador;
    NodoCircularDoble<Jugador*>* nodoActual = nodoInicial;
    if (totalJugadores > 1) {
        nodoActual = nodoActual->getSiguiente();
    }

    // Bucle principal de turnos
    while (!hayGanador) {

        // Verificar que el jugador actual exista y tenga cartas
        if (nodoActual == nullptr) {
            break;
        }

        Jugador* jugador = nodoActual->getDato();
        if (jugador == nullptr) {
            nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
            continue;
        }

        jugadorActual = jugador;
        nodoActualTurno = nodoActual;

        // Verificar si el jugador actual ya ha ganado
        if (jugador->getCantidadCartas() == 0) {
            std::cout << "\n" << jugador->getNombre() << " ha ganado.\n";
            nombreGanador = jugador->getNombre();
            hayGanador = true;
            break;
        }

        // Aplicar efectos pendientes al inicio del turno
        if (aplicarEfectosInicioTurno(jugador)) {
            esperarContinuar();
            nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
            continue;
        }

        // Mostrar el estado actual del juego
        limpiarPantalla();
        mostrarTopeDescarte();
        Lado* ladoTope = descarte.verCima()->getLadoActual();
        std::cout << "\nTurno de " << jugador->getNombre() << ":\n";

        bool acumulacionActiva = modoAcumulacion && cartasRoboPendientes > 0;

        if (!modoGanarConNegra && jugador->getCantidadCartas() == 1) {
            Carta* cartaUnica = jugador->getCartas().get(0);
            if (esCartaNegra(cartaUnica)) {
                std::cout << jugador->getNombre() << " no puede jugar una carta negra como última.\n";
                jugador->manejarSinCompatibles(*ladoTope);
                esperarContinuar();
                nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
                continue;
            }
        }

        if (acumulacionActiva && !jugador->tieneCartaAcumulable(*ladoTope)) {
            std::cout << jugador->getNombre() << " no puede acumular y debe robar " << cartasRoboPendientes << " carta(s).\n";
            jugador->robarCartas(cartasRoboPendientes);
            cartasRoboPendientes = 0;
            esperarContinuar();
            nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
            continue;
        }

        // Verificar si el jugador tiene cartas compatibles con el tope del descarte
        if (!jugador->tieneCartaCompatible(*ladoTope)) {
            jugador->manejarSinCompatibles(*ladoTope);

            // Verificar si el jugador actual ha ganado después de robar
            if (jugador->getCantidadCartas() == 0) {
                std::cout << "\n" << jugador->getNombre() << " ha ganado.\n";
                nombreGanador = jugador->getNombre();
                hayGanador = true;
                break;
            }

            esperarContinuar();

            // Pasar al siguiente jugador, se usa % para ciclar de vuelta al inicio de la lista de jugadores
            nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
            continue;
        }

        // Pedir al jugador que seleccione una carta para jugar o reportar UNO
        while (true) {
            mostrarCartasJugador(jugador);
            int totalCartas = jugador->getCantidadCartas();
            if (modoGritoDeUno) {
                std::cout << totalCartas + 1 << ". Reportar UNO\n";
            }

            int opcion = leerOpcionMenu();

            if (modoGritoDeUno && opcion == totalCartas + 1) {
                manejarReporteUno(jugador);
                continue;
            }

            if (opcion < 1 || opcion > totalCartas) {
                std::cout << "Indice inválido.\n";
                continue;
            }

            int indice = opcion - 1;
            Carta* cartaSeleccionada = jugador->getCartas().get(indice);
            if (!validarJugada(jugador, cartaSeleccionada, *ladoTope, acumulacionActiva)) {
                std::cout << "Esa carta no es compatible con las reglas actuales.\n";
                continue;
            }

            if (jugador->jugarCarta(indice, *ladoTope)) {
                manejarGritoUno(jugador);
                break;
            }

            std::cout << "Esa carta no es compatible con el tope.\n";
        }

        // Verificar si el jugador actual ha ganado después de jugar
        if (jugador->getCantidadCartas() == 0) {
            std::cout << "\n" << jugador->getNombre() << " ha ganado.\n";
            nombreGanador = jugador->getNombre();
            hayGanador = true;
            break;
        }

        if (repetirTurnoActual) {
            repetirTurnoActual = false;
            continue;
        }

        nodoActual = (direccionTurno == 1) ? nodoActual->getSiguiente() : nodoActual->getAnterior();
    }

    if (!hayGanador) {
        return false;
    }

    bool jugarDeNuevo = preguntarReinicio();
    if (!jugarDeNuevo) {
        std::cout << "\nSaliendo...\n";
    }
    return jugarDeNuevo;
}







