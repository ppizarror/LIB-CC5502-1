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
 * [GiftWrapping] Testeo básico, genera figuras simples de pocos puntos.
 */
void testBasicoGiftWrapping() {
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)}; // 5
    std::pair<Poligono<float>, int> cerradura = giftWrapping(plist, 5);

    // El poligono es el mismo
    assert(cerradura.second == 5);
}

/**
 * [GiftWrapping] Testeo duplicados
 */
void testDuplicadosGiftWrapping() {
    Punto<int> plist[] = {Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(1, 1), Punto<int>(1, 0),
                          Punto<int>(1, 0)}; // 6
    std::pair<Poligono<int>, int> cerradura = giftWrapping(plist, 6);
    assert(cerradura.second == 3);
}

/**
 * [GiftWrapping] Genera un cuadrado de 1x1 en flotante con 1000 puntos dentro,
 * la cerradura debe ser (0,0),(0,1),(1,1),(1,0)
 */
void testCuadradoGiftWrapping() {
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
    std::pair<Poligono<float>, int> cerradura = giftWrapping(cuadrado, 1000);
    std::cout << "\n[GiftWrapping] Cerradura cuadrado perfecto 1x1 con 1000 puntos" << std::endl;
    cerradura.first.print();
    assert(cerradura.second == 4);
}

/**
 * [GiftWrapping] Genera un rectángulo de 10000 puntos completamente aleatorio, altura 1 y ancho 10.
 */
void testRectanguloGiftWrapping() {
    Punto<float> *rectangulo = new Punto<float>[10000]; // NOLINT
    rectangulo[0] = Punto<float>(0, 0);
    rectangulo[1] = Punto<float>(10, 0);
    rectangulo[2] = Punto<float>(0, 1);
    rectangulo[3] = Punto<float>(10, 1);
    for (int i = 4; i < 10000; i++) {
        rectangulo[i] = Punto<float>(randomFloat(0, 10), randomFloat(0, 1));
    }

    // Calcula la cerradura
    std::pair<Poligono<float>, int> cerradura = giftWrapping(rectangulo, 10000);
    std::cout << "\n[GiftWrapping] Cerradura rectangulo 10x1 con 10000 puntos" << std::endl;
    cerradura.first.print();
    assert(cerradura.second == 4);
}

/**
 * Test básico que verifica validez de Graham en casos de prueba sencillos.
 */
void testBasicoGraham() {
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)}; // 5
    std::pair<Poligono<float>, int> cerradura = grahamScan(plist, 5);
}

/**
* Corre los test.
*/
int main() {
    std::cout << "Testeando cerradura convexa" << std::endl;

    // Carga los tests, GiftWrapping
    // testDuplicadosGiftWrapping();
    // testBasicoGiftWrapping();
    // testCuadradoGiftWrapping();
    // testRectanguloGiftWrapping();
    testBasicoGraham();

    // Retorna
    return 0;
}