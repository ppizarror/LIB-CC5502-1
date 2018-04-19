/**
 * Testea puntos
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../punto.h"

/**
 * Testea la creación de un punto entero.
 */
void testIntCreation() {
    Punto<int> p = Punto<int>(420, 69);

    // Comprueba que se hayan definido bien los objetos
    assert(p.getCoordX() == 420);
    assert(p.getCoordY() != 0);
}

/**
 * Testea punto en flotante.
 */
void testFloatCreation() {
    Punto<float> *p1, *p2;

    // Inicia los puntos
    p1 = new Punto<float>(4.20, 2.10);
    p2 = new Punto<float>(4.20, 2.10);

    // Comprobación a lo bruto sumas y restas
    assert(p1->getCoordY() + p2->getCoordY() == 4.20f);
}

/**
 * Corre los test
 * @return
 */
int main() {
    testIntCreation();
    testFloatCreation();
    return 0;
}