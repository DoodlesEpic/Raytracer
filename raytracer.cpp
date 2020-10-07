#include <iostream>

int main()
{
    const unsigned int larguraImagem = 1000;
    const unsigned int alturaImagem = 1000;

    // Header da image PPM
    std::cout << "P3" << std::endl
              << larguraImagem << " " << alturaImagem << std::endl
              << "255" << std::endl;

    // Para cada scanline
    for (unsigned int j = alturaImagem - 1; j > 0; j--)
    {
        // Printar progresso no std:cerr
        std::cerr << "\rScanlines restantes: " << j << ' ' << std::flush;

        // Para cada pixel na scanline
        for (unsigned int i = 0; i < larguraImagem; i++)
        {
            // Calcular valores RGB de 0 a 1 para o pixel
            const float r = float(i) / float(larguraImagem);
            const float g = float(j) / float(alturaImagem);
            const float b = float(j) / ((float(larguraImagem) + float(alturaImagem)) / 2);

            // Mapear os valores até 255
            const unsigned int ir = int(255.99 * r);
            const unsigned int ig = int(255.99 * g);
            const unsigned int ib = int(255.99 * b);

            // Printar resultado do pixel
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}