#pragma once
#include <map>

class PageTable {
public:
    std::map<int, int> pageMap;
    int getFrame(int pageID);
    void setFrame(int pageID, int frameID);
    void removePage(int pageID);
};