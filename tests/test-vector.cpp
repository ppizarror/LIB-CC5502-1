/**
 * Testea vectores.
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../vector.h"

/**
 * Testea normalizado de vectores.
 */
void testNormalize() {
    Vector<int> v = Vector<int>(1, 2);
    v.normalize();
    assert(v.getI() == 0 && v.getJ() == 1); // 0.5 -> 0 y 1.0 -> 1

    Vector<double> v2 = Vector<double>(1, 2);
    v2.normalize();
    assert(v2.getI() == 0.50f && v2.getJ() == 1.0f); // 0.5->0.5 y 1.0->1.0
}

/**
 * Testea producto punto entre vectores.
 */
void testDot() {

}

/**
 * Testea producto cruz vectores.
 */
void testCross() {

}

/**
 * Corre los test.
 * @return
 */
int main() {
    testCross();
    testDot();
    testNormalize();
    return 0;
}