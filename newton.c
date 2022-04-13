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
    //derivada f′), partindo do ponto x0.
    double anterior;
    double xk = x0;
    int contador = 0;
    do {
        anterior = xk;
        xk = anterior - (evalf(anterior) / evalDf(anterior));
        printf("xk-1 : %.10f\n", anterior);
        //printf("xk: %.10f\n", xk);
        contador++;
    } while (((xk - anterior) > atol || (xk - anterior) < -atol) && (contador < 150));
    return xk;
}

void plot (char *end_dados) {
    int pid, status;
    FILE *arq_especificacao;
    char *especificacao = "/tmp/texto_especificacao";
    char *img_bacias = "bacias.png";
    arq_especificacao = fopen(especificacao, "a");
    char* aux = "%lf";
    fprintf(arq_especificacao,  "set term png size 1000, 1200\n"
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
    // double x0,x1; 
    // double atol = 0.0000000001;

    // x0 = -298.12;
    // x1 = newton(x0, atol);
    
    // printf("Raiz 1: %.10f\n", x1);
    char *end_dados = "L96ta3y2.txt";
    plot(end_dados);
}