#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>


//primeiro teste f(x) = x^2 + 1

complex evalf (complex x) {
    // calcula o valor da função f aplicada em x
    complex z = cpowf(x,2) + 1;
    //printf("f(x) = %.10f + %.10fi\n",creal(z), cimag(z));
    return (z);
}

complex evalDf (complex x) {
    // calcula o valor da derivada da função f aplicada em x
    complex z = 2*cpowf(x,1);
    //printf("df(x) = %.10f + %.10fi\n",creal(z), cimag(z));
    return (z);
}

complex newton (complex x0, double atol) {
    // aplica o método de Newton para achar uma raiz da função f (com primeira
    //derivada f ′), partindo do ponto x0.
    complex f;
    complex anterior;
    complex xk = x0;
    printf("x0 = %.10f + %.10fi\n",creal(xk), cimag(xk));
    do {
        anterior = xk;
        xk = anterior - ( (evalf(anterior))/(evalDf(anterior)) );
        
        printf("xk = %.10f + %.10fi\n",creal(xk), cimag(xk));
        
        // cabs é a norma do numero complexo
        //printf("cabs = %.10f \n", fabs(cabs(xk) - cabs(anterior)) );

    } while (fabs(cabs(xk) - cabs(anterior)) > atol);

    printf("\nxk = %.10f + %.10fi\n",creal(xk), cimag(xk));
    return xk;
}

int main() {
    double complex x0,x1; 
    double atol = 0.0000000001;
    double r = 0.5, i = -1;
    x0 = CMPLX(r, i);

    x1 = newton(x0, atol);
    
    printf("\nx1 = %.5f + %.5fi\n",creal(x1), cimag(x1));
    
}