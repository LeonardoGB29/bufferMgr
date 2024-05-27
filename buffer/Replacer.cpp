#include "Replacer.h"
 
 void Replacer::eliminarPag(int IDpagina){
    cola.remove(IDpagina);
 }

 int Replacer::BuscarFrame() {
    if (!cola.empty()) {
        return cola.back(); // Devuelve el último frame en la cola
    }
    return -1; // Si la cola está vacía, devuelve un valor no válido
}


 void Replacer::Algortimo(int IDframe){
    cola.remove(IDframe);
    cola.push_front(IDframe);
 }

 void Replacer::addCola(int IDframe){
    cola.push_front(IDframe);
 }

 void Replacer::quitarDeCola(int IDframe){
    cola.remove(IDframe);
 }
 