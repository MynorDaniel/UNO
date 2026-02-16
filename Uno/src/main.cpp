#include <iostream>
#include <stdexcept>
#include "ListaCircularDoble/ListaCircularDoble.h"

using namespace std;

int main() {

    cout << "\n========== PROBANDO LISTA CIRCULAR DOBLE ==========\n";

    ListaCircularDoble<int> lista;

    cout << "\n¿Está vacía? "
         << (lista.isEmpty() ? "Sí" : "No") << endl;

    cout << "\nInsertando 10, 20, 30, 40, 50...\n";
    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);
    lista.insertar(50);

    cout << "Longitud: " << lista.getLongitud() << endl;

    cout << "\nLista completa:\n";
    lista.imprimir();

    cout << "\nBuscando valor 30: "
         << (lista.buscar(30) ? "Encontrado" : "No encontrado") << endl;

    cout << "Buscando valor 99: "
         << (lista.buscar(99) ? "Encontrado" : "No encontrado") << endl;

     cout << "\nEliminando el índice 2 (valor 30)...\n";
     lista.eliminar(2);
    cout << "Longitud: " << lista.getLongitud() << endl;
    cout << "Lista actual:\n";
    lista.imprimir();

     cout << "\nEliminando el índice 0 (cabeza)...\n";
     lista.eliminar(0);
    cout << "Longitud: " << lista.getLongitud() << endl;
    cout << "Lista actual:\n";
    lista.imprimir();

     cout << "\nEliminando el índice " << (lista.getLongitud() - 1) << " (último)...\n";
     lista.eliminar(lista.getLongitud() - 1);
    cout << "Longitud: " << lista.getLongitud() << endl;
    cout << "Lista actual:\n";
    lista.imprimir();

     cout << "\nEliminando todos los elementos restantes...\n";
     lista.eliminar(1);
     lista.eliminar(0);
    cout << "Longitud: " << lista.getLongitud() << endl;

    cout << "\n¿Está vacía ahora? "
         << (lista.isEmpty() ? "Sí" : "No") << endl;

    cout << "\nIntentando imprimir lista vacía:\n";
    lista.imprimir();

    return 0;
}
