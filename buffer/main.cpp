//#include <iostream>
//#include <string>
//#include <limits>
//#include "BufferManager.h"
//
//void bufferOperation(const std::string& operation, int pageID, BufferManager& manager) {
//    Frame& frame = manager.requestPage(pageID);
//    if (operation == "W") {
//        frame.setDirty(true);
//        std::cout << "Pagina " << pageID << " escrita y marcada como sucia.\n";
//    }
//    else if (operation == "L") {
//        std::cout << "Pagina " << pageID << " le�da.\n";
//    }
//    manager.unpinPage(pageID);  // Despinne la pagina independientemente de la operaci�n para liberar el recurso
//}
//
//// Agrega la funci�n 'loadPageToMemory' si es necesaria para cargar expl�citamente p�ginas
//void loadPageToMemory(int pageID, BufferManager& manager) {
//    Frame& frame = manager.requestPage(pageID);
//    std::cout << "Pagina " << pageID << " cargada en el Frame ID: " << frame.pageID << ".\n";
//}
//
//void displayMenu(BufferManager& bufferManager) {
//    int choice;
//    int pageID;
//    std::string operation;
//
//    while (true) {
//        std::cout << "########  MENU  ########\n\n";
//        std::cout << "1. Solicitar pagina\n";
//        std::cout << "2. Cargar pagina del disco a la memoria\n";
//        std::cout << "3. Imprimir Page Table\n";
//        std::cout << "4. Salir\n\n";
//        std::cout << "Ingrese su eleccion: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1:
//            std::cout << "Ingrese ID de pagina: ";
//            std::cin >> pageID;
//            std::cout << "Ingrese operaci�n (L para leer, W para escribir): ";
//            std::cin >> operation;
//            if (operation == "L" || operation == "W") {
//                bufferOperation(operation, pageID, bufferManager);
//            }
//            else {
//                std::cout << "Operacion invalida. Intente de nuevo.\n";
//            }
//            break;
//        case 2:
//            std::cout << "Ingrese ID de pagina para cargar: ";
//            std::cin >> pageID;
//            if (std::cin.fail()) {
//                std::cin.clear();
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                std::cout << "Entrada no valida. Intente de nuevo.\n";
//                continue;
//            }
//            loadPageToMemory(pageID, bufferManager);
//            break;
//        case 3:
//            bufferManager.printPageTable();
//            break;
//        case 4:
//            std::cout << "Saliendo del programa...\n";
//            return;
//        default:
//            std::cout << "Opcion no valida. Intente de nuevo.\n";
//        }
//    }
//}
//
//int main() {
//    BufferManager bufferManager(5);  // Suponiendo un tama�o del buffer de 5 frames
//    displayMenu(bufferManager);
//    return 0;
//}
//