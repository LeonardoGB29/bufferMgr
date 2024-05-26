#include "BufferPool.h"

BufferPool::BufferPool(int size) : frames(size), lastUsedCounter(0) {
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
    int minLastUsed = -1;  // Usamos -1 para identificar que a�n no hemos encontrado un frame v�lido.

    for (int i = 0; i < frames.size(); ++i) {
        if (frames[i].pinCount == 0) {  // Consideramos solo frames que no est�n 'pinned'.
            if (minLastUsed == -1 || frames[i].lastUsed < minLastUsed) {  // Actualizamos el m�nimo si es el primero encontrado o si encontramos uno m�s antiguo.
                minLastUsed = frames[i].lastUsed;
                lruIndex = i;
            }
        }
    }

    return lruIndex;  // Devuelve el �ndice del frame menos recientemente usado que puede ser reemplazado.
}

void BufferPool::updateLastUsed(int frameID) {
    if (frameID < frames.size()) {
        frames[frameID].lastUsed = ++lastUsedCounter;
    }
}

int BufferPool::getLastUsedCounter() {
    // Devuelve el contador de �ltimo uso.
    return lastUsedCounter;
}
