#include "cor.h"
#include "raio.h"
#include "vector3.h"
#include "util.h"
#include "objetosAcertaveis.h"
#include "esfera.h"
#include "camera.h"

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

cor corRaio(const raio &raio, const objetoAcertavel &mundo) {
    acerto acerto;
    if (mundo.acerto(raio, 0, infinito, acerto)) {
        return 0.5 * (acerto.normal + cor(1, 1, 1));
    }

    // Renderizar backdrop caso não tenho acertado esfera
    vector3 direcaoUnitaria = vetorUnitario(raio.getDirecao());
    double ponto = 0.5 * (direcaoUnitaria.y() + 1.0);
    return (1.0 - ponto) * cor(1.0, 1.0, 1.0) + ponto * cor(0.5, 0.7, 1.0);
}

int main(int, char **) {
    // Configuração da tela da imagem
    // Utilizar uma proporção de tela padrão, e inferir a altura a partir da largura
    const double proporcaoTela = 16.0 / 9.0;
    const int larguraImagem = 1280;
    const int alturaImagem = static_cast<int>(larguraImagem / proporcaoTela);

    // Configurar a câmera
    const camera camera;

    // Utilizado para o anti-aliasing
    // Quanto maior, mais lento, mas menos serrilhado
    const int samplesPorPixel = 100;

    // Configuração do mapa
    objetosAcertaveis mundo;
    mundo.adicionar(std::make_shared<esfera>(ponto3(0, 0, -1), 0.5));
    mundo.adicionar(std::make_shared<esfera>(ponto3(4, 4, -9), 1));
    mundo.adicionar(std::make_shared<esfera>(ponto3(0, -100.5, 1), 100));

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
            cor corPixel(0, 0, 0);

            for (int samples = 0; samples < samplesPorPixel; ++samples) {
                // Offsets em espaço UV para posicionar o raio
                // Adicionamos double aleatório para garantir samples diferentes
                // Dessa forma o resultado final não tem "escadinhas"
                // FIXME: Não aleatorizar com apenas 1 sample
                double u = double(i + doubleAleatorio()) / (larguraImagem - 1);
                double v = double(j + doubleAleatorio()) / (alturaImagem - 1);

                // Construir um raio e utilizá-lo para calcular a cor do pixel
                raio raio = camera.getRaio(u, v);

                // Somar a cor do pixel a cor que o raio pegou toda sample
                corPixel += corRaio(raio, mundo);
            }

            // Printar resultado do pixel, garantindo que as cores estão entre 0 e 255
            escreverCor(std::cout, corPixel, samplesPorPixel);
        }
    }

    std::cout << "Imagem finalizada" << std::endl;
}