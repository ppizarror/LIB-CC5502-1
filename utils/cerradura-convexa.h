/**
 * Funciones utilitarias de cerradura convexa
 *
 * @author Pablo Pizarro
 * @date 18/06/18
 */

// Importación de librerías
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
 * Algoritmo de Graham Scan
 * @tparam T - Tipo de datos
 * @param cloud - Nube de puntos a realizar la cerradura convexa
 * @param cloud_size - Número de puntos
 * @return Poligono - Polínono con puntos que representa la cerradura convexa
 */
std::pair<Poligono<T>, int> grahamScan(Punto<T> *cloud, int cloud_size) {
};

#endif //LIB_CC5502_1_CERRADURA_CONVEXA_H