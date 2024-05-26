#include "Replacer.h"

int Replacer::findFrame() {
    if (!lruQueue.empty()) {
        int frameID = lruQueue.front();  // Obtén el frame menos recientemente usado
        lruQueue.pop_front();            // Retira el frame de la cola
        return frameID;
    }
    return -1;  // Si la lista está vacía, indica que no hay frames disponibles
}

void Replacer::updateLRU(int frameID) {
    // Elimina el frame si ya está en la cola y lo añade al final para marcarlo como el más recientemente usado
    removeFromQueue(frameID);
    addToQueue(frameID);
}

void Replacer::addToQueue(int frameID) {
    lruQueue.push_back(frameID);  // Añade el frame ID al final de la lista
}

void Replacer::removeFromQueue(int frameID) {
    lruQueue.remove(frameID);  // Elimina todas las instancias del frame ID de la lista
}
