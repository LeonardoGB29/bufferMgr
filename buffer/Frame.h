#pragma once
#include <vector>
#include <string>

class Frame {
public:
    int pageID;
    bool isPinned;
    bool dirtyFlag;
    int pinCount;
    int lastUsed;
    std::vector<std::vector<std::string>> content;

    Frame();
    void pin();
    void unpin();
    void setDirty(bool flag);
    void reset();
};