/**
 * Funciones utilitarias de cerradura convexa
 *
 * @author Pablo Pizarro
 * @date 18/06/18
 */

// Importación de librerías
#include <algorithm>
#include <ctime>
#include <stack>
#include <vector>
#include "../elem/poligono.h"

// Constantes
#ifndef LIB_CC5502_1_CERRADURA_CONVEXA_H
#define LIB_CC5502_1_CERRADURA_CONVEXA_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

template<class T>
/**
 * Función utilitaria que imprime la lista de puntos
 * @tparam T - Template
 * @param P - Lista de puntos
 * @param n - Largo de la lista
 */
static void imprimeListaPuntos(Punto<T> *P, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << P[i] << "->";
    }
    std::cout << "" << std::endl;
}

#pragma clang diagnostic pop

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
    Punto<T> t = arr[i].clonar();
    arr[i] = arr[j];
    arr[j] = t;
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"

template<class T>
/**
 * Clase mergesort - Ordena la lista de puntos aplicando MergeSort orden nlogn peor caso
 * @tparam T
 */
class MergeSort {
private:
    Punto<T> *p; // Pivote
    bool comp(Punto<T> &a, Punto<T> &b) {
        return this->p->cos(a) < this->p->cos(b);
    }

    void merge(Punto<T> arr[], int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        // Listas temporales
        Punto<T> *L = new Punto<T>[n1];
        Punto<T> *R = new Punto<T>[n2];

        // Copia los datos
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (this->comp(L[i], R[j])) {
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
        delete[] L;
        delete[] R;
    }

public:

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    // Constructor
    MergeSort(Punto<T> &pivote) { // NOLINT
        this->p = &pivote;
    }

#pragma clang diagnostic pop

    void mergeSort(Punto<T> arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            this->merge(arr, l, m, r);
        }
    }
};

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"

template<class T>
/**
 * Clase Quicksort de ordenación
 * @tparam T - Template
 * Adaptado de https://gist.github.com/harish-r/10025689
 */
class QuickSort {
private:
    Punto<T> *p; // Pivote
    bool comp(Punto<T> &a, Punto<T> &b) {
        return this->p->cos(a) < this->p->cos(b);
    }

    int partition(Punto<T> a[], int m, int n) {
        int i, j, pindex;
        pindex = m;
        for (i = m; i < n; i++) {
            if (comp(a[i], a[n])) {
                swap(a, pindex, i);
                pindex++;
            }
        }
        swap(a, pindex, n);
        return pindex;
    }

public:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    QuickSort(Punto<T> &pivote) { // NOLINT
        this->p = &pivote;
    }

#pragma clang diagnostic pop

    int quicksort(Punto<T> a[], int m, int n) {
        int index;
        if (m >= n)
            return 0;
        {
            index = partition(a, m, n);
            quicksort(a, m, index - 1);
            quicksort(a, index + 1, n);
        }
    }
};

#pragma clang diagnostic pop

template<class T>
/**
 * Retorna el punto al lado del top del stack de puntos
 * @tparam T Template
 * @param S Stack de puntos
 * @return
 */
Punto<T> nextToTop(std::stack<Punto<T>> &S) {
    if (S.size() == 1) return S.top();
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

    /**
     * Se crea una nueva lista de puntos para evitar modificar la original, se pasa al plano +X+Y
     */
    Punto<T> *new_cloud = new Punto<T>[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        new_cloud[i] = Punto<T>(cloud[i].getCoordX(), cloud[i].getCoordY());
    }

    /**
     * Intercambio el menor con el primero en la lista
     */
    swap(new_cloud, 0, min);

    /**
     * Se genera el pivote
     */
    Punto<T> pivote = new_cloud[0].clonar();

    /**
     * Se ordenan los puntos por su ángulo con el pivote
     */
    int tinit = clock();
    MergeSort<T> msort = MergeSort<T>(pivote);
    msort.mergeSort(new_cloud, 1, cloud_size - 1);
    // QuickSort<T> qsort = QuickSort<T>(pivote);
    // qsort.quicksort(new_cloud, 1, cloud_size - 1);
    std::cout << "Tiempo msort: " << (clock() - tinit) / double(CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;

    /**
     * Si hay dos puntos con igual ángulo se deja aquel con mayor distancia
     */
    int vp = 1; // Indica cuántos puntos válidos existen
    double lang = 0;
    double mxdist = 0;
    int maxpos = -1;
    Punto<T> *final_cloud = new Punto<T>[cloud_size];
    final_cloud[0] = new_cloud[0];
    for (int i = 1; i < cloud_size; i++) {
        if (fabs(lang - new_cloud[0].cos(new_cloud[i])) > 1e-10) { // Si el ángulo cambia se actualiza la distancia
            if (maxpos != -1) {
                final_cloud[vp] = new_cloud[maxpos];
                vp++;
            }
            mxdist = new_cloud[0].dist(new_cloud[i]);
            lang = new_cloud[0].cos(new_cloud[i]);
            maxpos = i;
            if (i == cloud_size - 1) {
                final_cloud[vp] = new_cloud[i];
                vp++;
            }
        } else {
            if (new_cloud[0].dist(new_cloud[i]) > mxdist) {
                maxpos = i;
            }
            if (i == cloud_size - 1 && maxpos != -1) {
                final_cloud[vp] = new_cloud[i];
                vp++;
            }
        }
    }

    /**
     * Genera la cerradura
     */
    std::stack<Punto<T>> hull;
    hull.push(final_cloud[0]);
    hull.push(final_cloud[1]);
    hull.push(final_cloud[2]);
    for (int i = 3; i < vp; i++) {
        while (nextToTop(hull).ccw(hull.top(), final_cloud[i]) <= 0) {
            hull.pop();
        }
        hull.push(final_cloud[i]);
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
    delete[] final_cloud;
    delete[] new_cloud;

    /**
     * Retorna el par
     */
    return std::make_pair(*cerradura, total_cerradura);

};

/**
 * Intercambia dos valores de una lista de núeros enteros
 * @param arr - Arreglo
 * @param i - Posición i
 * @param j - Posición j
 */
void swapInt(int *arr, int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

/**
 * Clase mergesort - Ordena la lista de puntos aplicando MergeSort orden nlogn peor caso
 */
class MergeSort {
private:
    void merge(double *cosp, int *arrpos, int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        // Listas temporales
        int *L = new int[n1];
        int *R = new int[n2];

        // Copia los datos
        for (i = 0; i < n1; i++)
            L[i] = arrpos[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arrpos[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (cosp[L[i]] < cosp[R[j]]) {
                arrpos[k] = L[i];
                i++;
            } else {
                arrpos[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arrpos[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arrpos[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

public:
    void mergeSort(double *cosp, int *arrpos, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(cosp, arrpos, l, m);
            mergeSort(cosp, arrpos, m + 1, r);
            this->merge(cosp, arrpos, l, m, r);
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
std::pair<Poligono<T>, int> grahamScanv2(Punto<T> *cloud, int cloud_size) {

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
    for (int i = 1; i < cloud_size; i++) { // O(n)
        T y = cloud[i].getCoordY();
        // Se encontró un punto con menor coordenada y, o uno que tiene igual y pero menor x
        if ((y < ymin) or (y == ymin and cloud[i].getCoordX() < cloud[min].getCoordX())) {
            ymin = y;
            min = i;
        }
    }

    /**
     * Se genera el pivote
     */
    Punto<T> pivote = cloud[min].clonar();

    /**
     * Crea una lista con las posiciones de cada objeto a ordenar
     */
    int *ppos = new int[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        ppos[i] = i;
    }
    swapInt(ppos, 0, min);

    /**
     * Crea una lista con los cosenos de cada punto con respecto al pivote
     */
    double *cosp = new double[cloud_size];
    cosp[0] = 0;
    for (int i = 1; i < cloud_size; i++) {
        cosp[i] = pivote.cos(cloud[i]);
    }

    /**
     * Se ordena la lista de acuerdo al ángulo coseno con respecto al pivote, sólo se ordenan las posiciones
     */
    MergeSort2 msort = MergeSort2();
    msort.mergeSort(cosp, ppos, 1, cloud_size - 1);

    /**
     * Se crea una nueva lista de acuerdo a las posiciones
     */
    Punto<T> *new_cloud = new Punto<T>[cloud_size];
    for (int i = 0; i < cloud_size; i++) {
        new_cloud[i] = cloud[ppos[i]];
    }

    /**
     * Si hay dos puntos con igual ángulo se deja aquel con mayor distancia
     */
    int vp = 1; // Indica cuántos puntos válidos existen
    double lang = 0;
    double mxdist = 0;
    int maxpos = -1;
    Punto<T> *final_cloud = new Punto<T>[cloud_size];
    final_cloud[0] = new_cloud[0];
    for (int i = 1; i < cloud_size; i++) {
        if (fabs(lang - new_cloud[0].cos(new_cloud[i])) > 1e-10) { // Si el ángulo cambia se actualiza la distancia
            if (maxpos != -1) {
                final_cloud[vp] = new_cloud[maxpos];
                vp++;
            }
            mxdist = new_cloud[0].dist(new_cloud[i]);
            lang = new_cloud[0].cos(new_cloud[i]);
            maxpos = i;
            if (i == cloud_size - 1) {
                final_cloud[vp] = new_cloud[i];
                vp++;
            }
        } else {
            if (new_cloud[0].dist(new_cloud[i]) > mxdist) {
                maxpos = i;
            }
            if (i == cloud_size - 1 && maxpos != -1) {
                final_cloud[vp] = new_cloud[i];
                vp++;
            }
        }
    }

    /**
     * Genera la cerradura
     */
    std::stack<Punto<T>> hull;
    hull.push(final_cloud[0]);
    hull.push(final_cloud[1]);
    hull.push(final_cloud[2]);
    for (int i = 3; i < vp; i++) {
        while (nextToTop(hull).ccw(hull.top(), final_cloud[i]) <= 0) {
            hull.pop();
        }
        hull.push(final_cloud[i]);
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
    delete[] final_cloud;

    /**
     * Retorna el par
     */
    return std::make_pair(*cerradura, total_cerradura);

};

#endif //LIB_CC5502_1_CERRADURA_CONVEXA_H