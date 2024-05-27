#pragma once
#include <list>

class Replacer {
private:
    std::list<int> cola;

public:
    void eliminarPag(int pageID);
    int BuscarFrame();
    void Algortimo(int frameID);
    void addCola(int frameID);
    void quitarDeCola(int frameID);
    const std::list<int>& getCola() const { return cola;}
};