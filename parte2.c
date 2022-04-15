/*
EP1 MAC0210 PARTE 2
GRUPO: Matheus Sanches Jurgensen e André Nogueira Ribeiro
COMO COMPILAR: gcc -o parte2 parte2.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double complex evalf1 (double complex x) {
    /*
    Calcula o valor da função f1(x) = x⁴ - 1 no ponto x
    */
    return (cpowf(x,4) - 1);
}

double complex evalf2 (double complex x) {
    /*
    Calcula o valor da função f2(x) = x³ - 1 no ponto x
    */
    return (cpowf(x,3) - 1);
}

double complex evalf3 (double complex x) {
    /*
    Calcula o valor da função f3(x) = x⁵ - 1 no ponto x
    */
    return (cpowf(x,5) - 1);
}

double complex evalDf1 (double complex x) {
    /*
    Calcula o valor da derivada da função f1(x) = x⁴ - 1 no ponto x
    */
    return (4*cpowf(x,3));
}

double complex evalDf2 (double complex x) {
    /*
    Calcula o valor da derivada da função f2(x) = x³ - 1 no ponto x
    */
    return (3*cpowf(x,2));
}

double complex evalDf3 (double complex x) {
    /*
    Calcula o valor da derivada da função f3(x) = x⁵ - 1 no ponto x
    */
    return (5*cpowf(x,4));
}

double complex newton (double complex x0, double atol, int it) {
    /*
    Aplica o método de Newton para achar uma raiz da função f (com primeira derivada f'), partindo do ponto x0.
    */
    complex anterior;
    complex xk = x0;
    int contador = 0;
    for (int i = 0; i < it; i++){
        do {
            anterior = xk;
            xk = anterior - ((evalf1(anterior))/(evalDf1(anterior)));
            contador++;
        } while ((fabs(cabs(xk) - cabs(anterior)) > atol) && (contador < 150)); // cabs é a norma do numero complexo
        return xk; 
    }
    return(x0);
}

char *newton_basins (double* l, double* u, int p, double atol) {
    /*
    Acha as bacias de convergência da função f no domínio [l1, u1] × [l2, u2] e retorna um arquivo output.txt que
    contém os dados para a geração da imagem das bacias. Os dados gerados preenchem uma imagem com p × p pixels.
    */
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

    char *saida = "output.txt";
    FILE *dados = fopen(saida ,"w");
    for (int i = 0; i < p; i++){
        real = re[i];
        for (int j = 0; j < p; j++){
            imag = im[j];
            z = CMPLX(real, imag);
            raiz = newton(z, atol, 100);
            if(creal(z) == creal(raiz) && cimag(z) == cimag(raiz)) {
                fprintf(dados, "(%.10f,%.10f) (%.10f,%.10f)\n", real, imag, 800, 800);
                // 800 é número maior que o número de raízes do polinômio
            }
            else
                fprintf(dados, "(%.10f,%.10f) (%.10f,%.10f)\n", real, imag, creal(raiz), cimag(raiz));
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
    double l[2] = {-2,-2};
    double u[2] = {2,2};
    char* output = newton_basins(l, u, p, atol);
    plot(output);
}














