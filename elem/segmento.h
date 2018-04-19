/**
 * Clase Segmento.
 * Elemento creado por dos puntos, con un determinado largo.
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Definición de constantes
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#ifndef T1_CC5502_1_SEGMENTO_H
#define T1_CC5502_1_SEGMENTO_H
#endif //T1_CC5502_1_SEGMENTO_H

#include "punto.h"

template<typename T>
class Segmento {
private:
    Punto<T> p1, p2;
public:

    // Constructor, recibe dos puntos
    Segmento(Punto<T> p1, Punto<T> p2);

    // Destructor
    ~Segmento();
};

#pragma clang diagnostic pop