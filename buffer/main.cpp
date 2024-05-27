#include <iostream>
#include <string>
#include <limits>
#include "BufferManager.h"

void bufferOperation(const std::string& operation, int pageID, BufferManager& manager) {
    try {
        Frame& frame = manager.requestPage(pageID);
        if (operation == "W") {
            frame.setDirty(true);
            std::cout << "Pagina " << pageID << " escrita y marcada como sucia.\n";
        }
        else if (operation == "L") {
            std::cout << "Pagina " << pageID << " leida.\n";
        }
        manager.releasePage(pageID);  // Despinnea la pagina independientemente de la operacion para liberar el recurso
    }
    catch (const std::exception& e) {
        std::cout << "Error al procesar la pagina: " << e.what() << "\n";
    }
}

void loadPageToMemory(int pageID, BufferManager& manager) {
    if (!manager.checkPage(pageID)) {
        manager.setPage(pageID);
        std::cout << "Pagina " << pageID << " cargada satisfactoriamente en la memoria.\n";
    }
    else {
        std::cout << "Pagina " << pageID << " ya esta en memoria.\n";
    }
}

void releasePageFromMemory(int pageID, BufferManager& manager) {
    if (manager.checkPage(pageID)) {
        manager.releasePage(pageID);
        std::cout << "Pagina " << pageID << " liberada de la memoria.\n";
    }
    else {
        std::cout << "Pagina " << pageID << " no esta en memoria o ya fue liberada.\n";
    }
}

void displayMenu(BufferManager& manager) {
    int choice, pageID;
    std::string operation;

    while (true) {
        std::cout << "\n########  GESTION DE MEMORIA  ########\n";
        std::cout << "1. Solicitar pagina (Lectura/Escritura)\n";
        std::cout << "2. Cargar pagina del disco a la memoria\n";
        std::cout << "3. Liberar pagina de la memoria\n";
        std::cout << "4. Imprimir tabla de paginas\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Ingrese ID de pagina: ";
            std::cin >> pageID;
            std::cout << "Ingrese operacion (L para leer, W para escribir): ";
            std::cin >> operation;
            if (operation == "L" || operation == "W") {
                bufferOperation(operation, pageID, manager);
            }
            else {
                std::cout << "Operacion invalida. Intente de nuevo.\n";
            }
            break;
        case 2:
            std::cout << "Ingrese ID de pagina para cargar: ";
            std::cin >> pageID;
            loadPageToMemory(pageID, manager);
            break;
        case 3:
            std::cout << "Ingrese ID de pagina para liberar: ";
            std::cin >> pageID;
            releasePageFromMemory(pageID, manager);
            break;
        case 4:
            manager.printPageTable();
            break;
        case 5:
            std::cout << "Saliendo del programa...\n";
            return;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    }
}

int main() {
    BufferManager bufferManager(5);  // Suponiendo un tamaño del buffer de 5 frames
    displayMenu(bufferManager);
    return 0;
}
