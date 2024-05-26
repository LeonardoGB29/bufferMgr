#pragma once
#include <vector>
#include "Frame.h"

class BufferPool {
private:
    std::vector<Frame> frames;
    //int lastUsedCounter;  // Contador para el seguimiento de último uso de los frames

public:
    BufferPool(int size);
    void setPage(int pageID, int frameID);
    Frame& getFrame(int frameID);
    void releaseFrame(int frameID);
    int size();
    int getLeastRecentlyUsed();
    void updateLastUsed(int frameID);
    int getLastUsedCounter();  // Devuelve el contador de último uso
};
