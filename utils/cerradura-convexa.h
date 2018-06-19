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
 * Función utilitaria que imprime la lista de puntos
 * @tparam T - Template
 * @param P - Lista de puntos
 * @param n - Largo de la lista
 */
static void _imprimeListaPuntos(Punto<T> *P, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << P[i] << "->";
    }
    std::cout << "" << std::endl;
}

template<class T>
/**
 * Intercambia dos elementos en una lista de puntos
 * @tparam T Template
 * @param arr Arreglo
 * @param i
 * @param j
 */
void swap(Punto<T> arr[], int i, int j) {
    if (i == j) return;
    std::cout << i << "," << j << std::endl;
    Punto<T> *t = new Punto<T>(arr[i].getCoordX(), arr[i].getCoordY());
    arr[i] = arr[j];
    arr[j] = *t;
}

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
     * Busca el punto de más a la izquierda y más abajo
     */
    Punto<T> pointOnHull;
    int j = 0; // Almacena el índice del punto más hacia la izquierda
    T min_x = cloud[0].getCoordX();
    T min_y = cloud[0].getCoordY();
    for (int i = 1; i < cloud_size; i++) {
        // Se encontró un punto más hacia la izquierda y abajo
        if ((cloud[i].getCoordX() < min_x) or (min_x == cloud[i].getCoordX() && cloud[i].getCoordY() < min_y)) {
            j = i; // Actualiza el índice
            min_x = cloud[i].getCoordX();
            min_y = cloud[i].getCoordY();
        }
    }
    pointOnHull = cloud[j]; // Define el punto de más hacia la izquierda

    /**
     * Se crea un nuevo arreglo de puntos todos centrados en el plano +X+Y
     */
    T lx = pointOnHull.getCoordX();
    T ly = pointOnHull.getCoordY();
    Punto<T> *new_cloud = new Punto<T>[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        new_cloud[i] = Punto<T>(cloud[i].getCoordX() - lx, cloud[i].getCoordY() - ly);
    }
    swap(new_cloud, j, 0);
    pointOnHull = new_cloud[0];

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
        endpoint = new_cloud[0];
        Segmento<T> arco = Segmento<T>(P[i], endpoint);
        double lastdist = -1, newdist;
        for (j = 1; j < cloud_size; j++) {
            if (endpoint == pointOnHull or arco.left(new_cloud[j])) {
                arco = Segmento<T>(P[i], endpoint);
                endpoint = new_cloud[j];
                lastdist = P[i].dist(new_cloud[j]);
            } else if (arco.on(new_cloud[j]) && lastdist != -1) { // Punto colineal
                newdist = P[i].dist(new_cloud[j]);
                if (newdist > lastdist) {
                    arco = Segmento<T>(P[i], endpoint);
                    endpoint = new_cloud[j];
                    lastdist = P[i].dist(new_cloud[j]);
                }
            }
        }
        delete &arco;
        i++;
        pointOnHull = endpoint;
    } while (endpoint != P[0]);

    /**
     * Suma el punto inicial restado a P
     */
    Punto<T> lrest = Punto<T>(lx, ly);
    for (j = 0; j < i; j++) {
        P[j] += lrest;
    }

    /**
     * Crea el polígono
     */
    Poligono<T> *cerradura = new Poligono<T>(P, i);

    /**
     * Borra variables
     */
    delete[] P;
    delete[] new_cloud;

    /**
     * Retorna el polígono de la cerradura y el total de puntos
     */
    return std::make_pair(*cerradura, i);

}

/**
 * Puntero al pivote
 */
const void *pv;

template<class T>
class QuickSort {
public:
    bool comp(Punto<T> &a, Punto<T> &b) {
        Punto<T> *p = (Punto<T> *) pv;
        if (fabs(p->cos(a) - p->cos(b)) < 1e-10)
            return p->dist(a) < p->dist(b);
        else
            return p->cos(a) > p->cos(b);
    }

    int partition(Punto<T> *arr, const int left, const int right, const int sz) {
        const int mid = left + (right - left) / 2;
        Punto<T> pivot = arr[mid];
        swap(arr, mid, left);
        int i = left + 1;
        int j = right;
        while (i <= j) {
            while (i <= j && comp(arr[i], pivot)) {
                i++;
            }
            while (i <= j && !comp(arr[j], pivot)) {
                j--;
            }
            if (i < j) {
                swap(arr, i, j);
            }
        }
        swap(arr, i - 1, left);
        return i - 1;
    }

    void quicksort(Punto<T> *arr, const int left, const int right, const int sz) {
        if (left >= right) {
            return;
        }
        int part = partition(arr, left, right, sz);
        quicksort(arr, left, part - 1, sz);
        quicksort(arr, part + 1, right, sz);
    }
};

template<class T>
class MergeSort {
public:
    static bool comp(Punto<T> &a, Punto<T> &b) {
        Punto<T> *p = (Punto<T> *) pv;
        if (fabs(p->cos(a) - p->cos(b)) < 1e-10)
            return p->dist(a) >= p->dist(b);
        else
            return p->cos(a) >= p->cos(b);
    }

    static void merge(Punto<T> arr[], int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        // Listas temporales
        Punto<T> L[n1], R[n2];

        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSort(Punto<T> arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
};

template<class T>
/**
 * Retorna el punto al lado del top del stack de puntos
 * @tparam T Template
 * @param S Stack de puntos
 * @return
 */
Punto<T> nextToTop(std::stack<Punto<T>> &S) {
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
    Punto<T> p = cloud[min];
    T lx = p.getCoordX();
    T ly = p.getCoordY();

    /**
     * Se crea una nueva lista de puntos para evitar modificar la original, se pasa al plano +X+Y
     */
    Punto<T> *new_cloud = new Punto<T>[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        new_cloud[i] = Punto<T>(cloud[i].getCoordX() - lx, cloud[i].getCoordY() - ly);
    }

    /**
     * Intercambio el menor con el primero en la lista
     */
    swap(new_cloud, 0, min);

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
    // QuickSort<T> qsort = QuickSort<T>();
    MergeSort<T> msort = MergeSort<T>();
    _imprimeListaPuntos(new_cloud, cloud_size);
    std::cout << "orden" << std::endl;
    // qsort.quicksort(new_cloud, 1, cloud_size - 1, cloud_size);
    msort.mergeSort(new_cloud, 1, cloud_size - 1);
    _imprimeListaPuntos(new_cloud, cloud_size);

    /**
     * Si hay dos puntos con igual ángulo se deja aquel con mayor distancia
     */
    int vp = 1; // Indica cuántos puntos válidos existen
    double lang = 0;
    double mxdist = 0;
    int maxpos = -1;
    for (int i = 1; i < cloud_size; i++) {
        if (lang != new_cloud[0].cos(new_cloud[i])) { // Si el ángulo cambia se actualiza la distancia
            if (maxpos != -1) {
                vp++;
            }
            mxdist = new_cloud[0].dist(new_cloud[i]);
            lang = new_cloud[0].cos(new_cloud[i]);
            std::cout << "angulo cambia " << lang << std::endl;
            maxpos = i;
            if (i == cloud_size - 1) {
                vp++;
            }
        } else {
            if (new_cloud[0].dist(new_cloud[i]) > mxdist) {
                maxpos = i;
                std::cout << "bigg" << std::endl;
            }
        }
        std::cout << vp << std::endl;
    }

    /**
     * Se imprime lista de angulos
     */
    std::cout << "Angulos: ";
    for (int i = 1; i < cloud_size; i++) {
        std::cout << new_cloud[0].cos(new_cloud[i]) << " -> ";
    }
    std::cout << "" << std::endl;
    std::cout << "Distancias: ";
    for (int i = 1; i < cloud_size; i++) {
        std::cout << new_cloud[0].dist(new_cloud[i]) << " -> ";
    }
    std::cout << "" << std::endl;

    /**
     * Genera la cerradura
     */
    std::stack<Punto<T>> hull;
    hull.push(new_cloud[0]);
    hull.push(new_cloud[1]);
    hull.push(new_cloud[2]);
    for (int i = 3; i < cloud_size; i++) {
        while (nextToTop(hull).ccw(hull.top(), new_cloud[i]) <= 0) {
            std::cout << "vale kk" << hull.top() << std::endl;
            hull.pop();
        }
        hull.push(new_cloud[i]);
    }

    /**
     * Crea la lista de la cerradura
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

    /**
     * Retorna el par
     */
    return std::make_pair(*cerradura, total_cerradura);

};

#endif //LIB_CC5502_1_CERRADURA_CONVEXA_H