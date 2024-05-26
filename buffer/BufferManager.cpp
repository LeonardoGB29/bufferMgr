#include "BufferManager.h"
#include <iostream>
#include <cassert>

BufferManager::BufferManager(int size) : bufferPool(size), pageTable(), LRU() {
    // Inicializa el buffer pool con un tama�o determinado.
}

Frame& BufferManager::requestPage(int pageID) {
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {  // La p�gina ya est� en el buffer
        Frame& frame = bufferPool.getFrame(frameID);
        frame.pin();  // Incrementa el pinCount ya que la p�gina est� siendo accedida
        return frame;
    }
    else {  // La p�gina no est� en el buffer
        frameID = bufferPool.getLeastRecentlyUsed();  // Encuentra un frame LRU disponible
        if (frameID == -1) {
            throw std::runtime_error("No hay frames disponibles para reemplazo.");
        }
        Frame& oldFrame = bufferPool.getFrame(frameID);
        if (oldFrame.dirtyFlag) {
            // Simula escribir en el disco si dirty
            std::cout << "Escribiendo p�gina " << oldFrame.pageID << " al disco.\n";
        }
        // Limpia el frame y carga la nueva p�gina
        bufferPool.setPage(pageID, frameID);  // Asigna la p�gina al frame en el buffer
        pageTable.setFrame(pageID, frameID);  // Registra la p�gina en la tabla de p�ginas
        oldFrame.reset();  // Restablece el frame (simula la carga desde el disco)
        oldFrame.pin();  // Inicializa el pinCount a 1
        return oldFrame;
    }
}


void BufferManager::releasePage(int pageID) {
    // Libera una p�gina espec�fica.
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {
        bufferPool.releaseFrame(frameID);  // Libera el frame del buffer pool
        pageTable.setFrame(pageID, -1);  // Elimina la p�gina de la tabla de p�ginas
        LRU.addToQueue(frameID);  // A�ade el frame a la cola de LRU
    }
}

void BufferManager::pinPage(int pageID) {
    // Marca el frame como "pin".
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {
        bufferPool.getFrame(frameID).pin();  // Marca el frame como "pin"
    }
}

void BufferManager::unpinPage(int pageID) {
    // Desmarca el frame como "pin".
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {
        Frame& frame = bufferPool.getFrame(frameID);
        frame.unpin();  // Desmarca el frame
        if (frame.pinCount == 0) {
            LRU.addToQueue(frameID);
        }
    }
}

void BufferManager::checkSpace() {
    // Verifica si hay espacio suficiente en el buffer pool.
    if (bufferPool.size() == bufferPool.getLeastRecentlyUsed()) {
        std::cerr << "No hay espacio disponible en el buffer" << std::endl;
    }
}

void BufferManager::setPageInBufferPool(int pageID, int frameID) {
    // Establece una p�gina en el buffer pool asignando un pageID a un frameID.
    bufferPool.setPage(pageID, frameID);
    pageTable.setFrame(pageID, frameID);
    bufferPool.getFrame(frameID).lastUsed = bufferPool.getLastUsedCounter();  // Actualiza el contador de �ltimo uso
}

Frame& BufferManager::getFrameFromBufferPool(int frameID) {
    // Obtiene un frame espec�fico del buffer pool.
    return bufferPool.getFrame(frameID);
}

int BufferManager::getBufferSize() {
    // Devuelve el tama�o actual del buffer pool.
    return bufferPool.size();
}

void BufferManager::logAccess(int frameID, std::string operation) {
    // Registra el acceso a un frame espec�fico.
    std::cout << "Acceso a Frame ID: " << frameID << " Operaci�n: " << operation << std::endl;
    bufferPool.updateLastUsed(frameID);  // Actualiza el contador de �ltimo uso
}

void BufferManager::printPageTable() {
    // Imprime la tabla de p�ginas en un formato espec�fico.
    std::cout << "Frame ID - Page ID - Dirty Bit - Pin Count - Last Used\n";
    for (auto const& entry : pageTable.pageMap) {
        Frame& frame = bufferPool.getFrame(entry.second);
        std::cout << entry.second << " " << entry.first << " " << frame.dirtyFlag << " "
            << frame.pinCount << " " << frame.lastUsed << "\n";
    }
}