#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void Inicializa_Lista(Lista *l, int tam_info){
  l->tam_info = tam_info;
  l->lista = NULL;
  l->qtd_elem = 0;
}

int InserirListaInicio(Lista *l, void *elemento){
  Elemento *temp = malloc(sizeof(Elemento));
  if(temp==NULL){
    return 0;
  }
  temp->info = malloc(l->tam_info);
  if(temp->info==NULL){
    free(temp);
    return 0;
  }
  memcpy(temp->info, elemento, l->tam_info);
  temp->prox = l->lista;
  l->lista = temp;
  l->qtd_elem++;
  return 1;
}

int InserirListaFim(Lista *l, void *elemento){
  if(TestaVazia(l)==VAZIA){
    return InserirListaInicio(l, elemento);
  }
  Elemento *temp = malloc(sizeof(Elemento));
  if(temp==NULL){
    return 0;
  }
  temp->info = malloc(l->tam_info);
  if(temp->info==NULL){
    free(temp);
    return 0;
  }
  memcpy(temp->info, elemento, l->tam_info);
  temp->prox = NULL;
  Elemento *aux;
  aux = l->lista;
  while(aux->prox!= NULL){
    aux = aux->prox;
  }
  aux->prox = temp;
  l->qtd_elem++;
  return 1;
}

int RemoverListaFim(Lista *l, void *info){
  if(TestaVazia(l)==VAZIA){
    return VAZIA;
  }
  if(l->qtd_elem==1){
    return RemoverListaInicio(l, info);
  }
  Elemento *aux;
  aux = l->lista;
  while(aux->prox->prox!=NULL){
    aux = aux->prox;
  }
  memcpy(info, aux->prox->info, l->tam_info);
  free(aux->prox->info);
  free(aux->prox);
  aux->prox = NULL;
  l->qtd_elem--;
  return 1;
}

int RemoverListaInicio(Lista *l, void *info){
  if(TestaVazia(l)==VAZIA){
    return VAZIA;
  }
  Elemento *aux1;
  Elemento *aux2;
  aux1 = l->lista;
  aux2 = aux1->prox;
  memcpy(info, aux1->info, l->tam_info);
  free(aux1->info);
  free(aux1);
  l->lista = aux2;
  l->qtd_elem--;
  return 1;
}

int TestaVazia(Lista *l){
  if(l->lista==NULL){
    return VAZIA;
  }else{
    return 0;
  }
}
void *RetornaElemPosi(Lista *l, int posi){
  if(posi>l->qtd_elem){
    return NULL;
  }
  Elemento *aux = l->lista;
  int i;
  for(i=0;i<posi;i++){
    aux = aux->prox;
  }
  return aux->info;
}

int DesalocaLista(Lista *l){
  int i;
  int tempqtd = l->qtd_elem;
  for(i=0;i<tempqtd;i++){
    void *aux = malloc(l->tam_info);
    int temp1 = RemoverListaInicio(l, aux);
    if(temp1==0){
      printf("ERRO AO DESALOCAR!\n");
      return 0;
    }
  }
  free(l);
  return 1;
/*  Elemento *aux1 = l->lista;
  Elemento *aux2 = l->lista->prox;
  int i;
  for(i=0;i<l->qtd_elem;i++){
    if(i%2==0){
      free(aux1->info);
      free(aux1);
      aux1 = aux2->prox;
    }else{
      free(aux2->info);
      free(aux2);
      aux2 = aux1->prox;
    }
  }
  free(l);
  return 1;
  */
}
void MostraLista(Lista *l, void (*mostra)(void *)){
  if(TestaVazia(l)==VAZIA){
    printf("Lista Vazia!\n");
    return;
  }else{
    printf("Dados da lista: \n");
    Elemento *aux = l->lista;
    while(aux!=NULL){
      mostra(aux->info);
      aux = aux->prox;
    }
  }
}
/*
void MostraFloat(void *x){
  float *p = x;
  printf(".1f ", *p);
}*/

int InserirListaInd(Lista *l, void *info, int posi){
  if(posi<0){
    return 0;
  }
  if(posi>l->qtd_elem){
    return 0;
  }
  if(posi==0){
    return InserirListaInicio(l, info);
  }
  if(l->qtd_elem==posi){
    return InserirListaFim(l, info);
  }
  int i;
  Elemento *aux1 = l->lista;
  for(i=0;i<(posi-1);i++){
    aux1 = aux1->prox;
  }
  Elemento *temp = malloc(sizeof(Elemento));
  if(temp==NULL){
    return 0;
  }
  temp->info = malloc(sizeof(l->tam_info));
  if(temp->info==NULL){
    free(temp);
    return 0;
  }
  memcpy(temp->info, info, l->tam_info);
  temp->prox = aux1->prox;
  aux1->prox = temp;
  l->qtd_elem++;
  return 1;
}

int RemoverListaInd(Lista *l, void *info, int posi){
  if(TestaVazia(l)==VAZIA){
    return 0;
  }
  if(posi>l->qtd_elem){
    return 0;
  }
  if(posi==l->qtd_elem){
    return RemoverListaFim(l, info);
  }
  if(posi==0){
    return RemoverListaInicio(l, info);
  }
  int i;
  Elemento *aux = l->lista;
  for(i=0;i<posi-1;i++){
    aux = aux->prox;
  }
  Elemento *aux2;
  aux2 = aux->prox->prox;
  memcpy(aux->prox->info, info, l->tam_info);
  free(aux->prox->info);
  free(aux->prox);
  aux->prox = aux2;
  l->qtd_elem--;
  return 0;
}
