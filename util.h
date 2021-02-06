#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H

#include <limits>

// Constantes globais
const double infinito = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Helpers globais
inline double grausParaRadianos(double graus) {
    return graus * pi / 180.0;
}

#endif //RAYTRACER_UTIL_H
