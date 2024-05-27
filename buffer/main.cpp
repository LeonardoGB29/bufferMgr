#include <iostream>
#include <string>
#include <limits>
#include "BufferManager.h"
#include <iostream>
#include <string>
#include <limits>
#include "BufferManager.h"

void bufferOperation(const std::string& operation, int pageID, BufferManager& manager) {
    std::cout << "pageID: " << pageID << ".\n";
    Frame& frame = manager.requestPage(pageID);
    if (operation == "W") {
        frame.setDirty(true);
        std::cout << "P�gina " << pageID << " escrita y marcada como sucia.\n";
    }
    else if (operation == "L") {
        std::cout << "P�gina " << pageID << " le�da.\n";
    }
    manager.releasePage(pageID);  // despinne la p�gina independientemente de la operaci�n para liberar el recurso
}

void loadPageToMemory(int pageID, BufferManager& manager) {
    if (!manager.checkPage(pageID)) {
        manager.setPage(pageID);
        std::cout << "P�gina " << pageID << " cargada satisfactoriamente en la memoria.\n";
    }
    else {
        std::cout << "P�gina " << pageID << " ya est� en memoria.\n";
    }
}

void displayMenu(BufferManager& manager) {
    int choice, pageID;
    std::string operation;

    while (true) {
        std::cout << "\n########  GESTION DE MEMORIA  ########\n";
        std::cout << "1. Solicitar pagina (Lectura/Escritura)\n";
        std::cout << "2. Cargar pagina del disco a la memoria\n";
        std::cout << "3. Imprimir tabla de p�ginas\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Ingrese ID de pagina: ";
            std::cin >> pageID;
            std::cout << "Ingrese operaci�n (L para leer, W para escribir): ";
            std::cin >> operation;
            if (operation == "L" || operation == "W") {
                bufferOperation(operation, pageID, manager);
            }
            else {
                std::cout << "Operaci�n invalida. Intente de nuevo.\n";
            }
            break;
        case 2:
            std::cout << "Ingrese ID de p�gina para cargar: ";
            std::cin >> pageID;
            loadPageToMemory(pageID, manager);
            break;
        case 3:
            manager.printPageTable();
            break;
        case 4:
            std::cout << "Saliendo del programa...\n";
            return;
        default:
            std::cout << "Opci�n no valida. Intente de nuevo.\n";
        }
    }
}

int main() {
    BufferManager bufferManager(5);  // Suponiendo un tama�o del buffer de 5 frames
    displayMenu(bufferManager);
    return 0;
}