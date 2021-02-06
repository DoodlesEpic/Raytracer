#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "util.h"
#include "raio.h"
#include "vector3.h"

class camera {
public:
    camera() {
        // Configuração da câmera
        // Inferir largura da janela a partir da proporção e altura
        double proporcao = 16.0 / 9.0;
        double alturaJanela = 2.0;
        double larguraJanela = proporcao * alturaJanela;
        double distanciaFocal = 1.0;

        // Ponto 0, onde estará localizada a câmera
        origem = ponto3(0, 0, 0);

        // Vetores representando os eixo da tela, e o canto inferior esquerdo
        horizontal = vector3(larguraJanela, 0.0, 0.0);
        vertical = vector3(0.0, alturaJanela, 0.0);
        cantoInferiorEsquerdo = origem - horizontal / 2 - vertical / 2 - vector3(0, 0, distanciaFocal);
    }

    raio getRaio(double u, double v) const {
        return raio(origem, cantoInferiorEsquerdo + u * horizontal + v * vertical - origem);
    }

private:
    ponto3 origem;
    ponto3 cantoInferiorEsquerdo;
    vector3 horizontal;
    vector3 vertical;
};


#endif //RAYTRACER_CAMERA_H
