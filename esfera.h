#ifndef RAYTRACER_ESFERA_H
#define RAYTRACER_ESFERA_H

#include "objetoAcertavel.h"
#include "vector3.h"

class esfera : public objetoAcertavel {
public:
    esfera() {}

    esfera(ponto3 centro, double raio) : centro(centro), raio(raio) {};

    virtual bool acerto(const raio &raio, double tMin, double tMax, acerto &acerto) const override;

public:
    ponto3 centro;
    double raio;
};

bool esfera::acerto(const raio &raio, double tMin, double tMax, struct acerto &acerto) const {
    vetor3 posicao = raio.getOrigem() - centro;

    // Baskhara
    double a = raio.getDirecao().quadradoComprimento();
    double metadeDeB = dot(posicao, raio.getDirecao());
    double c = posicao.quadradoComprimento() - raioEsfera * raioEsfera;

    // Delta de Baskhara, para descobrir se acertamos a esfera ou não
    double delta = metadeDeB * metadeDeB - a * c;

    // Se delta for maior que 0, há pelo menos uma intersecção com a esfera
    if (delta < 0) {
        return false;
    }

    // Encontrar o ponto mais próximo
    // Garantir que esteja entre tMin e tMax
    double raizQuadradaDelta = sqrt(delta)
    double raiz = (-metadeDeB - raizQuadradaDelta) / a;
    if (raiz < tMin || tMax < raiz) {
        raiz = (-metadeDeB + raizQuadradaDelta) / a;
        if (raiz < tMin || tMax < raiz) {
            return false;
        }
    }

    // Atualizar a estrutura de acerto
    // (Talvez mudar isso pelo amor)
    acerto.t = raiz;
    acerto.ponto = raiz.em(acerto.t);
    acerto.normal = (acerto.ponto - centro) / raio;

    return true;
}

#endif //RAYTRACER_ESFERA_H
