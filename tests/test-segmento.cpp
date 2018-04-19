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

    // (0,10)      (10,10)      Un triángulo
    //   p5          p2             p1-p2   Segmento
    //              / .             p3      A la derecha
    //       (5,5) /  .             p4      Sobre el segmento
    //            p4  .             p5      A la izquierda del segmento
    //           /    .
    //         p1  .. p3
    //       (0,0)  (10,0)
    Punto<float> p1 = Punto<float>(0, 0);
    Punto<float> p2 = Punto<float>(3, 4);

    // Crea el segmento
    Segmento<float> s = Segmento<float>(p1, p2);
    assert(s.getLength() == 5.0f); // Debe ser 5
}

/**
 * Testea las ubicaciones punto/segmento.
 */
void testIntersection() {

    // (0,10)      (10,10)      Un triángulo
    //   p5          p2             p1-p2   Segmento
    //              / .             p3      A la derecha
    //       (5,5) /  .             p4      Sobre el segmento
    //            p4  .             p5      A la izquierda del segmento
    //           /    .
    //         p1  .. p3
    //       (0,0)  (10,0)
    Punto<float> p1 = Punto<float>(0, 0);
    Punto<float> p2 = Punto<float>(10, 10);
    Segmento<float> s = Segmento<float>(p1, p2);

}

/**
 * Corre los test.
 * @return
 */
int main() {
    testLength();
    testIntersection();
    return 0;
}