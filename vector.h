/**
 * Clase Vector.
 * @author Pablo Pizarro
 * @date 19/04/2018
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef T1_CC5502_1_VECTOR_H
#define T1_CC5502_1_VECTOR_H
#endif //T1_CC5502_1_VECTOR_H

template<class T>
class Vector {
private:
    T *c = new T[3];
    int dim;
public:

    // Inicia un vector con 2 componentes
    Vector(T i, T j);

    // Inicia un vector con 3 componentes
    Vector(T i, T j, T k);

    // Destructor
    ~Vector();
};

template<class T>
/**
 * Constructor vector 2 componentes.
 * @tparam T
 * @param i Componente eje x
 * @param j Componente eje y
 */
Vector<T>::Vector(T i, T j) {
    this->c[0] = i;
    this->c[1] = j;
    this->dim = 2;
}

template<class T>
/**
 * Constructor vector 3 componentes.
 * @tparam T
 * @param i Componente eje x
 * @param j Componente eje y
 * @param k Componente eje z
 */
Vector<T>::Vector(T i, T j, T k) {
    this->c[0] = i;
    this->c[1] = j;
    this->c[2] = k;
    this->dim = 2;
}

template<class T>
/**
 * Destructor
 * @tparam T Template
 */
Vector<T>::~Vector() {
    delete[] this->c;
}

#pragma clang diagnostic pop