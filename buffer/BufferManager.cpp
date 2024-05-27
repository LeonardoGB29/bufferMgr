#include "BufferManager.h"
#include <iostream>
#include <cassert>
#include "BufferManager.h"

BufferManager::BufferManager(int size) : bufferPool(size), replacer(), pageTable() {
    // Añade todos los frames al Replacer inicialmente
    for (int i = 0; i < size; i++) {
        replacer.addToQueue(i);
    }
}

void BufferManager::setPage(int pageID) {
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {
        std::cout << "Page already in memory.\n";
        return;
    }
    frameID = replacer.findFrame();
    if (frameID == -1) {
        std::cout << "No available frames.\n";
        return;
    }
    if (bufferPool.getFrame(frameID).dirtyFlag) {
        // Asegúrate de manejar la escritura en disco antes de sobreescribir
        std::cout << "Writing old page " << bufferPool.getFrame(frameID).pageID << " to disk.\n";
    }
    bufferPool.getFrame(frameID).reset();
    bufferPool.setPage(pageID, frameID);
    pageTable.setFrame(pageID, frameID);
    bufferPool.getFrame(frameID).pin();
    std::cout << "Page " << pageID << " loaded into frame " << frameID << ".\n";
}

Frame& BufferManager::requestPage(int pageID) {
    int frameID = pageTable.getFrame(pageID); // devuelve -1 si no lo encuentra
    //std::cout << "frameID " << frameID << ".\n";
    if (frameID == -1) {
        setPage(pageID); // si no esta en memoria, lo carga
        frameID = pageTable.getFrame(pageID);
    }
    Frame& frame = bufferPool.getFrame(frameID);
    frame.pin();
    return frame;
}

void BufferManager::releasePage(int pageID) {
    int frameID = pageTable.getFrame(pageID);
    if (frameID != -1) {
        Frame& frame = bufferPool.getFrame(frameID);
        frame.unpin();
        if (frame.pinCount == 0) {
            replacer.addToQueue(frameID); // Si no está "pinned", se añade para posible reemplazo.
        }
    }
}

bool BufferManager::checkPage(int pageID) {
    return pageTable.getFrame(pageID) != -1;
}

void BufferManager::printPageTable() {
    std::cout << "# Frame ID\t- Page ID\t- Dirty Bit\t- Pin Count\t- Last Used\n";
    for (auto& entry : pageTable.pageMap) {
        Frame& frame = bufferPool.getFrame(entry.second);
        std::cout <<"# "<< entry.second << "\t\t- " << entry.first << "\t\t- "
            << (frame.dirtyFlag ? "1" : "0") << "\t\t- "
            << frame.pinCount << "\t\t- " << frame.lastUsed << "\t\t\n";
    }
}