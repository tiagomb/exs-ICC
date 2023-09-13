#include <stdio.h>
#include <fenv.h>
#include <float.h>
#include "interval.h"

int main(){
    fesetround (FE_DOWNWARD);
    Float_t valor1, valor2;
    char operacao;
    Float_t intervalo1[2], intervalo2[2], resultado[2];
    scanf ("%f", &valor1.f);
    calculaIntervalo (valor1, intervalo1);
    for (int i =0; i < 4; i++){
        fesetround (FE_DOWNWARD);
        scanf (" %c %f", &operacao, &valor2.f);
        calculaIntervalo (valor2, intervalo2);
        printf ("[%1.8e, %1.8e] %c [%1.8e, %1.8e]\n", intervalo1[0].f, intervalo1[1].f, operacao, intervalo2[0].f, intervalo2[1].f);
        switch (operacao){
            case '+':
                adicionaIntervalo (intervalo1, intervalo2, resultado);
            break;
            case '-':
                subtraiIntervalo (intervalo1, intervalo2, resultado);
            break;
            case '*':
                multiplicaIntervalo (intervalo1, intervalo2, resultado);
            break;
            case '/':
                divideIntervalo (intervalo1, intervalo2, resultado);
            break;
            default:
                printf ("Operacao invalida\n");
        }
        calculaErroAbsoluto(resultado[0], resultado[1]);
        calculaErroRelativo(resultado[0], resultado[1]);
        calculaULPs (resultado[0], resultado[1]);

        intervalo1[0].f = resultado[0].f;
        intervalo1[1].f = resultado[1].f;
    }
}