// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef INTERVALOTIM_H
#define INTERVALOTIM_H

#include <stdint.h>
#include <fenv.h>
#include <float.h>
#include <math.h>

typedef struct intervalo {
    double inicio;
    double fim;
}intervalo_t;

typedef struct intervaloA{
    double *inicio;
    double *fim;
}intervaloA_t;

void adicionaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void subtraiIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void multiplicaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void divideIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void potenciaIntervalo(double inicio, double fim, int expoente, double *resini, double *resfim);

void calculaIntervalo (double inicio, double *fim);

#endif // INTERVALOTIM_H