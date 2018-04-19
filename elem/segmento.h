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
#include "vector.h"

template<class T>
class Segmento {
private:
    Punto<T> *a;
    Punto<T> *b;

    // Calcula el área entre el segmento y un punto externo
    T area2(Punto<T> &c);

public:
    // Constructor, recibe dos puntos
    Segmento(Punto<T> &p1, Punto<T> &p2);

    // Retorna el tamaño del segmento
    T getLength() const;

    // Indica si un punto está estrictamente a la izquierda del segmento
    bool left(Punto<T> &p);

    // Indica si un punto está estrictamente a la derecha del segmento
    bool right(Punto<T> &p);

    // Indica que un punto está encima del segmento
    bool on(Punto<T> &p);

    // Indica si un punto está a la izquierda o sobre el segmento
    bool leftOn(Punto<T> &p);

    // Indica si un punto está a la izquierda o sobre el segmento
    bool rightOn(Punto<T> &p);
};

template<class T>
/**
 * Constructor
 * @tparam T
 * @param p1 Punto 1
 * @param p2 Punto 2
 */
Segmento<T>::Segmento(Punto<T> &p1, Punto<T> &p2) {
    this->a = &p1;
    this->b = &p2;
}

template<class T>
/**
 * Retorna el largo del segmento.
 * @tparam T Template
 * @return
 */
T Segmento<T>::getLength() const {
    return this->a->dist(*this->b);
}

template<class T>
/**
 * Retorna el área con otro punto.
 * @tparam T Template
 * @param c Punto a calcular área
 * @return
 */
T Segmento<T>::area2(Punto<T> &c) {
    T area = (this->b->getCoordX() - this->a->getCoordX()) * (c.getCoordY() - this->a->getCoordY()) -
             (this->b->getCoordY() - this->a->getCoordY()) * (c.getCoordX() - this->a->getCoordX());
    return 0.5 * area;
}

template<class T>
/**
 * Indica si un punto está estrictamente a la izquierda del segmento
 * @tparam T Template
 * @param p Punto
 * @return
 */
bool Segmento<T>::left(Punto<T> &p) {
    return this->area2(p) > 0.0f;
}

template<class T>
/**
 * Indica si un punto está estrictamente a la derecha del segmento
 * @tparam T Template
 * @param p Punto
 * @return
 */
bool Segmento<T>::right(Punto<T> &p) {
    return this->area2(p) < 0.0f;
}

template<class T>
/**
 * Indica si un punto está encima del segmento
 * @tparam T Template
 * @param p Punto
 * @return
 */
bool Segmento<T>::on(Punto<T> &p) {
    return this->area2(p) == 0.0f;
}

template<class T>
/**
 * Indica si un punto está encima o a la izquierda del segmento
 * @tparam T Template
 * @param p Punto
 * @return
 */
bool Segmento<T>::leftOn(Punto<T> &p) {
    return this->area2(p) >= 0.0f;
}

template<class T>
/**
 * Indica si un punto está encima o a la derecha del segmento
 * @tparam T Template
 * @param p Punto
 * @return
 */
bool Segmento<T>::rightOn(Punto<T> &p) {
    return this->area2(p) <= 0.0f;
}

#pragma clang diagnostic pop