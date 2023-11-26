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

#define ADICIONA_INTERVALO(inicio1, fim1, inicio2, fim2, resini, resfim) \
    do { \
        fesetround(FE_DOWNWARD); \
        *(resini) = (inicio1) + (inicio2); \
        fesetround(FE_UPWARD); \
        *(resfim) = (fim1) + (fim2); \
    } while (0)
#define SUBTRAI_INTERVALO(inicio1, fim1, inicio2, fim2, resini, resfim) \
    do { \
        fesetround(FE_DOWNWARD); \
        *(resini) = (inicio1) - (fim2); \
        fesetround(FE_UPWARD); \
        *(resfim) = (fim1) - (inicio2); \
    } while (0)

#define MULTIPLICA_INTERVALO(inicio1, fim1, inicio2, fim2, resini, resfim) \
    do { \
        fesetround(FE_DOWNWARD); \
        double e = (inicio1) * (inicio2); \
        double f = (inicio1) * (fim2); \
        double c = (fim1) * (inicio2); \
        double d = (fim1) * (fim2); \
        *(resini) = fmin(fmin(e, f), fmin(c, d)); \
        fesetround(FE_UPWARD); \
        e = (inicio1) * (inicio2); \
        f = (inicio1) * (fim2); \
        c = (fim1) * (inicio2); \
        d = (fim1) * (fim2); \
        *(resfim) = fmax(fmax(e, f), fmax(c, d)); \
    } while (0)

#define DIVIDE_INTERVALO(inicio1, fim1, inicio2, fim2, resini, resfim) \
    do { \
        fesetround(FE_DOWNWARD); \
        double e = (inicio1) / (inicio2); \
        double f = (inicio1) / (fim2); \
        double c = (fim1) / (inicio2); \
        double d = (fim1) / (fim2); \
        *(resini) = fmin(fmin(e, f), fmin(c, d)); \
        fesetround(FE_UPWARD); \
        e = (inicio1) / (inicio2); \
        f = (inicio1) / (fim2); \
        c = (fim1) / (inicio2); \
        d = (fim1) / (fim2); \
        *(resfim) = fmax(fmax(e, f), fmax(c, d)); \
    } while (0)

#define POTENCIA_INTERVALO(inicio, fim, expoente, resini, resfim) \
    do { \
        fesetround(FE_DOWNWARD); \
        *(resini) = CALCULA_POTENCIA((inicio), (expoente)); \
        fesetround(FE_UPWARD); \
        *(resfim) = CALCULA_POTENCIA((fim), (expoente)); \
    } while (0)


#define CALCULA_INTERVALO(inicio, fim) \
    do { \
        (*(fim)) = nextafter((inicio), DBL_MAX); \
    } while (0)


void adicionaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void subtraiIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void multiplicaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void divideIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim);

void potenciaIntervalo(double inicio, double fim, int expoente, double *resini, double *resfim);

void calculaIntervalo (double inicio, double *fim);

#endif // INTERVALOTIM_H