#ifndef ___metodos_h
#define ___metodos_h

#include <stdio.h>
#include <stdlib.h>

void trocaLinhas (double **a, double *b, int i, int pivo);

int encontraPivo (double **a, int i, int tam);

void gaussComMult (double **a, double *b, int tam);

void gaussSemMult (double **a, double *b, int tam);

void semPivo (double **a, double *b, int tam);

void retroSub (double **a, double *b, double *x, int tam);

void leMatriz (double **a, double *b, int tam);

void calculaResiduo (double **a, double *b, double *x, int tam);

void imprimeMatriz (double **a, double *b, int tam);

void copiaMatriz (double **a, double **a2, double *b, double *b2, int tam);

#endif // ___metodos_h