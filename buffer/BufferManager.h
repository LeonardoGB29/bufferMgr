#pragma once
#include "BufferPool.h"
#include "PageTable.h"
#include "Replacer.h"
#include <string>

class BufferManager {
private:
    BufferPool bufferPool;
    PageTable pageTable;
    Replacer replacer;

public:
    BufferManager(int size);
    void setPage(int pageID);
    Frame& requestPage(int pageID);
    void releasePage(int pageID);
    bool checkPage(int pageID);
    void printPageTable();
};