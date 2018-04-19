/**
 * Testea puntos
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../elem/poligono.h"

/**
 * Testea la creación de un polígono.
 */
void testCreacion() {
    Poligono<double> poly = Poligono<double>();
    poly.addPoint(Punto<double>(1, 2));
    poly.addPoint(Punto<double>(3, 4));
    poly.addPoint(Punto<double>(5, 6));

    // Imprime el polígono
    std::cout << poly.toString() << std::endl;
}

/**
 * Testea la implementación de CCW.
 */
void testCCW() {

}

/**
 * Corre los test.
 * @return
 */
int main() {
    testCreacion();
    testCCW();
    return 0;
}