#include "BufferPool.h"

BufferPool::BufferPool(int size) : frames(size) {
    // Inicializa el buffer pool con un tama�o fijo y el contador de �ltimo uso a 0.
}

void BufferPool::setPage(int pageID, int frameID) {
    if (frameID < frames.size()) {
        frames[frameID].pageID = pageID;
        frames[frameID].dirtyFlag = false;  // Reinicia el flag de dirty
        updateLastUsed(frameID);  // Actualiza el contador de �ltimo uso
    }
}

Frame& BufferPool::getFrame(int frameID) {
    updateLastUsed(frameID);  // Actualiza cada vez que se accede a un frame
    return frames[frameID];
}

void BufferPool::releaseFrame(int frameID) {
    frames[frameID] = Frame();
}

int BufferPool::size() {
    return frames.size();
}

int BufferPool::getLeastRecentlyUsed() {
    int lruIndex = -1;
    int minLastUsed = -1;  // usamos -1 para identificar que a�n no hemos encontrado un frame v�lido.

    for (int i = 0; i < frames.size(); ++i) {
        if (frames[i].pinCount == 0) {  // consideramos solo frames que no est�n 'pinned'.
            if (minLastUsed == -1 || frames[i].lastUsed < minLastUsed) {  // actualizamos el m�nimo si es el primero encontrado o si encontramos uno m�s antiguo.
                minLastUsed = frames[i].lastUsed;
                lruIndex = i;
            }
        }
        // else cout no hay espacio disponible en este momento, break
    }

    return lruIndex;  // devuelve el �ndice del frame menos recientemente usado que puede ser reemplazado.
}

void BufferPool::updateLastUsed(int frameID) {
    if (frameID < frames.size()) { // comprobacion en el rango
        frames[frameID].lastUsed++;
    }
}

int BufferPool::getLastUsedCounter() { // falta comprobar que sea 0 isPinned tmbn
    int minLastUsed = frames[0].lastUsed;
    for (int i = 1; i < frames.size(); ++i) { 
        if (frames[i].lastUsed < minLastUsed) {
            minLastUsed = frames[i].lastUsed; 
        }
    }
    return minLastUsed; 
}