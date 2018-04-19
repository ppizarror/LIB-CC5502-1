/**
 * Archivo principal
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

// Importación de librerías
#include <iostream>
#include "punto.h"

int main() {
    Punto<float> p = Punto<float>(4.20, 3.60);
    std::cout << p.toString() << std::endl;
    return 0;
}