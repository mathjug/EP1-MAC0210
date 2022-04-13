#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

complex mulc(complex a, complex b){
    double ra,ia,rb,ib,rz,iz;
    complex z;
    ra = creal(a);
    ia = cimag(a);
    rb = creal(b);
    ib = cimag(b);

    printf("%f, %f, %f, %f\n", ra,ia,rb,ib);
    rz = (ra*rb - ia*ib);
    iz = (ra*ib + ia*rb);
    printf("%f, %f\n", rz,iz);

    z = CMPLX(rz,iz);
    return(z);
}

int main(){
    double real = 2.3, imag = 1.2;
    double complex z = CMPLX(real, imag);
    printf("z = %.1f + %.1fi\n",creal(z), cimag(z));

    double complex e = cpowf(z,3);
    printf("e = %.3f + %.3fi\n",creal(e), cimag(e));

    double r = -1.7, i = -0.3;
    double complex w = CMPLX(r, i);
    double complex m = mulc(z,w);
    printf("m = %.5f + %.5fi\n",creal(m), cimag(m));

    r = -1.2;
    i = 0.3;
    double complex u = CMPLX(r, i);
    double complex ms = 3*u;
    printf("ms = %.5f + %.5fi\n",creal(ms), cimag(ms));

    complex t = z*w;
    printf("t = %.5f + %.5fi\n",creal(t), cimag(t));

    printf("modulo(t) = %.5f\n",cabs(t));
}
