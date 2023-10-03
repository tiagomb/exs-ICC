#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "sistemas.h"
#include "utils.h"
#include <fenv.h>
#include <likwid.h>

int main (){
    int n, k, i;
    double **x, **y, ***a, **b, **somas, **coef;
    fesetround (FE_DOWNWARD);
    scanf ("%d", &n);
    scanf ("%d", &k);
    x = malloc (k * sizeof (double *));
    y = malloc (k * sizeof (double *));
    for (int i = 0; i < k; i++){
        x[i] = malloc (2 * sizeof (double));
        y[i] = malloc (2 * sizeof (double));
    }
    somas = malloc ((2*(n+1) - 1) * sizeof (double *));
    for (int i = 0; i < 2*(n+1) - 1; i++){
        somas[i] = malloc (2 * sizeof (double));
    }
    a = malloc ((n+1) * sizeof (double **));
    b = malloc ((n+1) * sizeof (double *));
    coef = malloc ((n+1) * sizeof (double *));
    for (int i = 0; i <=n; i++){
        a[i] = malloc ((n + 1) * sizeof (double *));
        b[i] = malloc (2 * sizeof (double));
        coef[i] = malloc (2 * sizeof (double));
        for (int j = 0; j <=n; j++){
            a[i][j] = malloc (2 * sizeof (double));
        }
    }
    LIKWID_MARKER_INIT;
    for (int i = 0; i < k; i++){
        scanf ("%lf", &x[i][0]);
        scanf ("%lf", &y[i][0]);
        calculaIntervalo (x[i][0], x[i]);
        calculaIntervalo (y[i][0], y[i]);
    }
    LIKWID_MARKER_START("geraSistema");
    //Calcula os somatórios necessários para a matriz A
    for (i = 0; i <= n-1; i++){
        somatorio(i, 0, x, k, somas[i]);
    }
    for (int j = 0; j <= n; j++){
        somatorio(j, i, x, k, somas[i+j]);
    }
    //Realiza as atribuições dos somatórios para a matriz A, evitando cálculos repetidos
    for (int i = 0; i <=n; i++){
        for (int j = 0; j <=n; j++){
            a[i][j][0] = somas[i+j][0];
            a[i][j][1] = somas[i+j][1];
        }
    }
    calculaB (b, n + 1, k, y, x);
    LIKWID_MARKER_STOP("geraSistema");
    LIKWID_MARKER_START("resolveSistema");
    gaussComMult (a, b, n+1);
    retroSub (a, b, coef, n+1);
    LIKWID_MARKER_STOP("resolveSistema");
    for (int i = 0; i <=n; i++){
        printf ("[%1.16e, %1.16e] ", coef[i][0], coef[i][1]);
    }
    printf ("\n");
    calculaResiduo (coef, x, y, k, n + 1);
    LIKWID_MARKER_CLOSE;
    for (int i = 0; i < k; i++){
        free (x[i]);
        free (y[i]);
    }
    free (x);
    free (y);
    for (int i = 0; i <=n; i++){
        free (b[i]);
        free (coef[i]);
        for (int j = 0; j <=n; j++){
            free (a[i][j]);
        }
        free (a[i]);
    }
    free (a);
    free (b);
    free (coef);
    for (int i = 0; i < 2*(n+1) - 1; i++){
        free (somas[i]);
    }
    free (somas);
    return 0;
}