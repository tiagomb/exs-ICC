// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "sistemas.h"
#include "utils.h"
#include <fenv.h>
#include <likwid.h>

/*O programa principal pode gerar o código de erro 1. Esse código significa que houve uma falha ao ler algum valor da entrada*/

int main (){
    int n;
    long long int k;
    double tempo[3];
    intervalo_t *x, *y, **a, *b, *coef;
    fesetround (FE_DOWNWARD);
    if (scanf ("%d", &n) != 1){
        fprintf (stderr, "Falha ao grau\n");
        exit (1);
    }
    if (scanf ("%lld", &k) != 1){
        fprintf (stderr, "Falha ao ler número de pontos\n");
        exit (1);
    }
    x = alocaVetor(k);
    y = alocaVetor(k);
    a = alocaMatriz(n+1);
    b = alocaVetor(n+1);
    coef = alocaVetor(n+1);
    LIKWID_MARKER_INIT;
    for (long long int i = 0; i < k; i++){
        if (scanf ("%lf", &x[i].inicio) != 1){
            fprintf (stderr, "Falha ao ler um dos pontos\n");
            exit (1);
        }
        if (scanf ("%lf", &y[i].inicio) != 1){
            fprintf (stderr, "Falha ao ler um dos pontos\n");
            exit (1);
        }
        calculaIntervalo (x[i].inicio, &x[i]);
        calculaIntervalo (y[i].inicio, &y[i]);
    }
    LIKWID_MARKER_START("geraSistema");
    tempo[0] = timestamp();
    calculaA (a, n + 1, k, x);
    calculaB (b, n + 1, k, y, x);
    tempo[0] = timestamp() - tempo[0];
    LIKWID_MARKER_STOP("geraSistema");
    LIKWID_MARKER_START("resolveSistema");
    tempo[1] = timestamp();
    gaussComMult (a, b, n+1);
    retroSub (a, b, coef, n+1);
    tempo[1] = timestamp() - tempo[1];
    LIKWID_MARKER_STOP("resolveSistema");
    #ifdef _DEBUG_
    for (int i = 0; i <=n; i++){
        printf ("[%1.16e, %1.16e] ", coef[i].inicio, coef[i].fim);
    }
    printf ("\n");
    #endif // _DEBUG_
    LIKWID_MARKER_START("calculaResiduo");
    tempo[2] = timestamp();
    calculaResiduo (coef, x, y, k, n + 1);
    tempo[2] = timestamp() - tempo[2];
    LIKWID_MARKER_STOP("calculaResiduo");
    printf ("%1.16e\n%1.16e\n%1.16e\n", tempo[0], tempo[1], tempo[2]);
    LIKWID_MARKER_CLOSE;
    x = liberaVetor (x);
    y = liberaVetor (y);
    a = liberMatriz (a, n+1);
    b = liberaVetor (b);
    coef = liberaVetor (coef);
    return 0;
}
