#include "Frame.h"

Frame::Frame() : pageID(-1), isPinned(false), dirtyFlag(false), pinCount(0), lastUsed(0) {
    // Constructor que inicializa un frame con valores por defecto.
}

void Frame::pin() {
    // Marca el frame como "pin", indicando que está en uso.
    isPinned = true;
    pinCount++;  // Incrementa el contador de pin para este frame
}

void Frame::unpin() {
    if (pinCount > 0) {
        pinCount--;  // Decrementar el contador de pines
        if (pinCount == 0) {
            isPinned = false;  // Si no hay más pines, marcar como no "pinned"
        }
    }
}

void Frame::setDirty(bool flag) {
    // Establece la bandera de suciedad para el frame.
    dirtyFlag = flag;  // Establece la bandera a true o false según el flag proporcionado
}

void Frame::reset() {
    pageID = -1;
    isPinned = false;
    dirtyFlag = false;
    pinCount = 0;
    lastUsed = 0;  // Restablece el tiempo de último uso
}
