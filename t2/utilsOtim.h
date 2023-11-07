// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#ifndef __UTILSOTIM_H__
#define __UTILSOTIM_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "interval.h"

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

intervalo_t *alocaVetor(long long int tam);

intervalo_t *liberaVetor(intervalo_t *vetor);

double calculaPotencia (double valor, int expoente);

#endif // __UTILSOTIM_H__

