#include <iostream>
#include "PageTable.h"
#include "Replacer.h"
#include <iomanip>

void mostrarMenu(int numPaginas, int numFrames) {
    std::cout << "\nMenu:\n";
    std::cout << "1. Agregar frames\n";
    std::cout << "2. Agregar pagina\n";
    std::cout << "3. Acceder a pagina\n";
    std::cout << "4. Simular reemplazo de pagina\n";
    std::cout << "5. Mostrar tabla de paginas\n";
    std::cout << "6. Mostrar cola de reemplazo\n";
    std::cout << "7. Salir\n";
    std::cout << "Paginas disponibles: " << numPaginas << ", Frames disponibles: " << numFrames << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void agregarFrames(PageTable& pageTable, Replacer& replacer, int& numPaginas, int& numFrames) {
    int numFramesToAdd;
    std::cout << "Ingrese la cantidad de frames que se van a requerir: ";
    std::cin >> numFramesToAdd;

    // Asignar IDs de tres dígitos a los frames
    for (int i = 0; i < numFramesToAdd; ++i) {
        int frameID = 100 + numFrames + 1; // Asignar IDs de tres dígitos a los frames
        std::cout << "Frame " << std::setw(3) << std::setfill('0') << frameID << " agregado." << std::endl;
        replacer.addCola(frameID);
        numFrames++;
    }
    
    // No asociar inicialmente los frames a ninguna página
    std::cout << "Los frames han sido agregados. Asociaremos paginas a los frames mas tarde." << std::endl;
}

void agregarPagina(PageTable& pageTable, Replacer& replacer, int& numPaginas) {
    int pageID, frameID;
    std::cout << "Ingrese el ID de la nueva pagina: ";
    std::cin >> pageID;
    std::cout << "Ingrese el ID del frame al que desea asignar la pagina: ";
    std::cin >> frameID;

    // Verificar si el frameID ya está ocupado
    bool frameOccupied = false;
    for (const auto& [pID, fID] : pageTable.pageMap) {
        if (fID == frameID) {
            frameOccupied = true;
            break;
        }
    }

    if (frameOccupied) {
        std::cout << "El frame " << frameID << " ya está ocupado.\n";
    } else {
        pageTable.setFrame(pageID, frameID);
        numPaginas++;
        std::cout << "Pagina " << pageID << " agregada al frame " << frameID << ".\n";
    }
}

void accederPagina(Replacer& replacer, PageTable& pageTable) {
    int frameID;
    std::cout << "Ingrese el ID del frame a acceder: ";
    std::cin >> frameID;

    // Verificar si el frameID está asociado a una página en la tabla de páginas
    bool found = false;
    for (const auto& [pageID, fID] : pageTable.pageMap) {
        if (fID == frameID) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "La pagina no existe.\n";
    } else {
        // Acceder a la página y actualizar la cola de reemplazo
        replacer.Algortimo(frameID);
        std::cout << "Pagina accedida y cola actualizada.\n";
    }
}

void simularReemplazo(PageTable& pageTable, Replacer& replacer, int& numPaginas) {
    int frameToReplace = replacer.BuscarFrame();
    if (frameToReplace != -1) {
        int oldPageID = -1;
        for (const auto& [pageID, frameID] : pageTable.pageMap) {
            if (frameID == frameToReplace) {
                oldPageID = pageID;
                break;
            }
        }
        if (oldPageID != -1) {
            pageTable.pageMap.erase(oldPageID);
            numPaginas--;
        }
        replacer.eliminarPag(frameToReplace);
        std::cout << "Ingrese el ID de la nueva pagina: ";
        int newPageID;
        std::cin >> newPageID;
        pageTable.setFrame(newPageID, frameToReplace);
        replacer.addCola(frameToReplace); // Añadimos el frame reemplazado a la cola
        numPaginas++;
        std::cout << "Pagina reemplazada.\n";
    } else {
        std::cout << "No hay paginas para reemplazar.\n";
    }
}

void mostrarTablaDePaginas(const PageTable& pageTable) {
    std::cout << "Frames en la tabla de paginas: " << std::endl;
    for (const auto& [pageID, frameID] : pageTable.pageMap) {
        std::cout << "Page ID: " << pageID << ", Frame ID: " << frameID << std::endl;
    }
}

void mostrarColaDeReemplazo(const Replacer& replacer) {
    std::cout << "Cola de reemplazo: ";
    for (const auto& frame : replacer.getCola()) {
        std::cout << frame << " ";
    }
    std::cout << std::endl;
}

int main() {
    PageTable pageTable;
    Replacer replacer;
    int opcion;
    int numPaginas = 0;
    int numFrames = 0;

    do {
        mostrarMenu(numPaginas, numFrames);
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarFrames(pageTable, replacer, numPaginas, numFrames);
                break;
            case 2:
                agregarPagina(pageTable, replacer, numPaginas);
                break;
            case 3:
                accederPagina(replacer, pageTable);
                break;
            case 4:
                simularReemplazo(pageTable, replacer, numPaginas);
                break;
            case 5:
                mostrarTablaDePaginas(pageTable);
                break;
            case 6:
                mostrarColaDeReemplazo(replacer);
                break;
            case 7:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion no valida, intente nuevamente.\n";
        }
    } while (opcion != 7);

    return 0;
}
