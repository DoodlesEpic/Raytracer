#ifndef RAYTRACER_COR_H
#define RAYTRACER_COR_H

#include "vector3.h"
#include "raio.h"
#include "util.h"
#include <iostream>

void escreverCor(std::ostream &out, cor corPixel, const int samplesPorPixel) {
    const double escala = 1.0 / samplesPorPixel;

    // Pegar a cor de cada pixel, multiplicando pela escala
    const double r = corPixel.x() * escala;
    const double g = corPixel.y() * escala;
    const double b = corPixel.z() * escala;

    // Escrever as cores mapeadas entre 0 <= cor < 1
    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif //RAYTRACER_COR_H
