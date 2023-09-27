#ifndef ___SISTEMAS_H___
#define ___SISTEMAS_H___

#include <stdio.h>

void trocaLinhas (double ***a, double **b, int i, int pivo);

int encontraPivo (double ***a, int i, int tam);

void gaussComMult (double ***a, double **b, int tam);

void retroSub (double ***a, double **b, double **x, int tam);

void calculaResiduo (double ***a, double **b, double **x, int tam);

void imprimeMatriz (double ***a, double **b, int tam);

#endif // ___SISTEMAS_H___