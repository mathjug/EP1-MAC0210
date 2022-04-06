/*
EP1 MAC0210
GRUPO: Matheus Sanches Jurgensen e André Nogueira
COMO COMPILAR: gcc -o EP1 EP1.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double g1 (double x) {
    // g1(x) = x + x²/2 - e^x/4
    // Converge para as raízes x1 = -0.539836 e x3 = 2.617866
    return (x + (pow(x, 2)/2) - (exp(x)/4));
}

double g2 (double x) {
    // g2(x) = (e^x)/(2x)
    // Converge para a raiz x2 = 1.487962
    return ((exp(x)) / (2*x));
}

double ponto_fixo1 (double x0, double atol) {
    // Implementa o método do ponto fixo para a função g1(x)
    double anterior;
    double xk = x0;
    do {
        anterior = xk;
        xk = g1(xk);
    } while ((xk - anterior) > atol || (xk - anterior) < -atol);
    return xk;
}

double ponto_fixo2 (double x0, double atol) {
    // Implementa o método do ponto fixo para a função g2(x)
    double anterior;
    double xk = x0;
    do {
        anterior = xk;
        xk = g2(xk);
    } while ((xk - anterior) > atol || (xk - anterior) < -atol);
    return xk;
}

int main() {
    double x0[3] = {-1, 1, 3}; // pontos iniciais
    double atol = 0.0000000001;
    double x1 = ponto_fixo1(x0[0], atol);
    double x2 = ponto_fixo2(x0[1], atol);
    double x3 = ponto_fixo1(x0[2], atol);
    printf("Raiz 1: %.10f\nRaiz 2: %.10f\nRaiz 3: %.10f\n", x1, x2, x3);
}