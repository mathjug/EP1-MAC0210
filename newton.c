#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//primeiro teste f(x) = x^3 - 1

double evalf (double x) {
    // calcula o valor da função f aplicada em x
    return (pow(x,3) - 1);
}

double evalDf (double x) {
    // calcula o valor da derivada da função f aplicada em x
    return (3*pow(x,2));
}

double newton (double x0, double atol) {
    // aplica o método de Newton para achar uma raiz da função f (com primeira
    //derivada f ′), partindo do ponto x0.
    double anterior;
    double xk = x0;
    do {
        anterior = xk;
        xk = anterior - (evalf(anterior) / evalDf(anterior));
        printf("xk-1 : %.10f\n", anterior);
        //printf("xk: %.10f\n", xk);
    } while ((xk - anterior) > atol || (xk - anterior) < -atol);
    return xk;
}

int main() {
    double x0,x1; 
    double atol = 0.0000000001;

    x0 = -298.12;
    x1 = newton(x0, atol);
    
    printf("Raiz 1: %.10f\n", x1);
}