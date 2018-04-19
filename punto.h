/**
 * Clase Punto
 * @author Pablo Pizarro
 * @date 18/04/2018
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef T1_CC5502_1_PUNTO_H
#define T1_CC5502_1_PUNTO_H
#endif //T1_CC5502_1_PUNTO_H

// Importación de librerías
#include <stdexcept>

// Crea un template para el tipo de dato de Punto
template<class T>
class Punto {
public:

    // Constructor punto en 2D
    Punto(T x, T y);

    // Constructor punto en 3D
    Punto(T x, T y, T z);

    // Destructor
    ~Punto();

    // Obtiene la coordenada x
    T getCoordX() const;

    // Obtiene la coordenada y
    T getCoordY() const;

    // Obtiene la coordenada z
    T getCoordZ() const;

    // Retorna el punto en forma de String
    std::string toString() const;

private:
    T *coord = new T[3]; // Vector
    int dim; // Dimensión del punto
};

// Crea punto en 2D
template<class T>
Punto<T>::Punto(T x, T y) {
    this->coord[0] = x;
    this->coord[1] = y;
    this->dim = 2;
}

// Crea punto en 3D
template<class T>
Punto<T>::Punto(T x, T y, T z) {
    this->coord[0] = x;
    this->coord[1] = y;
    this->coord[2] = z;
    this->dim = 3;
}

// Retorna coordenada x
template<class T>
T Punto<T>::getCoordX() const {
    return coord[0];
}

// Retorna coordenada y
template<class T>
T Punto<T>::getCoordY() const {
    return coord[1];
}

// Retorna coordenada x, sólo válido en un punto 3D
template<class T>
T Punto<T>::getCoordZ() const {
    if (this->dim < 3) {
        throw std::logic_error("La coordenada Z no existe en un punto 2D");
    }
    return coord[2];
}

// Elimina el objeto de la memoria
template<class T>
Punto<T>::~Punto() {
    delete[] this->coord;
}

// Retorna un string con el punto
template<class T>
std::string Punto<T>::toString() const {
    std::string s = "(" + std::to_string(this->getCoordX()) + "," + std::to_string(this->getCoordY()); // Punto
    if (this->dim == 2) {
        s += ")";
    } else {
        s += "," + std::to_string(this->getCoordZ()) + ")";
    }
    return s;
}

#pragma clang diagnostic pop