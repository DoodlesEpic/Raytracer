#include "cor.h"
#include "raio.h"
#include "vector3.h"

#include <iostream>

double acertouEsfera(const ponto3 &centro, double raioEsfera, const raio &raio) {
    vector3 posicao = raio.getOrigem() - centro;

    // Baskhara
    double a = raio.getDirecao().quadradoComprimento();
    double metadeDeB = dot(posicao, raio.getDirecao());
    double c = posicao.quadradoComprimento() - raioEsfera * raioEsfera;

    // Delta de Baskhara, para descobrir se acertamos a esfera ou não
    double delta = metadeDeB * metadeDeB - a * c;

    // Se delta for maior que 0, há pelo menos uma intersecção com a esfera
    if (delta < 0) {
        return -1.0;
    } else {
        return (-metadeDeB - sqrt(delta)) / a;
    }
}

cor corRaio(const raio &raio) {
    // Caso haja um ponto o raio acerta a esfera, renderizar com cores a partir do normal
    double ponto = acertouEsfera(ponto3(0, 0, -1), 0.7, raio);
    if (ponto > 0.0) {
        vector3 normal = vetorUnitario(raio.em(ponto) - vector3(0, 0, -1));
        return 0.5 * cor(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    // Renderizar backdrop caso não tenho acertado esfera
    vector3 direcaoUnitaria = vetorUnitario(raio.getDirecao());
    ponto = 0.5 * (direcaoUnitaria.y() + 1.0);
    return (1.0 - ponto) * cor(1.0, 1.0, 1.0) + ponto * cor(0.5, 0.7, 1.0);
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