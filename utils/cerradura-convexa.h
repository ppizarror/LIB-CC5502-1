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
    Punto<T> temp = new_cloud[0].clonar();
    new_cloud[0] = new_cloud[min];
    new_cloud[min] = temp;

    Punto<T> pivote = new_cloud[0]; // Punto pivote desde el cual se ordenan los demás puntos de acuerdo a su orientación
    std::sort(new_cloud + 1, new_cloud + cloud_size - 1, [&pivote](Punto<T> a, Punto<T> b) {
        int order = pivote.ccw(a, b);
        if (order == 0) {
            // Si los puntos son colineales ordena por distancia al pivote
            return pivote.dist(a) < pivote.dist(b);
        } else {
            // Retorna true si los puntos no están en ccw, así genera una lista con los primeros puntos en ccw
            return order == -1;
        }
    });

    /**
     * Se crea un stack para facilitar la creación de la cerradura
     */
    Poligono<T> *cerradura1 = new Poligono<T>(new_cloud, cloud_size);
    cerradura1->print();
    std::stack<Punto<T>> hull;
    hull.push(new_cloud[0]);
    hull.push(new_cloud[1]);
    hull.push(new_cloud[2]);

    for (int i = 3; i < cloud_size; i++) {
        while (nextToTop(hull).ccw(hull.top(), new_cloud[i]) != -1) {
            hull.pop();
        }
        hull.push(new_cloud[i]);
    }

    /**
     * Se crea lista de puntos a partir del stack
     */
    int total_cerradura = hull.size();
    Punto<T> *P = new Punto<T>[total_cerradura];
    for (int i = total_cerradura - 1; i >= 0; i--) {
        P[i] = hull.top();
        hull.pop();
    }

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