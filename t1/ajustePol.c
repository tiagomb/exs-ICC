#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "sistemas.h"
#include "utils.h"
#include <fenv.h>

void somatorio (int expoenteCima, int expoenteBaixo, double **x, int k, double soma[2]){
    double potencia1[2], potencia2[2], mult[2];
    soma[0] = soma[1] = 0;
    for (int i = 0; i < k; i++){
        potenciaIntervalo (x[i], expoenteCima, potencia1);
        potenciaIntervalo (x[i], expoenteBaixo, potencia2);
        multiplicaIntervalo (potencia1, potencia2, mult);
        adicionaIntervalo (soma, mult, soma);
    }
}

void calculaB (double **b, int n, int k, double **y, double **x){
    double potencia[2], mult[2];
    for (int i = 0; i < n; i++){
        b[i][0] = b[i][1] = 0;
        for (int j = 0; j < k; j++){
            potenciaIntervalo (x[j], i, potencia);
            multiplicaIntervalo (potencia, y[j], mult);
            adicionaIntervalo (b[i], mult, b[i]);
        }
    }
}

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

    for (int i = 0; i < k; i++){
        scanf ("%lf", &x[i][0]);
        scanf ("%lf", &y[i][0]);
        calculaIntervalo (x[i][0], x[i]);
        calculaIntervalo (y[i][0], y[i]);
    }
    for (i = 0; i <= n-1; i++){
        somatorio(i, 0, x, k, somas[i]);
    }
    for (int j = 0; j <= n; j++){
        somatorio(j, i, x, k, somas[i+j]);
    }
    for (int i = 0; i <=n; i++){
        for (int j = 0; j <=n; j++){
            a[i][j][0] = somas[i+j][0];
            a[i][j][1] = somas[i+j][1];
        }
    }
    printf ("\n");
    calculaB (b, n + 1, k, y, x);
    gaussComMult (a, b, n+1);
    retroSub (a, b, coef, n+1);
    for (int i = 0; i <=n; i++){
        printf ("[%1.16e, %1.16e] ", coef[i][0], coef[i][1]);
    }
    printf ("\n");
    calculaResiduo (coef, x, y, k, n + 1);



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