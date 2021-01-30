#include "cor.h"
#include "raio.h"
#include "vector3.h"

#include <iostream>

bool acertouEsfera(const ponto3 &centro, double raioEsfera, const raio &raio) {
    vector3 posicao = raio.getOrigem() - centro;

    // Baskhara
    double a = dot(raio.getDirecao(), raio.getDirecao());
    double b = 2.0 * dot(posicao, raio.getDirecao());
    double c = dot(posicao, posicao) - raioEsfera * raioEsfera;

    // Delta de Baskhara, para descobrir se acertamos a esfera ou não
    double delta = b * b - 4 * a * c;

    // Se delta for maior que 0, há pelo menos uma intersecção com a esfera
    return (delta > 0);
}

cor corRaio(const raio &raio) {
    // Caso o raio acertar a esfera no ponto z = -1, com raio 0.7, colorir o pixel de vermelho
    if (acertouEsfera(ponto3(0, 0, -1), 0.7, raio)) {
        return cor(0.7, 0.2, 0);
    }

    vector3 direcaoUnitaria = vetorUnitario(raio.getDirecao());
    auto t = 0.5 * (direcaoUnitaria.y() + 1.0);
    return (1.0 - t) * cor(1.0, 1.0, 1.0) + t * cor(0.5, 0.7, 1.0);
}

int main(int, char **) {
    // Configuração da tela da imagem
    // Utilizar uma proporção de tela padrão, e inferir a altura a partir da largura
    const double proporcaoTela = 16.0 / 9.0;
    const int larguraImagem = 1280;
    const int alturaImagem = static_cast<int>(larguraImagem / proporcaoTela);

    // Configuração da câmera
    // Inferir largura da janela a partir da proporção e altura
    double alturaJanela = 2.0;
    double larguraJanela = proporcaoTela * alturaJanela;
    double distanciaFocal = 1.0;

    // Ponto 0, onde estará localizada a câmera
    ponto3 origem = ponto3(0, 0, 0);

    // Vetores representando os eixo da tela, e o canto inferior esquerdo
    vector3 horizontal = vector3(larguraJanela, 0, 0);
    vector3 vertical = vector3(0, alturaJanela, 0);
    vector3 cantoInferiorEsquerdo = origem - horizontal / 2 - vertical / 2 - vector3(0, 0, distanciaFocal);

    // Header da image PPM
    std::cout << "P3" << std::endl
              << larguraImagem << " " << alturaImagem << std::endl
              << "255" << std::endl;

    // Para cada scanline
    for (int j = alturaImagem - 1; j >= 0; --j) {
        // Printar progresso no std:cerr
        std::cerr << "\rScanlines restantes: " << j << ' ' << std::flush;

        // Para cada pixel na scanline
        for (int i = 0; i < larguraImagem; ++i) {
            // Offsets em espaço UV para posicionar o raio
            double u = double(i) / (larguraImagem - 1);
            double v = double(j) / (alturaImagem - 1);

            // Construir um raio e utilizá-lo para calcular a cor do pixel
            raio raio(origem, cantoInferiorEsquerdo + u * horizontal + v * vertical - origem);
            cor corPixel = corRaio(raio);

            // Printar resultado do pixel
            escreverCor(std::cout, corPixel);
        }
    }

    std::cout << "Imagem finalizada" << std::endl;
}