/**
 * Clase Polígono.
 * @author Pablo Pizarro
 * @date 19/04/2018
 */

// Constantes
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#ifndef T1_CC5502_1_POLIGONO_H
#define T1_CC5502_1_POLIGONO_H
#endif //T1_CC5502_1_POLIGONO_H

// Importación de librerías
#include "segmento.h"
#include <list>

template<class T>
class Poligono {
private:
    std::list<Punto<T>> puntos;
public:
    // Constructor
    Poligono();

    // Destructor
    ~Poligono();

    // Agrega un punto
    void addPoint(const Punto<T> &p);
};

template<class T>
/**
 * Destructor.
 * @tparam T
 */
Poligono<T>::~Poligono() {
    puntos.clear();
}

template<class T>
/**
 * Constructor
 * @tparam T
 */
Poligono<T>::Poligono() {
}

template<class T>
void Poligono<T>::addPoint(const Punto<T> &p) {
    this->puntos.push_back(p);
}

#pragma clang diagnostic pop