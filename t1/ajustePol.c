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
    int n, k, i;
    intervalo_t *x, *y, **a, *b, *somas, *coef, tempo;
    fesetround (FE_DOWNWARD);
    if (scanf ("%d", &n) != 1){
        fprintf (stderr, "Falha ao ler grau do polinômio\n");
        exit (1);
    }
    if (scanf ("%d", &k) != 1){
        fprintf (stderr, "Falha ao ler número de pontos\n");
        exit (1);
    }
    x = alocaVetor(k);
    y = alocaVetor(k);
    somas = alocaVetor(2*(n+1) - 1);
    a = alocaMatriz(n+1);
    b = alocaVetor(n+1);
    coef = alocaVetor(n+1);
    LIKWID_MARKER_INIT;
    for (int i = 0; i < k; i++){
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
    tempo.inicio = timestamp();
    //Calcula os somatórios necessários para a matriz A
    for (i = 0; i <= n-1; i++){
        somatorio(i, 0, x, k, &somas[i]);
    }
    for (int j = 0; j <= n; j++){
        somatorio(i, j, x, k, &somas[i+j]);
    }
    //Realiza as atribuições dos somatórios para a matriz A, evitando cálculos repetidos
    for (int i = 0; i <=n; i++){
        for (int j = 0; j <=n; j++){
            a[i][j].inicio = somas[i+j].inicio;
            a[i][j].fim = somas[i+j].fim;
        }
    }
    calculaB (b, n + 1, k, y, x);
    tempo.inicio = timestamp() - tempo.inicio;
    LIKWID_MARKER_STOP("geraSistema");
    LIKWID_MARKER_START("resolveSistema");
    tempo.fim = timestamp();
    gaussComMult (a, b, n+1);
    retroSub (a, b, coef, n+1);
    tempo.fim = timestamp() - tempo.fim;
    LIKWID_MARKER_STOP("resolveSistema");
    for (int i = 0; i <=n; i++){
        printf ("[%1.16e, %1.16e] ", coef[i].inicio, coef[i].fim);
    }
    printf ("\n");
    calculaResiduo (coef, x, y, k, n + 1);
    printf ("%1.16e\n%1.16e\n", tempo.inicio, tempo.fim);
    LIKWID_MARKER_CLOSE;
    x = liberaVetor (x);
    y = liberaVetor (y);
    somas = liberaVetor (somas);
    a = liberMatriz (a, n+1);
    b = liberaVetor (b);
    coef = liberaVetor (coef);
    return 0;
}