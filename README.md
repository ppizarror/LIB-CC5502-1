# LIB-CC5502

Librería funciones geométricas curso Geometría computacional CI5502, uchile. Para ejecutar cargar el proyecto en CLion y ejecutar los distintos casos de prueba.

1. **TEST-POLIGONO**: Testea la clase Poligono&lt;T>.
2. **TEST-PUNTO**: Testea la clase Punto&lt;T>.
3. **TEST-POLIGONO**: Testea la clase Segmento&lt;T>.
4. **TEST-POLIGONO**: Testea la clase Vector&lt;T>.
5. **TEST-CERRADURA-CONVEXA**: Testea las funciones de la cerradura convexa *giftWrapping* y *grahamScan*

## Punto

Para crear un punto en 2D o 3D:
```cpp
#include "elem/punto.h"

Punto<int> p1 = Punto<int>(0, 1); // Punto coordenadas enteras
Punto<double> p2 = Punto<double>(10, 5, 7);    
```

Funciones de Punto:

```cpp
#include "elem/punto.h"

Punto<int> a = Punto<int>(1, 2, 3);
Punto<int> b = Punto<int>(4, 5, 6);

// Imprime el punto
a.print();
std::cout << a << std::endl;

// Operaciones puntos
Punto<int> c = a + b;
Punto<int> c = a - b;
Punto<int> c = a / 5;
Punto<int> c = a * 5;
a *= 5;
a /= 5;

// Igualdad
bool c = a == b;
bool c = a != b;

// Otras operaciones
Punto<int> c = abs(a); // Valor absoluto
double c = a.dist(b); // Distancia
double c = a.dist2(b); // Distancia al cuadrado
double c = a.distOrigin(); // Distancia al origen
int c = a.getDimension(); // Obtiene la dimensión del punto
int c = a.ccw(c,d); // Ve si el punto y c,d están orientados en ccw
Punto<int> c = a.clonar(); // Clona el punto
double c = a.cos(b); // Retorna el coseno vectorial   
```

## Segmento

Permite crear un segmento entre dos puntos:

```cpp
#include "elem/segmento.h"

Punto<double> p1 = Punto<double>(0, 1);
Punto<double> p2 = Punto<double>(2, 3);

Segmento<double> s = Segmento<double>(p1, p2); 
```

Funciones del segmento:

```cpp
double c = s.getLength(); // Obtiene largo del segmento, igual a norm();

// Verifica posiciones
Punto<double> p = Punto<double>(4, 8);
bool c = s.left(p); // Ve si p esta a la izquierda de s
bool c = s.right(p);
bool c = s.on(p);
bool c = s.leftOn(p);
bool c = s.rightOn(p);
```

## Vector

Permite crear un vector entre (0,0,0) y un punto

```cpp
#include "elem/vector.h"

Punto<double> p1 = Punto<double>(0, 1);

Vector<double> vec = Vector<double>(p1);    
```

Funciones:

```cpp
// Imprimir en consola
vec.print();
std::cout << vec << std::endl;

// Operaciones
vec.normalize();
vec.getNormalized() // -> new Vector<T>
vec.cross(v1); // Producto cruz
vec.dot(v1); // Producto punto
vec.abs(); // -> new Vector<T> valor absoluto

// Otros
int d = vec.getDimension(); // Dimensión del vector
T d = vec.norm(); // Norma del vector
```


## Poligono

Permite crear un polígono a partir de una lista de puntos

```cpp
#include "elem/poligono.h"

Punto<double> *p = {Punto<double>(0,1)....}; // #n elementos

Poligono<double> poly = Poligono<double>(p, n);    
```

```cpp
// Imprimir en consola
poly.print();
std::cout << poly << std::endl;

// Operaciones geométricas
bool c = poly.inCCW(); // Punto en CCW (Counter clockwise)
poly.addPoint(p); // Añade un punto
T area = poly.area(); // Calcula el área del polígono
T perimetro = poly.perimetro(); // Calcula el perímetro del polígono
bool c = poly.inPoly(p); // Verifica si un punto está dentro del polígono
bool c = poly.isVertex(p); // p vértice del polígono
bool c = poly.mismosPuntos(poly2); // poly y poly2 tienen iguales puntos
```

## Calcular cerradura

Existen dos implementaciones para calcular la cerradura convexa de un polígono: <a href="https://en.wikipedia.org/wiki/Gift_wrapping_algorithm">Gift Wrapping</a> y <a href="https://en.wikipedia.org/wiki/Graham_scan">Graham Scan</a>.

```cpp
#include "utils/cerradura-convexa.h"

Punto<double> *cloud = {Punto<double>(0,1)....}; // #n elementos

// Calcula la cerradura con Gift Wrapping
std::pair<Poligono<double>, int> cerradura = giftWrapping(cloud, n);
Poligono<T> *hull = cerradura.first; // Polígono de la cerradura
int n = cerradura.second; // Total de puntos de la cerradura

// Calcula la cerradura con Graham Scan
std::pair<Poligono<double>, int> cerradura = grahamScan(cloud, n);
Poligono<T> *hull = cerradura.first; // Polígono de la cerradura
int n = cerradura.second; // Total de puntos de la cerradura
```

También es posible obtener las listas de puntos en vez de polígonos haciendo uso de las funciones *privadas*:

```cpp
#include "utils/cerradura-convexa.h"

Punto<double> *cloud = {Punto<double>(0,1)....}; // #n elementos

// Calcula la cerradura con Gift Wrapping
std::pair<Punto<double>, int> cerradura = __giftWrapping(cloud, n);
Punto<T> *hull = cerradura.first; // Polígono de la cerradura
int n = cerradura.second; // Total de puntos de la cerradura

// Calcula la cerradura con Graham Scan
std::pair<Punto<double>, int> cerradura = __grahamScan(cloud, n);
Punto<T> *hull = cerradura.first; // Lista de puntos de la cerradura
int n = cerradura.second; // Total de puntos de la cerradura
```

## Autor
<a href="http://ppizarror.com" title="ppizarror">Pablo Pizarro R.</a> | 2018