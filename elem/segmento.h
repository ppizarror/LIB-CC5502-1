/**
 * Clase Segmento.
 * Elemento creado por dos puntos, con un determinado largo.
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Definición de constantes
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#ifndef T1_CC5502_1_SEGMENTO_H
#define T1_CC5502_1_SEGMENTO_H
#endif //T1_CC5502_1_SEGMENTO_H

// Importación de librerías
#include "punto.h"

template<class T>
class Segmento {
private:
    Punto<T> *p1;
    Punto<T> *p2;
public:
    // Constructor, recibe dos puntos
    Segmento(Punto<T> &p1, Punto<T> &p2);

    // Retorna el tamaño del segmento
    T getLength() const;
};

template<class T>
/**
 * Constructor
 * @tparam T
 * @param p1 Punto 1
 * @param p2 Punto 2
 */
Segmento<T>::Segmento(Punto<T> &p1, Punto<T> &p2) {
    this->p1 = &p1;
    this->p2 = &p2;
}

template<class T>
/**
 * Retorna el largo del segmento.
 * @tparam T Template
 * @return
 */
T Segmento<T>::getLength() const {
    return this->p1->dist(*this->p2);
}

#pragma clang diagnostic pop