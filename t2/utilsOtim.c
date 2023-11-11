// Matheus Sebastian Alencar de Carvalho - GRR20220065
// Tiago Mendes Bottamedi - GRR20220068

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utilsOtim.h"

/*  Retorna tempo em milisegundos desde EPOCH

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

rtime_t timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (rtime_t) tp.tv_sec*1.0e3 + (rtime_t) tp.tv_nsec*1.0e-6 );
}

/* Gera string '<baseName>_n'
 * Por exemplo, se baseName = "ABC" e n = 10,
 *  Função retorna a string "ABC_10"
 * Útil para gerar marcadores para LIKWID
 */
string_t markerName(string_t baseName, int n)
{
    string_t mark = (string_t) malloc( (strlen(baseName)+1) + numDigits(n) + 1 );

  sprintf(mark, "%s_%u", baseName,n);

  // printf("*** %s\n", mark);

  return mark;

}

/*As 2 funções abaixo de alocação podem apresentar o código de erro 2. Esse código significa que houve alguma falha durante o processo de alocação.*/

/*Recebe como parâmetro um tamanho e aloca um vetor de intervalos desse tamanho,
retornando o ponteiro para esse vetor*/
intervalo_t *alocaVetor(long long int tam){
	intervalo_t *aux;
	aux = malloc (tam * sizeof (intervalo_t ));
	if (!aux){
		fprintf (stderr, "Falha ao alocar vetor\n");
		exit(2);
	}
	return aux;
}

/*Recebe como parâmetro um ponteiro do tipo intervalo, libera a memória alocada por ele e retorna NULL*/
intervalo_t *liberaVetor(intervalo_t *vetor){
	free (vetor);
	return NULL;
}

double calculaPotencia (double valor, int expoente){
	double resultado = valor;
	for (int i = 1; i < expoente; i++){
		resultado *= valor;
	}
	return resultado;
}

/*Recebe como parâmetro um tamanho e aloca uma matriz de intervalos de tamanho linhas x tamanho colunas,
retornando o ponteiro para essa matriz*/
intervalo_t **alocaMatriz(int tam){
	intervalo_t **aux;
	aux = malloc (tam * sizeof (intervalo_t *));
	if (!aux){
		fprintf (stderr, "Falha ao alocar matriz\n");
		exit(2);
	}
	for (int i = 0; i < tam; i++){
		aux[i] = malloc (tam * sizeof(intervalo_t ));
		if (!aux[i]){
			fprintf (stderr, "Falha ao alocar matriz\n");
			exit(2);
		}
	}
	return aux;
}

/*Recebe como parâmetro um ponteiro para ponteiro do tipo intervalo e um inteiro indicando o tamanho da matriz.
Libera toda a memória alocada por esse ponteiro e retorna NULL*/
intervalo_t **liberMatriz(intervalo_t **matriz, int tam){
	for (int i = 0; i < tam; i++){
		free (matriz[i]);
	}
	free (matriz);
	return NULL;
}