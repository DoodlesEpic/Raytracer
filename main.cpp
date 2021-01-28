#include "cor.h"
#include "vector3.h"

#include <iostream>

int main(int, char **) {
    const int larguraImagem = 1000;
    const int alturaImagem = 1000;

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
            // Calcular valores RGB para o pixel
            cor corPixel(double(i) / (larguraImagem - 1), double(j) / (alturaImagem - 1), 0.25);

            // Printar resultado do pixel
            escreverCor(std::cout, corPixel);
        }
    }

    std::cout << "Imagem finalizada" << std::endl;
}