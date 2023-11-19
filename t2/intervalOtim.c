#include <stdint.h>
#include <fenv.h>
#include <float.h>
#include "intervalOtim.h"
#include "utilsOtim.h"

void inline adicionaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim) {
    fesetround(FE_DOWNWARD);
    *resini = inicio1 + inicio2;
    fesetround(FE_UPWARD);
    *resfim = fim1 + fim2;
}

void inline subtraiIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim) {
    fesetround(FE_DOWNWARD);
    *resini = inicio1 - fim2;
    fesetround(FE_UPWARD);
    *resfim = fim1 - inicio2;
}

void inline multiplicaIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim) {
    fesetround(FE_DOWNWARD);
    double e = inicio1 * inicio2;
    double f = inicio1 * fim2;
    double c = fim1 * inicio2;
    double d = fim1 * fim2;
    *resini = fmin(fmin(e, f), fmin(c, d));
    fesetround(FE_UPWARD);
    e = inicio1 * inicio2;
    f = inicio1 * fim2;
    c = fim1 * inicio2;
    d = fim1 * fim2;
    *resfim = fmax(fmax(e, f), fmax(c, d));
}

void inline divideIntervalo (double inicio1, double fim1, double inicio2, double fim2, double *resini, double *resfim) {
    fesetround(FE_DOWNWARD);
    double e = inicio1 / inicio2;
    double f = inicio1 / fim2;
    double c = fim1 / inicio2;
    double d = fim1 / fim2;
    *resini = fmin(fmin(e, f), fmin(c, d));
    fesetround(FE_UPWARD);
    e = inicio1 / inicio2;
    f = inicio1 / fim2;
    c = fim1 / inicio2;
    d = fim1 / fim2;
    *resfim = fmax(fmax(e, f), fmax(c, d));
}

void inline potenciaIntervalo(double inicio, double fim, int expoente, double *resini, double *resfim){
    fesetround(FE_DOWNWARD);
    *resini = calculaPotencia(inicio, expoente);
    fesetround(FE_UPWARD);
    *resfim = calculaPotencia(fim, expoente);
}

void inline calculaIntervalo (double inicio, double *fim){
    (*fim) = nextafter(inicio, DBL_MAX);
}