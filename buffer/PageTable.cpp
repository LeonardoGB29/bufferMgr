#include "PageTable.h"

int PageTable::getFrame(int pageID) {
    // Devuelve el Frame ID asociado con el Page ID dado, o -1 si no se encuentra.
    auto it = pageMap.find(pageID);
    if (it != pageMap.end()) {
        return it->second;
    }
    return -1;  //una forma de decir que no se ha encontrado un frame
}

void PageTable::setFrame(int pageID, int frameID) {
    // Asocia un Page ID con un Frame ID en la tabla de p�ginas.
    pageMap[pageID] = frameID;  // Establece o actualiza el mapeo
}

void PageTable::removePage(int pageID) {
    pageMap.erase(pageID);
}