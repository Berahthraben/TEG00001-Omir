#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

typedef struct{
  int coluna;
  int valor;
}EntradaMatriz;

typedef struct{
  int lin, col;
  Lista lis;
}MatrizEsp;

typedef struct{ //Estrutura auxiliar para o menu na Main
    MatrizEsp *arrayPrincipal;
    int tamanhoAtual;
} Registro;

int Inicializa_MatrizEsp(MatrizEsp *m, int linha, int coluna);
int InsereValor(MatrizEsp *m, int linha, int coluna, void *entrada);
int EditaValor(MatrizEsp *m, int linha, int coluna, void *entrada);
int RemoveValor(MatrizEsp *m, int linha, int coluna);
int EncontraColuna(Lista *l, int coluna);
int EncontraListaPosi(Lista *l, int coluna);
void MostraValorPosi(MatrizEsp *m, int linha, int coluna);
int AuxOp(Lista *l, int coluna);
void SomaMatriz(MatrizEsp *m1, MatrizEsp *m2, MatrizEsp *m3);
void MultiplicaMatriz(MatrizEsp *m1, MatrizEsp *m2, MatrizEsp *m3);
void DesalocaMatriz(MatrizEsp *m);
void MostraMatriz(MatrizEsp *m);
