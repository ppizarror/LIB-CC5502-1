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
    bool _isccw = false;

    // Calcula el área entre 3 puntos
    T area2(Punto<T> &a, Punto<T> &b, Punto<T> &c);

public:
    // Constructor, no toma parámetros
    explicit Poligono();

    // Se crea con lista de puntos
    Poligono(Punto<T> *plist, int size);

    // Destructor
    ~Poligono();

    // Agrega un punto
    void addPoint(const Punto<T> &p);

    // Retorna el polígono en forma de string
    std::string toString() const;

    // Chequea que el polígono sea CCW
    bool checkCCW();

    // Operación concatenación con string
    template<class U>
    friend std::ostream &operator<<(std::ostream &out, const Poligono<U> &p);

    // Imprime el punto en la consola
    void print() const;

    // Asignación
    Poligono<T> &operator=(const Poligono<T> &poly);

    // Calcula el área del polígono
    T area();
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
 * @param size Largo de la lista de puntos
 * @param plist Lista de puntos
 */
Poligono<T>::Poligono(Punto<T> *plist, int size) {
    this->MAX_POINTS = std::max(this->MAX_POINTS, size);
    this->puntos = new Punto<T>[this->MAX_POINTS];

    // Recorre cada punto y lo añade
    for (int i = 0; i < size; i++) {
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

template<class T>
/**
 * Chequea que el polígono esté en CCW.
 * @tparam T
 * @return
 */
bool Poligono<T>::checkCCW() {
    T sum, t;

    this->_isccw = false;
    if (this->totalp >= 3) {
        for (int i = 0; i < this->totalp; i++) {
            if (i < this->totalp - 1) {
                t = (this->puntos[i + 1].getCoordX() - this->puntos[i].getCoordX()) *
                    (this->puntos[i].getCoordY() + this->puntos[i + 1].getCoordY());
            } else {
                t = (this->puntos[0].getCoordX() - this->puntos[i].getCoordX()) *
                    (this->puntos[i].getCoordY() + this->puntos[0].getCoordY());
            }
            sum += t;
        }

        // Es CCW si la suma es menor a cero
        if (sum < 0) {
            this->_isccw = true;
        }
    }
    return this->_isccw;
}

template<class T>
/**
 * Operador concatenación con strings.
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Poligono<T> &p) {
    out << p.toString();
    return out;
}

template<class T>
/**
 * Imprime el punto en la consola.
 * @tparam T Template
 */
void Poligono<T>::print() const {
    std::cout << this->toString() << std::endl;
}

template<class T>
/**
 * Operador asignación a otro polígono, clona lista de puntos.
 * @tparam T Template
 * @param poly Polígono
 * @return
 */
Poligono<T> &Poligono<T>::operator=(const Poligono<T> &poly) {
    this->totalp = poly.totalp;
    this->MAX_POINTS = poly.MAX_POINTS;
    delete[] this->puntos;

    // Crea nueva lista de puntos
    this->puntos = new Punto<T>[this->MAX_POINTS];

    // Copia los puntos
    for (int i = 0; i < this->totalp; i++) {
        this->puntos[i] = poly.puntos[i];
    }
}

template<class T>
/**
 * Calcula el área del polígono.
 * @tparam T Template
 * @return El área del polígono
 */
T Poligono<T>::area() {
    if (this->checkCCW()) {
        T area;

        // Se crea un punto cualquiera P en el origen para calcular el área
        Punto<T> p0 = Punto<T>(0, 0);

        // Se recorre cada punto para calcular el área
        for (int i = 0; i < this->totalp; i++) {
            if (i < this->totalp - 1) {
                area += area2(p0, this->puntos[i], this->puntos[i + 1]);
            } else { // Se está en el último punto
                area += area2(p0, this->puntos[i], this->puntos[0]);
            }
        }

        return area;
    } else {
        throw std::logic_error("No se puede calcular el área a un polígono que no esté en CCW");
    }
}

template<class T>
/**
 * Calcula el área entre tres puntos-
 * @tparam T
 * @param a Punto A
 * @param b Punto B
 * @param c Punto C
 * @return
 */
T Poligono<T>::area2(Punto<T> &a, Punto<T> &b, Punto<T> &c) {
    T area = (b.getCoordX() - a.getCoordX()) * (c.getCoordY() - a.getCoordY()) -
             (b.getCoordY() - a.getCoordY()) * (c.getCoordX() - a.getCoordX());
    return 0.5 * area;
}

#pragma clang diagnostic pop