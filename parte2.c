/*
EP1 MAC0210
GRUPO: Matheus Sanches Jurgensen e André Nogueira Ribeiro
COMO COMPILAR: gcc -o parte2 parte2.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>


//primeiro teste f(x) = x^4 - 1

double complex evalf (double complex x) {
    // calcula o valor da função f aplicada em x
    return (cpowf(x,4) - 1);
}

double complex evalDf (double complex x) {
    // calcula o valor da derivada da função f aplicada em x
    return (4*cpowf(x,3));
}

double complex newton(double complex x0, double atol, int it) {
    // aplica o método de Newton para achar uma raiz da função f (com primeira
    //derivada f ′), partindo do ponto x0.
    complex anterior;
    complex xk = x0;
    for( int i = 0; i < it; i++){
        do {
            anterior = xk;
            xk = anterior - ( (evalf(anterior))/(evalDf(anterior)) ); 
            // cabs é a norma do numero complexo
        } while (fabs(cabs(xk) - cabs(anterior)) > atol);

        return xk; 
    }
    return(x0);
}

void newton_basins (double* l, double* u, int p, double atol) {
    // acha as bacias de convergência da função f no domínio
    // [l1, u1] × [l2, u2] e gera um arquivo output.txt que contém os dados para a geração
    // da imagem das bacias (pode usar gnuplot para gerar as imagens). Os dados gerados
    // preenchem uma imagem com p1 × p2 pixels.
    double pontos[p][4];
    double tamr, tami, distr, disti, aux;
    double complex z, raiz;
    double real, imag;

    tamr = u[0] - l[0];
    tami = u[1] - l[1];
    distr = tamr/p;
    disti = tami/p;

    double re[p];
    double im[p];

    aux = l[0];
    for(int k = 0; k < p; k++){
        re[k] = aux;
        aux += distr;
    }
    aux = l[1];
    for(int k = 0; k < p; k++){
        im[k] = aux;
        aux += disti;
    }

    for (int i = 0; i < p; i++){
        real = re[i];
        imag = im[i];
        z = CMPLX(real, imag);
        raiz = newton(z, atol, 100);
        if(creal(z) == creal(raiz) && cimag(z) == cimag(raiz)){
            pontos[i][0] = real;
            pontos[i][1] = imag;
            pontos[i][2] = 800; //numero maior q o numero de raizes do polinomio
            pontos[i][3] = 800; //numero maior q o numero de raizes do polinomio
        }
        else{
            pontos[i][0] = real;
            pontos[i][1] = imag;
            pontos[i][2] = creal(raiz);
            pontos[i][3] = cimag(raiz);
        }
    }

    FILE *dados = fopen("gnu_plot.txt" ,"w");

    for (int lin = 0; lin < p; lin++){
        fprintf(dados, "(%.10f,%.10f) (%.10f,%.10f)\n", 
                pontos[lin][0],pontos[lin][1],pontos[lin][2],pontos[lin][3]);
    }
    fclose(dados);
    
}



int main() {
    double atol = 1e-10;
    double real = 2.3, imag = 1.2;
    double complex z = CMPLX(real, imag);
    double r = -1.7, i = -0.3;
    double complex w = CMPLX(r, i);

    double p = 100;
    double l[2] = {-2,-2};
    double u[2] = {2,2};

    newton_basins(l, u, p, atol);
}














