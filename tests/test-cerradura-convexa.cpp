/**
 * Tests de cerradura convexa
 *
 * @author Pablo Pizarro
 * @date 18/06/18
 */

// Importación de librerías
#include <iostream>
#include <cassert>
#include "../utils/cerradura-convexa.h"
#include <vector>
#include <random>

/**
 * Genera un número aleatorio entre dos valores flotantes
 * @param a Número menor
 * @param b Número mayor
 * @return
 */
float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX; // NOLINT
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/**
 * Testeo básico, genera figuras simples de pocos puntos.
 */
void testBasico() {
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)}; // 5

    // [GiftWrapping]
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(plist, 5);
    assert(cerraduraGW.second == 5);

    // [Graham scan]
    std::pair<Poligono<float>, int> cerraduraGS = grahamScan(plist, 5);
    assert(cerraduraGS.second == 5);
}

/**
 * Testeo triangulo con puntos en hipotenusa
 */
void testTriangulo() {
    Punto<int> triangulo[] = {Punto<int>(0, 0), Punto<int>(-1, -1), Punto<int>(2, 2), Punto<int>(3, 3),
                              Punto<int>(4, 4),
                              Punto<int>(5, 5), Punto<int>(0, 0), Punto<int>(5, 0)}; // 8

    // [GiftWrapping]
    std::pair<Poligono<int>, int> cerraduraGW = giftWrapping(triangulo, 8);
    assert(cerraduraGW.second == 3);

    // [Graham scan]
    std::pair<Poligono<int>, int> cerraduraGS = grahamScan(triangulo, 8);
    assert(cerraduraGS.second == 3);
}

/**
 * Testeo duplicados
 */
void testDuplicados() {
    Punto<int> plist[] = {Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(1, 1), Punto<int>(1, 0),
                          Punto<int>(1, 0)}; // 6

    // [GiftWrapping]
    std::pair<Poligono<int>, int> cerraduraGW = giftWrapping(plist, 6);
    assert(cerraduraGW.second == 3);

    // [Graham scan]
    std::pair<Poligono<int>, int> cerraduraGS = grahamScan(plist, 6);
    assert(cerraduraGS.second == 3);
}

/**
 * Genera un cuadrado de 1x1 en flotante con 10 puntos dentro,
 * la cerradura debe ser (0,0),(0,1),(1,1),(1,0)
 */
void testCuadradoChico() {
    Punto<float> *cuadrado = new Punto<float>[10]; // NOLINT

    // Añade los puntos
    for (int i = 0; i < 10; i++) {
        cuadrado[i] = Punto<float>(randomFloat(0, 1), randomFloat(0, 1));
    }
    cuadrado[2] = Punto<float>(0, 0);
    cuadrado[5] = Punto<float>(0, 1);
    cuadrado[7] = Punto<float>(1, 1);
    cuadrado[8] = Punto<float>(1, 0);

    std::cout << "\n[GiftWrapping] Cerradura cuadrado perfecto 1x1 con 10 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(cuadrado, 10);
    cerraduraGW.first.print();
    assert(cerraduraGW.second == 4);

    std::cout << "\n[Graham Scan] Cerradura cuadrado perfecto 1x1 con 10 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGS = grahamScan(cuadrado, 10);
    cerraduraGS.first.print();
    // assert(cerraduraGS.second == 4);
}

/**
 * Genera un cuadrado de 1x1 en flotante con 1000 puntos dentro,
 * la cerradura debe ser (0,0),(0,1),(1,1),(1,0)
 */
void testCuadradoMediano() {
    Punto<float> *cuadrado = new Punto<float>[1000]; // NOLINT

    // Añade los puntos
    for (int i = 0; i < 1000; i++) {
        cuadrado[i] = Punto<float>(randomFloat(0, 1), randomFloat(0, 1));
    }
    cuadrado[100] = Punto<float>(0, 0);
    cuadrado[200] = Punto<float>(0, 1);
    cuadrado[300] = Punto<float>(1, 1);
    cuadrado[400] = Punto<float>(1, 0);

    std::cout << "\n[GiftWrapping] Cerradura cuadrado perfecto 1x1 con 1000 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(cuadrado, 1000);
    cerraduraGW.first.print();
    assert(cerraduraGW.second == 4);

    std::cout << "\n[Graham Scan] Cerradura cuadrado perfecto 1x1 con 1000 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGS = grahamScan(cuadrado, 1000);
    cerraduraGS.first.print();
    // assert(cerraduraGS.second == 4);
}

/**
 * Genera un rectángulo de 10000 puntos completamente aleatorio, altura 1 y ancho 10.
 */
void testRectangulo() {
    Punto<float> *rectangulo = new Punto<float>[10000]; // NOLINT

    // Añade los puntos
    for (int i = 0; i < 10000; i++) {
        rectangulo[i] = Punto<float>(randomFloat(0, 10), randomFloat(0, 1));
    }
    rectangulo[1000] = Punto<float>(0, 0);
    rectangulo[2000] = Punto<float>(10, 0);
    rectangulo[3000] = Punto<float>(0, 1);
    rectangulo[4000] = Punto<float>(10, 1);

    // Calcula la cerradura
    std::cout << "\n[GiftWrapping] Cerradura rectangulo 10x1 con 10000 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(rectangulo, 10000);
    cerraduraGW.first.print();
    assert(cerraduraGW.second == 4);

    // Calcula la cerradura
    std::cout << "\n[Graham Scan] Cerradura rectangulo 10x1 con 10000 puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGS = giftWrapping(rectangulo, 10000);
    cerraduraGS.first.print();
    assert(cerraduraGS.second == 4);
}

/**
 * Testea una figura sin anclajes predefinidos.
 */
void testFiguraDeforme(int n) {
    Punto<float> *figura = new Punto<float>[n]; // NOLINT

    // Añade los puntos
    for (int i = 0; i < n; i++) {
        figura[i] = Punto<float>(randomFloat(0, 1), randomFloat(0, 1));
    }

    // Calcula la cerradura
    std::cout << "\n[GiftWrapping] Cerradura figura deforme 10x1 con " << n << " puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(figura, n);

    // Vuelve a ejecutar GiftWrapping para comprobar errores en el cambio de los datos
    std::cout << "\n[GiftWrapping]x2 Cerradura figura deforme 10x1 con " << n << " puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGW2 = giftWrapping(figura, n);

    // Calcula cerradura con Graham Scan
    std::cout << "\n[GrahamScan] Cerradura figura deforme 10x1 con " << n << " puntos" << std::endl;
    std::pair<Poligono<float>, int> cerraduraGS = grahamScan(figura, n);

    // Verifica que ambos polígonos tengan iguales puntos
    assert(cerraduraGW2.first.mismosPuntos(cerraduraGS.first));
}

/**
* Corre los test.
*/
int main() {
    std::cout << "Testeando cerradura convexa" << std::endl;

    // Carga los tests
    testBasico();
    testDuplicados();
    testTriangulo();
    testCuadradoChico();
    testCuadradoMediano();
    testRectangulo();
    testFiguraDeforme(static_cast<int>(1e4));

    // Retorna
    return 0;
}