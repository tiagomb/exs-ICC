#ifndef ___SISTEMAS_H___
#define ___SISTEMAS_H___

#include <stdio.h>

void trocaLinhas (double ***a, double **b, int i, int pivo);

int encontraPivo (double ***a, int i, int tam);

void gaussComMult (double ***a, double **b, int tam);

void retroSub (double ***a, double **b, double **x, int tam);

void calculaResiduo (double **coef, double **x, double **y, int pontos, int tam);

void imprimeMatriz (double ***a, double **b, int tam);

void somatorio (int expoenteCima, int expoenteBaixo, double **x, int k, double soma[2]);

void calculaB (double **b, int n, int k, double **y, double **x);

#endif // ___SISTEMAS_H___