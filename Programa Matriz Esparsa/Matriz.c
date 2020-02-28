#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matriz.h"

int Inicializa_MatrizEsp(MatrizEsp *m, int linha, int coluna){
  m->lin = linha;
  m->col = coluna;
  int i;
  Inicializa_Lista(&m->lis, sizeof(Lista));
  for(i=0;i<linha;i++){
    Lista temp2;
    Inicializa_Lista(&temp2, sizeof(EntradaMatriz));
    if(i!=0){
        InserirListaFim(&m->lis, &temp2);
    }else{
        InserirListaInicio(&m->lis, &temp2);
    }
  }
  return 1;
}

int InsereValor(MatrizEsp *m, int linha, int coluna, void *entrada){
  Elemento *aux;
  aux = m->lis.lista; //apontando para linha correta, pra fazer a operacao na mesma
  int i;
  for(i=1;i<linha;i++){
	  aux = aux->prox;
  }
  // Aux agora aponta pra lista da Line "linha"
  if(EncontraColuna(aux->info, coluna) != -1){ // se há uma coluna já existente, substui o valor.
	  return EditaValor(m, linha, coluna, entrada);
  }
  if(TestaVazia(aux->info)==-1){ //se a lista estiver vazia, insere no inicio
	  return InserirListaInicio(aux->info, entrada);
  }
  int posi = EncontraListaPosi(aux->info, coluna); //encontra a posição da coluna a ser inserida (ordenação)
  return InserirListaInd(aux->info, entrada, posi); //insere na coluna correta (ordem)
}
int EditaValor(MatrizEsp *m, int linha, int coluna, void *entrada){
	//Testes para casos especificos
	if(linha <= 0 || coluna <=0){
	  printf("Linha &| Coluna não pode ser 0 ou negativa!\n");
	  return -1;
	}
	if(((EntradaMatriz *)entrada)->valor==0){ //se valor da entrada for 0, remove.
	  return RemoveValor(m, linha, coluna);
	}
	if(linha > m->lin){ //se linha a ser inserida for maior que nro de linhas da matriz, aloca novas listas e altera o valor.
	  int i;
	  for(i=m->lin;i<linha;i++){
		  Lista temp;
		  Inicializa_Lista(&temp, sizeof(EntradaMatriz));
		  InserirListaFim(&m->lis, &temp);
	  }
	  m->lin = linha;
	}
	if(coluna > m->col){ //apenas altera o valor máximo das colunas, caso necessário
	  m->col = coluna;
	}
	//apontar para a linha a ser resolvida
	Elemento *aux;
    aux = m->lis.lista; //apontando para linha correta, pra fazer a operacao na mesma
    int i;
    for(i=1;i<linha;i++){
        aux = aux->prox;
    }
    // Aux agora aponta pra lista da Line "linha"
	//adicionar o valor
	int teste = EncontraColuna(aux->info, coluna);
	if(teste==-1){ //testa se o valor na coluna existe na lista
		if(TestaVazia(aux->info)==VAZIA){ //se lista estiver vazia, insere no inicio
			return InserirListaInicio(aux->info, entrada);
		}else{ //senao, insere na posi certa
			int posi = EncontraListaPosi(aux->info, coluna);
			return InserirListaInd(aux->info, entrada, posi);
		}
	}
	//modificar o valor
	return InserirListaInd(aux->info, entrada, teste);
}


int RemoveValor(MatrizEsp *m, int linha, int coluna){
	Elemento *aux;
    aux = m->lis.lista; //apontando para linha correta, pra fazer a operacao na mesma
    int i;
    for(i=1;i<linha;i++){
        aux = aux->prox;
    }
    // Aux agora aponta pra lista da Line "linha"
    int temp = EncontraColuna(aux->info, coluna);
    if(temp==-1){
        printf("Elemento nao existe!\n");
        return 0;
    }
    void *info = malloc(sizeof(EntradaMatriz));
	return RemoverListaInd(aux->info, info, temp);
}
int EncontraColuna(Lista *l, int coluna){ //Comp. se a coluna já existe, retorna a posi na lista se sim, -1 se não
	/*Elemento *aux = m->lis->lista;
	int i;
	for(i=1;i<linha;i++){
		aux = aux->prox;
	}*/
	int cont=0;
	Elemento *aux;
	aux = l->lista;
	while(aux!=NULL){
        EntradaMatriz *temp;
        temp = (EntradaMatriz *)(aux->info);
        if(temp->coluna==coluna){
            return cont;
        }
        cont++;
        aux = aux->prox;
	}
	return -1;
}

int EncontraListaPosi(Lista *l, int coluna){
	int i;
	Elemento *aux1 = l->lista;
	EntradaMatriz *aux2;
	for(i=0;i<l->qtd_elem;i++){
		aux2 = aux1->info;
		if(aux2->coluna > coluna){
			return i;
		}
	}
	return i;
}
void MostraValorPosi(MatrizEsp *m, int linha, int coluna){
    if(linha > m->lin){
        printf("Erro! Fora do escopo da matriz (Insira o valor primeiro para editar o tamanho)\n");
        return;
    }
	Elemento *aux;
    aux = m->lis.lista; //apontando para linha correta, pra fazer a operacao na mesma
    int i;
    for(i=1;i<linha;i++){
        aux = aux->prox;
    }
    // Aux agora aponta pra lista da Line "linha"
    int temp = EncontraColuna(aux->info, coluna);
	if(temp==-1){
        printf("O valor eh 0\n");
        return;
	}
	EntradaMatriz *p = RetornaElemPosi(aux->info, temp);
	printf("O valor eh %d\n", p->valor);
}
void MostraMatriz(MatrizEsp *m){
	int i, j;
	Elemento *aux;
	aux = m->lis.lista;
	for(i = 0; i<m->lin ; i++){
        Lista *aux2;
        aux2 = aux->info;
        if(TestaVazia(aux2)==VAZIA){
            for(j=0;j<m->col;j++){
                printf(" 0");
            }
        }else{
            Elemento *aux3;
            aux3 = aux2->lista;
            for(j = 0; j<m->col; j++){
                EntradaMatriz *temp;
                if(aux3 != NULL){
                    temp = aux3->info;
                    if(temp->coluna-1 == j){
                        printf(" %d", temp->valor);
                        aux3 = aux3->prox;
                    }else{
                        printf(" 0");
                    }
                }else{
                    printf(" 0");
                }
            }
        }
		printf("\n");
		aux = aux->prox;
	}
	printf("\n");
}
void SomaMatriz(MatrizEsp *m1, MatrizEsp *m2, MatrizEsp *m3){ //soma m1 e m2, armazena em m3
    if(m1->lin != m2->lin || m1->col != m2->col){
        printf("Nao eh possivel somar matrizes de tamanhos diferentes!\n");
        return;
    }
    Inicializa_MatrizEsp(m3, m1->lin, m1->col);
    int i, j;
    Elemento *auxm1 = m1->lis.lista;
    Elemento *auxm2 = m2->lis.lista;
    Elemento *auxm3 = m3->lis.lista;
    Lista *auxm1j;
    Lista *auxm2j;
    Lista *auxm3j;
    for(i=0;i<m1->lin;i++){
        auxm1j = auxm1->info;
        auxm2j = auxm2->info;
        auxm3j = auxm3->info;
        for(j=0;j<m1->col;j++){
            int somaf = AuxOp(auxm1j, j+1) + AuxOp(auxm2j, j+1);
            if(somaf!=0){
                EntradaMatriz envio;
                envio.coluna = j+1;
                envio.valor = somaf;
                InserirListaFim(auxm3j, &envio);
            }
        }
        auxm1 = auxm1->prox;
        auxm2 = auxm2->prox;
        auxm3 = auxm3->prox;
    }
    printf("Calculos completos! Mostrando a matriz resultante...\n");
    MostraMatriz(m3);
}

void MultiplicaMatriz(MatrizEsp *m1, MatrizEsp *m2, MatrizEsp *m3){
    //testando validade da mult
    if(m1->col != m2->lin){
        printf("Nao eh possivel multiplicar! Matrizes incompativeis!\n");
        return;
    }
    Inicializa_MatrizEsp(m3, m1->lin, m2->col);
    int linha, coluna, i;
    //variaveis para linha
    Elemento *auxm1 = m1->lis.lista;
    Elemento *auxm2 = m2->lis.lista;
    Elemento *auxm3 = m3->lis.lista;
    //variaveis para coluna
    Lista *auxm1j;
    Lista *auxm2j;
    Lista *auxm3j;
    for(linha=0;linha<m1->lin;linha++){
        auxm1j = auxm1->info;
        auxm2j = auxm2->info;
        auxm3j = auxm3->info;
        for(coluna=0;coluna<m2->col;coluna++){
            int somageral = 0;
            Elemento *auxlog2 = auxm2;
            for(i=0;i<m1->col;i++){
                int op1 = AuxOp(auxm1j, i+1);
                int op2 = AuxOp(auxlog2->info, coluna+1);
                somageral = somageral + (op1 * op2);
                auxlog2 = auxlog2->prox;
            }
            if(somageral!=0){
                EntradaMatriz ent;
                ent.coluna = coluna+1;
                ent.valor = somageral;
                InserirListaFim(auxm3j, &ent);
            }
        }
        auxm1 = auxm1->prox;
        auxm3 = auxm3->prox;
    }
    printf("Operacao concluida! Mostrando matriz resultante...\n");
    MostraMatriz(m3);
}

int AuxOp(Lista *l, int coluna){ //retorna o valor na coluna especificada
    Elemento *aux;
    int i;
    aux = l->lista;
    EntradaMatriz *aux2;
    for(i=0;i<l->qtd_elem;i++){
        aux2 = aux->info;
        if(aux2->coluna==coluna){
            return aux2->valor;
        }
        aux = aux->prox;
    }
    return 0;
}
void DesalocaMatriz(MatrizEsp *m){
    Elemento *aux1;
    aux1 = m->lis.lista;
    int i;
    /*if(m->lis.qtd_elem == 1){
        RemoverListaInicio()
    }*/
    for(i=0;i<m->lin;i++){
        int temp = DesalocaLista(aux1->info);
        aux1 = aux1->prox;
    }
    free(m);
}
