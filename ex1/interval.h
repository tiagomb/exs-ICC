#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdint.h>

typedef union{
    int32_t i;
    float f;
    struct
    {   // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        uint32_t mantissa : 23; // primeiros 23 bits (da direita para a esquerda)
        uint32_t exponent : 8;  // prÃ³ximos 8 bits
        uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

void adicionaIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]);

void subtraiIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]);

void multiplicaIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]);

void divideIntervalo (Float_t intervalo1[2], Float_t intervalo2[2], Float_t resultado[2]);

void calculaIntervalo (Float_t valor, Float_t intervalo[2]);

void calculaErroAbsoluto (Float_t a, Float_t b);

void calculaErroRelativo (Float_t a, Float_t b);

void calculaULPs(Float_t A, Float_t B);

#endif // INTERVAL_H