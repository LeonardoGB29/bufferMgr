#pragma once
#include <list>

class Replacer {
private:
    std::list<int> queue;

public:
    void removePage(int pageID);
    int findFrame();
    void updateLRU(int frameID);
    void addToQueue(int frameID);
    void removeFromQueue(int frameID);
};