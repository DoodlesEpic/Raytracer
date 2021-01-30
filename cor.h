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

#endif //RAYTRACER_COR_H
