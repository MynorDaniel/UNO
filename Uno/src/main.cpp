#include <iostream>
#include "Lista/Lista.h"

int main(int, char**){
    Lista<int> lista;

    lista.agregar(10);
    lista.agregar(20);
    lista.agregar(30);
    lista.agregar(40);

    for (int i = 0; i < lista.getLongitud(); i++) {
        std::cout << "Elemento en índice " << i << ": " << lista.get(i) << std::endl;
    }
}
