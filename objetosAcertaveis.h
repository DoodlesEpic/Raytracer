#ifndef RAYTRACER_OBJETOSACERTAVEIS_H
#define RAYTRACER_OBJETOSACERTAVEIS_H

#include "objetoAcertavel.h"

#include <memory>
#include <vector>

// A lista de objetos acertáveis também será um objeto acertável
// Sendo assim um raio pode acertar a lista de objetos acertáveis
// Uma abstração por cima de um vetor de objetos
class objetosAcertaveis : public objetoAcertavel {
public:
    objetosAcertaveis() {}

    objetosAcertaveis(std::shared_ptr<objetoAcertavel> objeto) {
        adicionar(objeto);
    }

    // Remover todos os objetos acertáveis
    void limpar() { objetos.clear(); }

    // Adicionar um objeto para a lista de acertáveis
    void adicionar(std::shared_ptr<objetoAcertavel> objeto) {
        objetos.push_back(objeto);
    }

    // Altera acerto para ser o objeto acertado mais próximo
    // Retorna se acertou um objeto ou não
    bool acerto(const raio &raio, double tMin, double tMax, acerto &acerto) const override;

public:
    std::vector<std::shared_ptr<objetoAcertavel>> objetos;
};

// Altera acerto para ser o objeto acertado mais próximo
// Retorna se acertou um objeto ou não
bool objetosAcertaveis::acerto(const raio &raio, double tMin, double tMax, acerto &acerto) const {
    acerto acertoTemporario;
    bool acertouAlgo = false;
    double acertoMaisProximo = tMax;

    for (const auto &objeto : objetos) {
        if (objeto->acerto(raio, tMin, acertoMaisProximo, acertoTemporario)) {
            acertouAlgo = true;
            acertoMaisProximo = acertoTemporario.t;
            acerto = acertoTemporario;
        }
    }

    return acertouAlgo;
}

#endif //RAYTRACER_OBJETOSACERTAVEIS_H
