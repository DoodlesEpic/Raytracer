#ifndef RAYTRACER_COR_H
#define RAYTRACER_COR_H

#include "vector3.h"
#include "raio.h"
#include <iostream>

void escreverCor(std::ostream &out, cor corPixel) {
    out << static_cast<int>(255.999 * corPixel.x()) << ' '
        << static_cast<int>(255.999 * corPixel.y()) << ' '
        << static_cast<int>(255.999 * corPixel.z()) << '\n';
}

cor corRaio(const raio &raio) {
    vector3 direcaoUnitaria = vetorUnitario(raio.getDirecao());
    auto t = 0.5 * (direcaoUnitaria.y() + 1.0);
    return (1.0 - t) * cor(1.0, 1.0, 1.0) + t * cor(0.5, 0.7, 1.0);
}

#endif //RAYTRACER_COR_H
