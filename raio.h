#ifndef RAYTRACER_RAIO_H
#define RAYTRACER_RAIO_H

#include "vector3.h"

// O raio base para nosso raytracer
class raio {
public:
    raio() = default;

    raio(const ponto3 &novaOrigem, const vector3 &novaDirecao)
            : origem(novaOrigem), direcao(novaDirecao) {}

    const ponto3 &getOrigem() const {
        return origem;
    }

    const vector3 &getDirecao() const {
        return direcao;
    }

    // Retorna a posição no raio de acordo com o offset
    ponto3 em(double offset) const {
        return origem + offset * direcao;
    }

private:
    ponto3 origem;
    vector3 direcao;
};

#endif //RAYTRACER_RAIO_H
