// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef ___SISTEMASOTIM_H___
#define ___SISTEMASOTIM_H___

#include <stdio.h>
#include "intervalOtim.h"

void trocaLinhas (intervalo_t ** restrict a, intervaloA_t * restrict b, int i, int pivo);

int encontraPivo (intervalo_t ** restrict a, int i, int tam);

void gaussComMult (intervalo_t ** restrict a, intervaloA_t * restrict b, int tam);

void retroSub (intervalo_t ** restrict a, intervaloA_t * restrict b, intervaloA_t * restrict x, int tam);

void calculaResiduo (intervaloA_t * restrict coef, intervaloA_t * restrict x, intervaloA_t * restrict y, long long int pontos, int tam, intervaloA_t * restrict r);

void imprimeMatriz (intervalo_t ** restrict a, intervaloA_t * restrict b, int tam);

void calculaAeB (intervalo_t ** restrict a, intervaloA_t * restrict b, int n, int k, intervaloA_t * restrict x, intervaloA_t * restrict y);

#endif // ___SISTEMASOTIM_H___