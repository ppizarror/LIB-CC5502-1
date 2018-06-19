/**
 * Funciones utilitarias de cerradura convexa
 *
 * @author Pablo Pizarro
 * @date 18/06/18
 */

// Importación de librerías
#include <algorithm>
#include <stack>
#include <vector>
#include "../elem/poligono.h"

// Constantes
#ifndef LIB_CC5502_1_CERRADURA_CONVEXA_H
#define LIB_CC5502_1_CERRADURA_CONVEXA_H

template<class T>
/**
 * Algoritmo de Gift Wrapping
 * @tparam T - Tipo de datos
 * @param cloud - Nube de puntos a realizar la cerradura convexa
 * @param cloud_size - Número de puntos
 * @return Poligono - Polínono con puntos que representa la cerradura convexa
 */
std::pair<Poligono<T>, int> giftWrapping(Punto<T> *cloud, int cloud_size) {

    /**
     * Caso de borde
     */
    if (cloud_size <= 3) {
        Poligono<T> *cerradura = new Poligono<T>(cloud, cloud_size);
        return std::make_pair(*cerradura, cloud_size);
    }

    /**
     * Busca el punto de más a la izquierda
     */
    Punto<T> pointOnHull;
    int j = 0; // Almacena el índice del punto más hacia la izquierda
    T min_x = cloud[0].getCoordX();
    for (int i = 1; i < cloud_size; i++) {
        if (cloud[i].getCoordX() < min_x) { // Se encontró un punto más hacia la izquierda
            j = i; // Actualiza el índice
            min_x = cloud[i].getCoordX();
        }
    }
    pointOnHull = cloud[j]; // Define el punto de más hacia la izquierda

    /**
     * Crea el arreglo de puntos en la cerradura convexa P, ya que en un principio
     * no se sabe cuantos son pueden ser hasta |S|=cloud_size, luego se rehará otro
     * arreglo con tamaño fijo
     */
    Punto<T> *P = new Punto<T>[cloud_size];

    /**
     * Se recorre cada punto de S, buscando aquellos puntos entre P[i] que formen un arco
     * que deje a todos los demás puntos de la nube hacia la derecha
     */
    int i = 0;
    Punto<T> endpoint; // Punto final del segmento que nace en P[i]
    do {
        P[i] = pointOnHull; // Añade el punto que se sabe que pertenece a CH
        endpoint = cloud[0];
        Segmento<T> arco = Segmento<T>(P[i], endpoint);
        for (j = 1; j < cloud_size; j++) {
            if (endpoint == pointOnHull or arco.left(cloud[j])) {
                arco = Segmento<T>(P[i], endpoint);
                endpoint = cloud[j];
            }
        }
        delete &arco;
        i++;
        pointOnHull = endpoint;
    } while (endpoint != P[0]);

    /**
     * Crea el polígono
     */
    Poligono<T> *cerradura = new Poligono<T>(P, i);

    /**
     * Borra variables
     */
    delete &P;

    /**
     * Retorna el polígono de la cerradura y el total de puntos
     */
    return std::make_pair(*cerradura, i);

}

template<class T>
/**
 * Retorna el punto al lado del top del stack de puntos
 * @tparam T Template
 * @param S Stack de puntos
 * @return
 */
Punto<T> nextToTop(std::stack<Punto<T>> &S) {
    if (S.size() == 1) {
        return S.top();
    }
    Punto<T> p = S.top();
    S.pop();
    Punto<T> res = S.top();
    S.push(p);
    return res;
}

/**
 * Puntero al pivote
 */
const void *pv;

template<class T>
/**
 * Ordena dos puntos de acuerdo a su ángulo con el pivote
 * @param a Punto
 * @param b Punto
 * @return
 */
bool ordenarAngulo(Punto<T> &a, Punto<T> &b) {
    Punto<T> *p = (Punto<T> *) pv;
    a.print();
    b.print();
    std::cout << p->cos(a) << std::endl;
    std::cout << p->cos(b) << std::endl;
    std::cout << (p->cos(a) < p->cos(b)) << std::endl;
    std::cout << "....." << std::endl;
    return p->cos(a) < p->cos(b);
}

template<class T>
void _imprimeListaPuntos(Punto<T> *P, int n) {
    Poligono<T> poly = Poligono<T>(P, n);
    poly.print();
}

template<class T>
class QuickSort {
public:
    // Función que compara dos puntos con el pivote
    bool comparar(Punto<T> &a, Punto<T> &b) {
        Punto<T> *p = (Punto<T> *) pv;
        return p->cos(a) < p->cos(b);
    }

    // Función para dividir el array y hacer los intercambios
    int dividir(Punto<T> *array, int start, int end) {
        int left;
        int right;
        Punto<T> pivot;
        Punto<T> temp;

        pivot = array[start];
        left = start;
        right = end;

        // Mientras no se cruzen los índices
        while (left < right) {
            while (comparar(array[right], pivot)) {
                right--;
            }

            while ((left < right) && (!comparar(array[right], pivot))) {
                left++;
            }

            // Si todavía no se cruzan los indices seguimos intercambiando
            if (left < right) {
                temp = array[left];
                array[left] = array[right];
                array[right] = temp;
            }
        }

        // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
        temp = array[right];
        array[right] = array[start];
        array[start] = temp;

        // La nueva posición del pivot
        return right;
    }

    // Función recursiva para hacer el ordenamiento
    void quicksort(Punto<T> *array, int start, int end) {
        int pivot;
        if (start < end) {
            pivot = dividir(array, start, end);
            quicksort(array, start, pivot - 1);
            quicksort(array, pivot + 1, end);
        }
    }
};

template<class T>
/**
 * Algoritmo de Graham Scan, algoritmo sólo valido para 2D
 * @tparam T - Tipo de datos
 * @param cloud - Nube de puntos a realizar la cerradura convexa
 * @param cloud_size - Número de puntos
 * @return Poligono - Polínono con puntos que representa la cerradura convexa
 */
std::pair<Poligono<T>, int> grahamScan(Punto<T> *cloud, int cloud_size) {

    /**
     * Caso de borde
     */
    if (cloud_size <= 3) {
        Poligono<T> *cerradura = new Poligono<T>(cloud, cloud_size);
        return std::make_pair(*cerradura, cloud_size);
    }

    /**
     * Se elige el punto con la menor coordenada ordenada, si hay varios iguales
     * se elige aquel con el menor x
     */
    T ymin = cloud[0].getCoordY(); // Valor más chico de y
    int min = 0; // Posición en la nube con el punto ganador
    for (int i = 1; i < cloud_size; i++) {
        T y = cloud[i].getCoordY();
        // Se encontró un punto con menor coordenada y, o uno que tiene igual y pero menor x
        if ((y < ymin) or (y == ymin and cloud[i].getCoordX() < cloud[min].getCoordX())) {
            ymin = y;
            min = i;
        }
    }

    /**
     * Se crea una nueva lista de puntos para evitar modificar la original
     */
    Punto<T> *new_cloud = new Punto<T>[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        new_cloud[i] = Punto<T>(cloud[i].getCoordX(), cloud[i].getCoordY());
    }

    /**
     * Intercambio el menor con el primero en la lista
     */
    if (min != 0) {
        Punto<T> temp = new_cloud[0].clonar();
        new_cloud[0] = new_cloud[min];
        new_cloud[min] = temp;
    }

    /**
     * Se genera el pivote
     */
    Punto<T> pivote = new_cloud[0].clonar();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
    pv = &pivote;
#pragma clang diagnostic pop

    /**
     * Se ordenan los puntos por su ángulo con el pivote
     */
    QuickSort<T> qsort = QuickSort<T>();
    _imprimeListaPuntos(new_cloud, cloud_size);
    qsort.quicksort(new_cloud, 1, cloud_size - 1);
    // std::sort(new_cloud + 1, new_cloud + cloud_size, ordenarAngulo<T>);
    _imprimeListaPuntos(new_cloud, cloud_size);

    /**
     * Crea una nueva lista con la cerradura
     */
     Punto<T> *hull

    /**
     * Crea el polígono cerradura convexa
     */
    int total_cerradura = 0;
    Punto<T> *P = new Punto<T>[total_cerradura];

    /**
     * Crea el polígono
     */
    Poligono<T> *cerradura = new Poligono<T>(P, total_cerradura);

    /**
     * Elimina variables
     */
    delete[] new_cloud;
    delete[] P;

    /**
     * Retorna el par
     */
    return std::make_pair(*cerradura, total_cerradura);

};

#endif //LIB_CC5502_1_CERRADURA_CONVEXA_H