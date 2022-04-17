/*
EP1 MAC0210 PARTE 2
GRUPO: Matheus Sanches Jurgensen e André Nogueira Ribeiro
COMO COMPILAR: gcc -o parte2 parte2.c -lm -w
*/

// PROBLEMAS:
// - ESTÁ PINTANDO CASOS EM QUE RETORNA NaN?

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double complex evalf1 (double complex x) {
    /*
    Calcula o valor da função f1(x) = x⁴ - 1 no ponto x
    RAÍZES: 1, -1, i, -i
    l[2] = {-2,-2}
    u[2] = {2,2}
    */
    return (cpowf(x,4) - 1);
}

double complex evalDf1 (double complex x) {
    /*
    Calcula o valor da derivada da função f1(x) = x⁴ - 1 no ponto x
    */
    return (4*cpowf(x,3));
}

double complex evalf2 (double complex x) {
    /*
    Calcula o valor da função f2(x) = x³ - 1 no ponto x
    RAÍZES: 1, -0.5 - (sqrt(3)i/2), -0.5 + (sqrt(3)i/2)
    l[2] = {-2,-2}
    u[2] = {2,2}
    */
    return (cpowf(x,3) - 1);
}

double complex evalDf2 (double complex x) {
    /*
    Calcula o valor da derivada da função f2(x) = x³ - 1 no ponto x
    */
    return (3*cpowf(x,2));
}

double complex evalf3 (double complex x) {
    /*
    Calcula o valor da função f3(x) = x³ - 2x² + 25x - 50 no ponto x
    RAÍZES: 2, -5i, 5i
    l[2] = {-5,-5}
    u[2] = {5,5}
    */
    return (cpowf(x,3) - 2*cpowf(x,2) + 25*x - 50);
}

double complex evalDf3 (double complex x) {
    /*
    Calcula o valor da derivada da função f3(x) = 3x² - 4x + 25 no ponto x
    */
    return (3*cpowf(x,2) - 4*x + 25);
}

double complex evalf4 (double complex x) {
    /*
    Calcula o valor da função f4(x) = x⁵ - 4x⁴ + 10x³ + x² - 10 no ponto x
    l[2] = {-5,-5}
    u[2] = {5,5}
    */
    return (cpowf(x,5) - 4*cpowf(x,4) + 10*cpowf(x,3) + cpowf(x,2) - 10);
}

double complex evalDf4 (double complex x) {
    /*
    Calcula o valor da derivada da função f4(x) = x⁵ - 4x⁴ + 10x³ + x² - 10 no ponto x
    */
    return (5*cpowf(x,4) - 16*cpowf(x,3) + 30*cpowf(x,2) + 2*x);
}

double complex newton (double complex x0, double atol) {
    /*
    Aplica o método de Newton para achar uma raiz da função f (com primeira derivada f'), partindo do ponto x0.
    */
    complex anterior, df;
    complex xk = x0;
    int contador = 0;
    do {
        anterior = xk;
        df = evalDf4(anterior);
        if (creal(df) == 0 && cimag(df) == 0) break;
        xk = anterior - ((evalf4(anterior))/(df)); 
        contador++;
    } while ((fabs(cabs(xk) - cabs(anterior)) > atol) && (contador < 150)); // cabs é a norma do numero complexo
    
    if (fabs(cabs(xk) - cabs(anterior)) < atol || contador >= 150) return(xk);
    else return(x0);
}

char *newton_basins (double* l, double* u, int p, double atol) {
    /*
    Acha as bacias de convergência da função f no domínio [l1, u1] × [l2, u2] e retorna um arquivo output.txt que
    contém os dados para a geração da imagem das bacias. Os dados gerados preenchem uma imagem com p × p pixels.
    */
    double real, imag;
    double complex z, raiz;
    double tamr = u[0] - l[0];
    double tami = u[1] - l[1];
    double distr = tamr/p;
    double disti = tami/p;
    char *saida = "output.txt";
    FILE *dados = fopen(saida ,"w");
    for (int i = 0; i < p; i++) {
        real = l[0] + distr * i;
        for (int j = 0; j < p; j++) {
            imag = l[1] + disti * j;
            z = CMPLX(real, imag);
            raiz = newton(z, atol);
            fprintf(dados, "(%.10f,%.10f) (%.6f,%.6f)\n", real, imag, creal(raiz), cimag(raiz));
        }
    }
    fclose(dados);
    return saida;
}

void plot (char *end_dados) {
    int pid, status;
    FILE *arq_especificacao;
    char *especificacao = "/tmp/texto_especificacao";
    char *img_bacias = "bacias.png";
    arq_especificacao = fopen(especificacao, "a");
    char* aux = "%lf";
    fprintf(arq_especificacao,  "set term png size 1000, 1000\n"
                                "set output '%s'\n"
                                "plot \"%s\" using 2:1:(arg($3+$4*{0,1})) '(%s,%s) (%s,%s)' palette", img_bacias, end_dados, aux, aux, aux, aux);
    fclose(arq_especificacao);

    // chamada do execvp
    char *args[] = { "gnuplot", "-p -e", especificacao, NULL };
    if((pid = (fork())) < 0) {
        fprintf(stderr, "Erro de fork().\n");
        return;
    }
    else if(pid == 0) {
        if(execvp(*args, args) == -1) {
        fprintf(stderr, "Erro de execvp().\n");
        _exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    remove(especificacao);
}

int main() {
    double atol = 1e-10;
    double p = 1000;
    double l[2] = {-5,-5};
    double u[2] = {5,5};
    char* output = newton_basins(l, u, p, atol);
    plot(output);
}
