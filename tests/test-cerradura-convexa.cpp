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

/**
 * Testeo básico, genera figuras simples de pocos puntos.
 */
void testBasico() {
    Punto<float> plist[] = {Punto<float>(5, 0), Punto<float>(6, 4), Punto<float>(4, 5), Punto<float>(1, 5),
                            Punto<float>(1, 0)};
    giftWrapping(plist);
}

/**
* Corre los test.
*/
int main() {
    std::cout << "Testeando cerradura convexa" << std::endl;

    // Carga los tests
    testBasico();

    // Retorna
    return 0;
}