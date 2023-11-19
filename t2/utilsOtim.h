// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef __UTILSOTIM_H__
#define __UTILSOTIM_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "intervalOtim.h"

#define UF 4
#define BK 8

#define CALCULA_POTENCIA(valor, expoente) ({ \
    double resultado_macro = (valor); \
    for (int i_macro = 1; i_macro < (expoente); i_macro++) { \
        resultado_macro *= (valor); \
    } \
    resultado_macro; \
})


// Valor absoluto de um número. Alternativa ao uso da função 'fabs()'
#define ABS(num)  ((num) < 0.0 ? -(num) : (num))

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// int_t: tipo usado para representar valores em inteiros
typedef int64_t int_t;

// string_t: tipo usado para representar ponteiros para char/strings
typedef char * string_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// Número máximo de dígitos em um número
#define numDigits(n)  6  // ( (int) log10(n) + 1 )

// Macro para verificar se valor 'n' é potência de 2 ou não
#define isPot2(n) (n && !(n & (n - 1)))

// Funções
rtime_t timestamp(void);
string_t markerName(string_t baseName, int n);

intervaloA_t *alocaVetor(long long int tam);

intervaloA_t *liberaVetor(intervaloA_t *vetor);

intervalo_t **alocaMatriz(int tam);

intervalo_t **liberMatriz(intervalo_t **matriz, int tam);

double calculaPotencia(double base, int expoente);

#endif // __UTILSOTIM_H__

