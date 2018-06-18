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

/**
 * Testeo básico, genera figuras simples de pocos puntos.
 */
void testBasico() {
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)}; // 5
    std::pair<Poligono<float>, int> cerradura = giftWrapping(plist, 5);

    // El poligono es el mismo
    assert(cerradura.second == 5);
}

/**
 * Testeo duplicados
 */
void testDuplicados() {
    Punto<int> plist[] = {Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(0, 0), Punto<int>(1, 1), Punto<int>(1, 0),
                          Punto<int>(1, 0)}; // 6
    std::pair<Poligono<int>, int> cerradura = giftWrapping(plist, 6);
    cerradura.first.print();
    std::cout << cerradura.second << std::endl;
}

/**
 * Genera un cuadrado de 1x1 en flotante con 1000 puntos dentro, la cerradura debe ser (0,0),(0,1),(1,1),(1,0)
 */
void testCuadrado() {
    Punto<float> *cuadrado = new Punto<float>[1000]; // NOLINT

    // Añade las aristas
    cuadrado[0] = Punto<float>(0, 0);
    cuadrado[1] = Punto<float>(0, 1);
    cuadrado[2] = Punto<float>(1, 1);
    cuadrado[3] = Punto<float>(1, 0);

    // Añade 996 puntos aleatorios
    for (int i = 0; i < 996; i++) {

    }
}

/**
* Corre los test.
*/
int main() {
    std::cout << "Testeando cerradura convexa" << std::endl;

    // Carga los tests
    testDuplicados();
    // testBasico();

    // Retorna
    return 0;
}