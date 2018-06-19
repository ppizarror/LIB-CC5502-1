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
 * Genera un cuadrado de 1x1 en flotante con 1000 puntos dentro,
 * la cerradura debe ser (0,0),(0,1),(1,1),(1,0)
 */
void testCuadrado() {
    Punto<float> *cuadrado = new Punto<float>[1000]; // NOLINT

    // Añade las aristas
    cuadrado[0] = Punto<float>(0, 0);
    cuadrado[1] = Punto<float>(0, 1);
    cuadrado[2] = Punto<float>(1, 1);
    cuadrado[3] = Punto<float>(1, 0);

    // Añade 996 puntos aleatorios
    for (int i = 4; i < 1000; i++) {
        cuadrado[i] = Punto<float>(randomFloat(0, 1), randomFloat(0, 1));
    }

    // Calcula la cerradura
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(cuadrado, 1000);
    std::cout << "\n[GiftWrapping] Cerradura cuadrado perfecto 1x1 con 1000 puntos" << std::endl;
    cerraduraGW.first.print();
    assert(cerraduraGW.second == 4);
}

/**
 * Genera un rectángulo de 10000 puntos completamente aleatorio, altura 1 y ancho 10.
 */
void testRectangulo() {
    Punto<float> *rectangulo = new Punto<float>[10000]; // NOLINT
    rectangulo[0] = Punto<float>(0, 0);
    rectangulo[1] = Punto<float>(10, 0);
    rectangulo[2] = Punto<float>(0, 1);
    rectangulo[3] = Punto<float>(10, 1);
    for (int i = 4; i < 10000; i++) {
        rectangulo[i] = Punto<float>(randomFloat(0, 10), randomFloat(0, 1));
    }

    // Calcula la cerradura
    std::pair<Poligono<float>, int> cerraduraGW = giftWrapping(rectangulo, 10000);
    std::cout << "\n[GiftWrapping] Cerradura rectangulo 10x1 con 10000 puntos" << std::endl;
    cerraduraGW.first.print();
    assert(cerraduraGW.second == 4);
}

/**
* Corre los test.
*/
int main() {
    std::cout << "Testeando cerradura convexa" << std::endl;

    // Carga los tests
    testBasico();
    testDuplicados();
    testCuadrado();
    testRectangulo();

    // Retorna
    return 0;
}