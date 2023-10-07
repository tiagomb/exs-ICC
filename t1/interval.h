// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdint.h>

typedef struct intervalo {
    double inicio;
    double fim;
} intervalo_t;

void adicionaIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado);

void subtraiIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado);

void multiplicaIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado);

void divideIntervalo (intervalo_t intervalo1, intervalo_t intervalo2, intervalo_t *resultado);

void potenciaIntervalo (intervalo_t intervalo, int expoente, intervalo_t *resultado);

void calculaIntervalo (double valor, intervalo_t *intervalo);


#endif // INTERVAL_H