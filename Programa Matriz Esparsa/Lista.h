#include <stdio.h>
#include <stdlib.h>
#define VAZIA -1

typedef struct Elemento1 {
  void *info;
  struct Elemento1 *prox;
} Elemento;

typedef struct{
  int qtd_elem;
  int tam_info;
  Elemento *lista;
} Lista;

void Inicializa_Lista(Lista *l, int tam_info);
int InserirListaInicio(Lista *l, void *info);
int RemoverListaInicio(Lista *l, void *info);
int InserirListaFim(Lista *l, void *info);
int InserirListaInd(Lista *l, void *info, int posi);
int RemoverListaInd(Lista *l, void *info, int posi);
int RemoverListaFim(Lista *l, void *info);
void *RetornaElemPosi(Lista *l, int posi);
int TestaVazia(Lista *l);
int DesalocaLista(Lista *l);
void MostraLista(Lista *l, void (*mostra)(void *));
