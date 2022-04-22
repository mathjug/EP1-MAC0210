/*
EP1 MAC0210 PARTE 1
GRUPO:  Andre Nogueira Ribeiro nUSP: 12542230
        Matheus Sanches Jurgensen nUSP: 12542199
COMO COMPILAR: gcc -o EP1 EP1.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double g1 (double x) {
    /*
    g1(x) = x + x²/2 - e^x/4
    Converge para as raízes x1 = -0.539836 e x3 = 2.617866
    */
    return (x + (x*x/2) - (exp(x)/4));
}

double g2 (double x) {
    /*
    g2(x) = (e^x)/(2x)
    Converge para a raiz x2 = 1.487962
    */
    return ((exp(x)) / (2*x));
}

double ponto_fixo1 (double x0, double atol) {
    /*
    Implementa o método do ponto fixo para a função g1(x)
    */
    double anterior;
    double xk = x0;
    int contador = 0;
    do {
        anterior = xk;
        xk = g1(xk);
        contador++;
    } while ((fabs(xk - anterior) > atol) && (contador < 500) && (!isnan(xk)));
    if (isnan(xk)) printf("\nDurante as iterações, valores tenderam ao infinito.");
    printf("\nNúmero de iterações: %d\n", contador);
    return xk;
}

double ponto_fixo2 (double x0, double atol) {
    /*
    Implementa o método do ponto fixo para a função g2(x)
    */
    double anterior;
    double xk = x0;
    int contador = 0;
    do {
        anterior = xk;
        xk = g2(xk);
        contador++;
    } while ((fabs(xk - anterior) > atol) && (contador < 500) && (!isnan(xk)));
    if (isnan(xk)) printf("\nDurante as iterações, valores tenderam ao infinito.");
    printf("\nNúmero de iterações: %d\n", contador);
    return xk;
}

int main() {
    int funcao;
    double x0, x1;
    double atol = 1e-7;
    printf("A partir de qual ponto você quer executar o método do ponto fixo? ");
    scanf("%lf", &x0);
    printf("\nEscolha uma das seguintes funções para executar o método:\n");
    printf("1. g1(x) = x + x²/2 - e^x/4\n2. g2(x) = (e^x)/(2x)\n");
    do {
        printf("\nSua escolha: ");
        scanf("%d", &funcao);
    } while (funcao != 1 && funcao != 2);
    if (funcao == 1) x1 = ponto_fixo1(x0, atol);
    else x1 = ponto_fixo2(x0, atol);
    if (isnan(x1) || isinf(x1)) printf("A partir da função e do ponto dados, o método do ponto fixo não convergiu para uma raiz.\n");
    else printf("A partir da função e do ponto dados, o método do ponto fixo convergiu para a raiz x = %lf.\n", x1);
}