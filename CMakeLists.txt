# Propiedades del make
cmake_minimum_required(VERSION 3.10)
project(LIB-CC5502-1)
set(CMAKE_CXX_STANDARD 11)

# Testing
add_executable(TEST-POLIGONO tests/test-poligono.cpp elem/poligono.h)
add_executable(TEST-PUNTO tests/test-punto.cpp elem/punto.h)
add_executable(TEST-SEGMENTO tests/test-segmento.cpp elem/segmento.h)
add_executable(TEST-VECTOR tests/test-vector.cpp elem/vector.h)
add_executable(TEST-CERRADURA-CONVEXA tests/test-cerradura-convexa.cpp utils/cerradura-convexa.h)