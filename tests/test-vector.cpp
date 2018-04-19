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
    Vector<float> v = Vector<float>(1, 2);
    v.print();
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