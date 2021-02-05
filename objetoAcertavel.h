#ifndef RAYTRACER_OBJETOACERTAVEL_H
#define RAYTRACER_OBJETOACERTAVEL_H

#include "raio.h"

struct acerto {
    ponto3 ponto;
    vector3 normal;
    double t;
};

class objetoAcertavel {
public:
    virtual bool acerto(const raio &raio, double tMin, double tMax, acerto &acerto) const = 0;
};


#endif //RAYTRACER_OBJETOACERTAVEL_H
