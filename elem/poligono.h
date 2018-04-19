/**
 * Clase Polígono.
 * @author Pablo Pizarro
 * @date 19/04/2018
 */

// Constantes
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#ifndef T1_CC5502_1_POLIGONO_H
#define T1_CC5502_1_POLIGONO_H
#endif //T1_CC5502_1_POLIGONO_H

// Importación de librerías
#include "segmento.h"
#include <cmath>

template<class T>
class Poligono {
private:
    Punto<T> *puntos;
    int totalp = 0;
    int MAX_POINTS = 100;
public:
    // Constructor, no toma parámetros
    explicit Poligono();

    // Se crea con lista de puntos
    Poligono(Punto<T> *plist, int totalp);

    // Destructor
    ~Poligono();

    // Agrega un punto
    void addPoint(const Punto<T> &p);

    // Retorna el polígono en forma de string
    std::string toString() const;
};

template<class T>
/**
 * Constructor sin parámetros.
 * @tparam T Template
 */
Poligono<T>::Poligono() {
    this->puntos = new Punto<T>[this->MAX_POINTS];
}

template<class T>
/**
 * Crea polígono usando lista de puntos.
 * @tparam T
 * @param totalp Largo de la lista de puntos
 * @param plist Lista de puntos
 */
Poligono<T>::Poligono(Punto<T> *plist, int totalp) {
    this->MAX_POINTS = std::max(this->MAX_POINTS, totalp);
    this->puntos = new Punto<T>[this->MAX_POINTS];

    // Recorre cada punto y lo añade
    for (int i = 0; i < totalp; i++) {
        this->addPoint(plist[i]);
    }
}

template<class T>
/**
 * Destructor.
 * @tparam T
 */
Poligono<T>::~Poligono() {
    delete[] this->puntos;
}

template<class T>
/**
 * Añade punto al polígono.
 * @tparam T Template
 * @param p Punto
 */
void Poligono<T>::addPoint(const Punto<T> &p) {

    // Si se pasa del límite se aumenta límite de la lista
    if (this->totalp >= this->MAX_POINTS) {
        std::cout << "duplicando" << std::endl;
        this->MAX_POINTS *= 10;

        // Se crea una nueva lista
        Punto<T> *ptemp = new Punto<T>[MAX_POINTS];

        // Se copian los puntos a nueva lista
        for (int i = 0; i < this->totalp; i++) {
            ptemp[i] = this->puntos[i];
        }

        // Se borra lista de puntos vieja
        delete[] this->puntos;

        // Se actualiza puntero
        this->puntos = ptemp;
    }

    // Se guarda el punto
    this->puntos[this->totalp] = p;
    this->totalp += 1;
}

template<class T>
/**
 * Crea string del polígono.
 * @tparam T Template
 * @return
 */
std::string Poligono<T>::toString() const {
    std::string s = "";
    for (int i = 0; i < this->totalp; i++) {
        s += this->puntos[i].toString();
        if (i < this->totalp - 1) {
            s += "->";
        }
    }
    return s;
}

#pragma clang diagnostic pop