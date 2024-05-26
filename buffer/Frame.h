#pragma once

class Frame {
public:
    int pageID;
    bool isPinned;
    bool dirtyFlag;
    int pinCount;
    int lastUsed;

    Frame();
    void pin();
    void unpin();
    void setDirty(bool flag);
    void reset();
};