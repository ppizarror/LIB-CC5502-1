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

    // Chequea CCW
    assert(poly.inCCW());

    /**
     * Polígono no CCw
     */
    Punto<float> plist2[] = {Punto<float>(0, 0), Punto<float>(0, 1), Punto<float>(1, 1)};
    poly = Poligono<float>(plist2, 3);

    // Chequea CCW
    assert(!poly.inCCW());
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
 * Chequea contención de puntos.
 */
void testInPoly() {

    /**
     * Cuadrado de lado 1.
     */
    Punto<float> plist[] = {Punto<float>(0, 0), Punto<float>(1, 0), Punto<float>(1, 1),
                            Punto<float>(0, 1)};
    Poligono<float> poly = Poligono<float>(plist, 4);

    // Creación de varios puntos
    Punto<float> p;

    // Deben estar dentro
    p = Punto<float>(0.5, 0.5);
    assert(poly.inPoly(p));
    p = Punto<float>(0.2, 0.5);
    assert(poly.inPoly(p));

    // Deben estar fuera
    p = Punto<float>(0, 1.1);
    assert(!poly.inPoly(p));
    p = Punto<float>(1.1, 0);
    assert(!poly.inPoly(p));

    /**
     * Polígono más complicado.
     */
    //         (0.5,0.5)
    //            p4
    //           /  \
    //          /    \           Poligono místico
    //         /  p2  \             > DRINCC PEPSI OR BEPBIS?
    //        /  /  \  \            > BEPES,BOPIS,BEPPS,BEPIS
    //       / /      \ \        p2: (0.5,0.25)
    //      //          \\
    //     p1            p3
    // (0.0,0.0)      (1.0,0.0)
    Punto<float> plist2[] = {Punto<float>(0.0, 0.0), Punto<float>(0.5, 0.25), Punto<float>(1.0, 0.0),
                             Punto<float>(0.5, 0.5)};
    poly = Poligono<float>(plist2, 4);

    // Área
    assert(poly.area() == 0.125f);

    // Deben estar fuera
    p = Punto<float>(0.5, 0.24);
    assert(!poly.inPoly(p));
    p = Punto<float>(0.4, 0.2);
    assert(!poly.inPoly(p));

    // Deben estar dentro
    p = Punto<float>(0.5, 0.26);
    assert(poly.inPoly(p));
    p = Punto<float>(0.1, 0.1);
    assert(poly.inPoly(p));
}

/**
 * Corre los test.
 * @return
 */
int main() {
    std::cout << "Testeando poligono" << std::endl;

    // Carga los tests
    testCreacion();
    testCCW();
    testArea();
    testInPoly();

    // Retorna
    return 0;
}