#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdint.h>

void adicionaIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]);

void subtraiIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]);

void multiplicaIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]);

void divideIntervalo (double intervalo1[2], double intervalo2[2], double resultado[2]);

void potenciaIntervalo (double intervalo[2], int expoente, double resultado[2]);

void calculaIntervalo (double valor, double intervalo[2]);


#endif // INTERVAL_H