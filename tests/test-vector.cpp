/**
 * Testea vectores.
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../elem/vector.h"

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
    Vector<float> v1 = Vector<float>(3, 2);
    Vector<float> v2 = Vector<float>(2, -1);
    Vector<float> v3 = v1.dot(v2);
    assert(v3.getI() == 6.0f && v3.getJ() == -2.0f); // (3,2).(2,-1)=(6,-2)

    // Prueba cambiando a ceros
    v3.setI(0);
    v3.setJ(0);
    v1 = v1.dot(v3);
    assert(v1.getI() == 0.0f && v1.getJ() == 0.0f); // (3,2).(0,0)=(0,0)
}

/**
 * Testea producto cruz vectores.
 */
void testCross() {
    Vector<float> v1 = Vector<float>(3, 2);
    Vector<float> v2 = Vector<float>(2, -1);
    Vector<float> v3 = v1.cross(v2);
    assert(v3.getI() == 0.0f && v3.getJ() == 0.0f && v3.getK() == -7.0f); // (3,2,0)x(2,-1,0)=(0,0,-7)

    // Prueba vectores en 3d
    v1 = Vector<float>(2, 0, 1);
    v2 = Vector<float>(1, -1, 3);
    v3 = v1.cross(v2);
    assert(v3.getI() == 1.0f && v3.getJ() == -5.0f && v3.getK() == -2.0f);
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