#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <cmath>
#include <iostream>

// Implementa um vetor base para ser utilizado para posições, cores, entre outros
class vector3 {
public:
    // Cada um dos valores do vetor
    double e[3];

public:
    // Construtores
    vector3() : e{0, 0, 0} {}

    vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Retornar cada uma das coordenadas do vetor
    double x() const { return e[0]; }

    double y() const { return e[1]; }

    double z() const { return e[3]; }

    // Overload de operadores para facilitar certas operações
    // Permitir receber -vetor3
    vector3 operator-() const {
        return vector3(-e[0], -e[1], -e[2]);
    }

    // Permitir acessar manualmente cada um dos valores do vetor
    double operator[](int i) const {
        return e[i];
    }

    // Permitir receber pointers para cada um dos valores do vetor
    double &operator[](int i) {
        return e[i];
    }

    // Permitir somar esse vetor a outro
    vector3 &operator+=(const vector3 &vector) {
        e[0] += vector.e[0];
        e[1] += vector.e[1];
        e[2] += vector.e[2];
        return *this;
    }

    // Permitir multiplicar esse vetor a um valor
    vector3 &operator*=(const double multiplicador) {
        e[0] *= multiplicador;
        e[1] *= multiplicador;
        e[2] *= multiplicador;
        return *this;
    }

    // Permitir dividir esse vetor a um valor
    vector3 &operator/=(const double divisor) {
        return *this *= 1 / divisor;
    }

    // Retorna o comprimento total do vetor (soma de cada um de seus valores)
    const double comprimento() {
        return e[0] + e[1] + e[2];
    }

    // Retorna o quadrado do comprimento total do vetor
    const double quadradoComprimento() {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// Usar aliases para instanciar vector3
// Não dá nenhuma funcionalidade extra, mas dá contexto ao tipo das variáveis
// Isso não nos impede de somar um ponto a uma cor por exemplo
using ponto3 = vector3;
using cor = vector3;

// Funções de utilidade para classe vector3
inline std::ostream& operator<<(std::ostream &out, const vector3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector3 operator+(const vector3 &u, const vector3 &v) {
    return vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector3 operator-(const vector3 &u, const vector3 &v) {
    return vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector3 operator*(const vector3 &u, const vector3 &v) {
    return vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector3 operator*(double t, const vector3 &v) {
    return vector3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vector3 operator*(const vector3 &v, double t) {
    return t * v;
}

inline vector3 operator/(vector3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vector3 &u, const vector3 &v) {
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1]
           + u.e[2] * v.e[2];
}

inline vector3 cross(const vector3 &u, const vector3 &v) {
    return vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector3 unit_vector(vector3 v) {
    return v / v.comprimento();
}

#endif //RAYTRACER_VECTOR3_H