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

    /**
     * Polígono CCW
     */
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)};
    Poligono<float> poly = Poligono<float>(plist, 5);

    // Se imprime polígono
    poly.print();

    // Chequea CCW
    assert(poly.checkCCW());

    /**
     * Polígono no CCw
     */
    Punto<float> plist2[] = {Punto<float>(0, 0), Punto<float>(0, 1), Punto<float>(1, 1)};
    poly = Poligono<float>(plist2, 3);

    // Se imprime polígono
    poly.print();

    // Chequea CCW
    assert(!poly.checkCCW());
}

/**
 * Testea el cálculo de áreas.
 */
void testArea() {
    // Cuadrado de lado 2
    Punto<float> plist[] = {Punto<float>(0, 0) * 2, Punto<float>(1, 0) * 2, Punto<float>(1, 1) * 2,
                            Punto<float>(0, 1) * 2};
    Poligono<float> poly = Poligono<float>(plist, 4);
    assert(poly.area() == 4.0f);

    // Triangulo
    // https://1.bp.blogspot.com/-AGt5tqYpDhk/UK5hSxmwbZI/AAAAAAAAEo8/khEwS7riKlI/s640/%C3%A1rea.jpg
    Punto<float> triangulo[] = {Punto<float>(-3, -1), Punto<float>(5, -4), Punto<float>(-2, 6)};
    poly = Poligono<float>(triangulo, 3);
    assert(poly.area() == 29.5f);
}

/**
 * Corre los test.
 * @return
 */
int main() {
    testCreacion();
    testCCW();
    testArea();
    return 0;
}