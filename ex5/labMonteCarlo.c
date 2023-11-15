#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int dimensoes)
{
  double resultado;
  double soma = 0.0;
  double x[dimensoes];
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);
  
  double t_inicial = timestamp();
  switch (dimensoes){
    case 2:
      for (int i = 0; i < namostras; i++){
        x[0] = a + NRAND * (b - a);
        x[1] = a + NRAND * (b - a);
        soma += (x[0]*x[0]*x[0]*x[0] - 16 *x[0]*x[0] + 5*x[0] + x[1]*x[1]*x[1]*x[1] - 16*x[1]*x[1] + 5*x[1])/2;
      }
      break;
    case 4:
      for (int i = 0; i < namostras; i++){
        x[0] = a + NRAND * (b - a);
        x[1] = a + NRAND * (b - a);
        x[2] = a + NRAND * (b - a);
        x[3] = a + NRAND * (b - a);
        soma += (x[0]*x[0]*x[0]*x[0] - 16 *x[0]*x[0] + 5*x[0] + x[1]*x[1]*x[1]*x[1] - 16*x[1]*x[1] + 5*x[1])/2;
        soma += (x[2]*x[2]*x[2]*x[2] - 16 *x[2]*x[2] + 5*x[2] + x[3]*x[3]*x[3]*x[3] - 16*x[3]*x[3] + 5*x[3])/2;
      }
      break;
    case 8:
      for (int i = 0; i < namostras; i++){
        x[0] = a + NRAND * (b - a);
        x[1] = a + NRAND * (b - a);
        x[2] = a + NRAND * (b - a);
        x[3] = a + NRAND * (b - a);
        x[4] = a + NRAND * (b - a);
        x[5] = a + NRAND * (b - a);
        x[6] = a + NRAND * (b - a);
        x[7] = a + NRAND * (b - a);
        soma += (x[0]*x[0]*x[0]*x[0] - 16 *x[0]*x[0] + 5*x[0] + x[1]*x[1]*x[1]*x[1] - 16*x[1]*x[1] + 5*x[1])/2;
        soma += (x[2]*x[2]*x[2]*x[2] - 16 *x[2]*x[2] + 5*x[2] + x[3]*x[3]*x[3]*x[3] - 16*x[3]*x[3] + 5*x[3])/2;
        soma += (x[4]*x[4]*x[4]*x[4] - 16 *x[4]*x[4] + 5*x[4] + x[5]*x[5]*x[5]*x[5] - 16*x[5]*x[5] + 5*x[5])/2;
        soma += (x[6]*x[6]*x[6]*x[6] - 16 *x[6]*x[6] + 5*x[6] + x[7]*x[7]*x[7]*x[7] - 16*x[7]*x[7] + 5*x[7])/2;
      }
      break;
    default:
      printf("Numero de dimensoes invalido.\n");
      return 0;
      break;
  }    
  
  resultado = soma / namostras * (b - a) * (b - a);
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f ms.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h;
  double resultado;
  double soma = 0;
  h = (b - a) / npontos;
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  double t_inicial = timestamp();
  double h2 = h * h;
  double tang = 0;

  for (int j = 0; j < npontos; j++){
    double y = a + j * h;
    tang += (y*y*y*y - 16 *y*y + 5*y)/2;
  }

  for (int i = 0; i < npontos; i++){
    double x = a + i * h;
    soma += tang + 5000000*(x*x*x*x - 16 *x*x + 5*x);
  }

  resultado = soma * h2;
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f ms.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 4) {
    printf("Utilização: %s dimensoes inicial final\n", argv[0]);
    return 1;
  }

  SRAND(20232); // semente para o gerador de números aleatórios
  
  int dimensoes = atoi(argv[1]);
  double a = atof(argv[2]);
  double b = atof(argv[3]);

  double resultado = styblinskiTang(a, b, 10000000, dimensoes);
  printf("Resultado: %f\n", resultado);
  if (dimensoes == 2){
    resultado = retangulos_xy(a, b, 10000000);
    printf("Resultado: %f\n", resultado);
  }
  return 0;
}

