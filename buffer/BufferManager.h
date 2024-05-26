#pragma once
#include "BufferPool.h"
#include "PageTable.h"
#include "Replacer.h"
#include <string>

class BufferManager {
private:
    BufferPool bufferPool;
    PageTable pageTable;
    Replacer LRU;

public:
    BufferManager(int size);
    Frame& requestPage(int pageID);
    void releasePage(int pageID);
    void pinPage(int pageID);
    void unpinPage(int pageID);
    void checkSpace();
    void setPageInBufferPool(int pageID, int frameID);
    Frame& getFrameFromBufferPool(int frameID);
    int getBufferSize();
    void logAccess(int frameID, std::string operation);
    void printPageTable();
};