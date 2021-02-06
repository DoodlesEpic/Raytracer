#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H

#include <limits>
#include <cstdlib>

// Constantes globais
const double infinito = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Helpers globais
inline double grausParaRadianos(double graus) {
    return graus * pi / 180.0;
}

// Retorna um número real em que 0 <= r < 1
inline double doubleAleatorio() {
    return rand() / (RAND_MAX + 1.0);
}

// Retorna um número real em que min <= r < max
inline double doubleAleatorio(double min, double max) {
    return min + (max - min) * doubleAleatorio();
}

// Garante que o valor recebido x estará entre min e max
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif //RAYTRACER_UTIL_H
