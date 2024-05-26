#include "Replacer.h"

int Replacer::findFrame() {
    // Encuentra un frame disponible para ser reutilizado.
    if (!queue.empty()) {
        int frameID = queue.front(); // Obtén el ID del frame desde el frente de la cola
        queue.pop_front();          // Retira el frame de la cola
        return frameID;             // Devuelve el ID del frame
    }
    return -1;  // Retorna -1 si no hay frames disponibles
}

void Replacer::removeFromQueue(int frameID) {
    // Elimina el frame de la cola
    queue.remove(frameID);
}

void Replacer::addToQueue(int frameID) {
    // Añade un frame al final de la cola de reemplazo.
    queue.push_back(frameID);  // Añade el frame ID al final de la cola
}