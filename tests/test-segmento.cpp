/**
 * Testea vectores.
 * @author Pablo Pizarro
 * @date 19/04/2018
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../elem/segmento.h"

/**
 * Testea el largo de un segmento.
 */
void testLength() {
    Punto<float> p1 = Punto<float>(0, 0);
    Punto<float> p2 = Punto<float>(3, 4);

    // Crea el segmento
    Segmento<float> s = Segmento<float>(p1, p2);
    assert(s.getLength() == 5.0f); // Debe ser 5
}

/**
 * Corre los test.
 * @return
 */
int main() {
    testLength();
    return 0;
}