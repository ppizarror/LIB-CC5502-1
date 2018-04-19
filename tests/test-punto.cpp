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
    // Crea punto inicial
    Punto<int> p1 = Punto<int>(420, 69);

    // Comprueba que se hayan definido bien los objetos
    assert(p1.getCoordX() == 420);
    assert(p1.getCoordY() != 0);

    // Comprueba sumas
    Punto<int> p2 = Punto<int>(0, -69);
    Punto<int> p3 = p1 + p2;
    assert(p3.getCoordX() == 420 && p3.getCoordY() == 0);

    // Comprueba suma a sí mismo. (0, -69) + (420, 0) = (420, -69)
    p2 += p3;
    assert(p2.getCoordX() == 420 && p2.getCoordY() == -69);

    // Restas
    p2 = -p2;
    assert(p2.getCoordX() == -420 && p2.getCoordY() == 69);
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