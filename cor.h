#ifndef RAYTRACER_COR_H
#define RAYTRACER_COR_H

#include "vector3.h"
#include "raio.h"
#include "util.h"
#include <iostream>

void escreverCor(std::ostream &out, cor corPixel, const int samplesPorPixel) {
    const double escala = 1.0 / samplesPorPixel;

    // Pegar a cor de cada pixel, dividindo pela escala
    // Realizar correção de gamma para gamma 2
    const double r = sqrt(corPixel.x() * escala);
    const double g = sqrt(corPixel.y() * escala);
    const double b = sqrt(corPixel.z() * escala);

    // Escrever as cores mapeadas entre 0 <= cor < 1
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif //RAYTRACER_COR_H
