/**
 * Archivo principal
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include "punto.h"

int main() {
    Punto<float> p = Punto<float>(1.5, 1);
    std::cout << p.toString() << std::endl;
    return 0;
}