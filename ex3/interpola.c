#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include "utils.h"
#include "polinomios.h"

int main(int argc, char **argv){
    int tam;
    double *x, *y, tempo, xe;
    void (*interpola[2]) (int, double *, double *, double);
    LIKWID_MARKER_INIT;
    interpola[0] = poliLagrange;
    interpola[1] = poliNewton;
    if (scanf ("%d", &tam) != 1){
        fprintf (stderr, "Erro ao ler o tamanho do vetor\n");
        exit (1);
    }
    x = (double *) malloc (tam * sizeof(double));
    y = (double *) malloc (tam * sizeof(double));
    for (int i = 0; i < tam; i++){
        if (scanf ("%lf", &x[i]) != 1){
            fprintf (stderr, "Erro ao ler o vetor x\n");
            exit (1);
        }
        if (scanf ("%lf", &y[i]) != 1){
            fprintf (stderr, "Erro ao ler o vetor y\n");
            exit (1);
        }
    }
    xe = atoi(argv[1]);
    for (int i = 0; i < 2; i++){
        LIKWID_MARKER_START(markerName("interpola", i));
        tempo = timestamp();
        interpola[i] (tam, x, y, xe);
        tempo = timestamp() - tempo;
        printf ("%1.16e ms\n", tempo);
        LIKWID_MARKER_STOP(markerName("interpola", i));
    }
    free (x);
    free (y);
    LIKWID_MARKER_CLOSE;
    return 0;
}