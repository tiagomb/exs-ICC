#include <stdio.h>
#include <stdlib.h>
#include "metodos.h"
#include "utils.h"
#include <likwid.h>

int main(){
    LIKWID_MARKER_INIT;
    double **a, **a2, *b, *b2, *x, tempo;
    int tam;
    void (*metodo[3]) (double **, double *, int);
    metodo[0] = gaussComMult;
    metodo[1] = gaussSemMult;
    metodo[2] = semPivo;    
    if (scanf ("%d", &tam) != 1){
        printf ("Erro ao ler o tamanho da matriz\n");
        exit (1);
    }
    a = malloc (tam * sizeof (double *));
    a2 = malloc (tam * sizeof (double *));
    for (int i = 0; i < tam; i++){
        a[i] = malloc (tam * sizeof (double));
        a2[i] = malloc (tam * sizeof (double));
    }
    b = malloc (tam * sizeof (double));
    b2 = malloc (tam * sizeof (double));
    x = malloc (tam * sizeof (double));
    leMatriz (a, b, tam);
    copiaMatriz (a, a2, b, b2, tam);
    for (int i = 0; i<3;i++){
        switch (i){
            case 0:
                printf ("Gauss com multiplicador\n\n");
            break;
            case 1:
                printf ("Gauss sem multiplicador\n\n");
            break;
            case 2:
                printf ("Sem pivoteamento\n\n");
            break;
        }
        LIKWID_MARKER_START(markerName("metodo",i));
        tempo = timestamp();
        metodo[i](a, b, tam);
        retroSub (a, b, x, tam);
        tempo = timestamp() - tempo;
        LIKWID_MARKER_STOP(markerName("metodo",i));
        printf ("\nSolução: ");
        printf ("[ ");
        for (int i = 0; i < tam; i++){
            printf ("%1.8e ", x[i]);
        }
        printf ("]\n");
        printf ("\nTempo: %1.8e ms\n", tempo);
        printf ("\nResíduo: ");
        calculaResiduo (a2, b2, x, tam);
        printf ("\n\n\n");
        copiaMatriz (a2, a, b2, b, tam);
    }   
    free (b);
    free (b2);
    free (x);
    for (int i = 0; i < tam; i++){
        free (a[i]);
        free (a2[i]);
    }
    free (a);
    free (a2);
    LIKWID_MARKER_CLOSE;
    return 0;
}