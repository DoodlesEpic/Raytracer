#ifndef RAYTRACER_OBJETOACERTAVEL_H
#define RAYTRACER_OBJETOACERTAVEL_H

#include "raio.h"

struct acerto {
    ponto3 ponto;
    vector3 normal;
    double t;
    bool faceFrontal;

    inline void definirNormalDaFace(const raio &raio, const vector3 &normalParaFora) {
        faceFrontal = produtoEscalar(raio.getDirecao(), normalParaFora) < 0;
        normal = faceFrontal ? normalParaFora : -normalParaFora;
    }
};

class objetoAcertavel {
public:
    virtual bool acerto(const raio &raio, double tMin, double tMax, acerto &acerto) const = 0;
};


#endif //RAYTRACER_OBJETOACERTAVEL_H
