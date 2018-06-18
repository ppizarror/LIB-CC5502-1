/**
 * Funciones utilitarias de cerradura convexa
 *
 * @author Pablo Pizarro
 * @date 18/06/18
 */

// Importación de librerías
#include "../elem/poligono.h"

// Constantes
#ifndef LIB_CC5502_1_CERRADURA_CONVEXA_H
#define LIB_CC5502_1_CERRADURA_CONVEXA_H

template<class T>
/**
 * Algoritmo de Gift Wrapping
 * @tparam T - Tipo de datos
 * @param cloud - Nube de puntos a realizar la cerradura convexa
 * @return Polínono con puntos que representa la cerradura convexa
 */
Poligono<T> giftWrapping(Punto<T> *cloud) {
    cloud[0].print();
}

#endif //LIB_CC5502_1_CERRADURA_CONVEXA_H