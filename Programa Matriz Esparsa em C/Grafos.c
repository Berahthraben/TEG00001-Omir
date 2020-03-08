#include <stdio.h>
#include <stdlib.h>
#include "Grafos.h"

int mostrarGrauVertice(MatrizEsp *m, int vertice){
    int i;
    int grau = 0;
    for(int i = 0; i < m->lin ; i++){
        int em = RetornaValorPosi(m, i+1, vertice);
        if(em != -1){
            grau += em;
        }
    };
    return grau;
};

int isSimples(MatrizEsp *m){
    int i, j;
    int retorno = 0;
    //primeiro testa se elemento conecta consigo mesmo
    for(i = 0; i < m->lin; i++){
        int a = RetornaValorPosi(m, i+1, i+1);
        if(a > 0){
            retorno = 1;
            break;
        }
    }
    //depois testa por arcos paralelos
    if(retorno != 1){
        for(i = 0 ; i < m->lin ; i++){
            for(j = 0 ; j < m->col ; j++){
                int a = RetornaValorPosi(m, i+1, j+1);
                if(a > 1){
                    retorno = 1;
                    break;
                }
            }
        }
    }
    return retorno;
};

int isCompleto(MatrizEsp *m){
    int i, j;
    int completo = 1;
    for(i = 0 ; i < m->lin ; i++){
        for(j = 0 ; j < m->col ; j++){
            if(i!=j){ //desconsiderar diagonal princ.
                int a = RetornaValorPosi(m, i+1, j+1);
                int b = RetornaValorPosi(m, j+1, i+1);
                if(a != b && a!=-1){
                    completo = 0;
                    break;
                };
            };
        };
        if(completo==0){ // evitar processamento desnecessario se já não for completo
            break;
        };
    };
    return completo;
};

int isDesconexo(MatrizEsp *m){
    int i = 0, j = 0, z;
    int desconexo = 0;
	int *aux = malloc(sizeof(int)*m->lin); //vetor para teste final
	int *aux2 = malloc(sizeof(int)*m->lin); //aux pra sequencia de pulos
	for(i = 0 ; i < m->lin ; i++){
		aux[i] = 0;
		aux2[i] = -1;
	}
	i = 0;
	aux[0] = 1;
	while(1 == 1){
		int a = RetornaValorPosi(m, i+1, j+1);
		printf("VALOR EH:%d\n", a);
		if(a > 0 && aux[j] == 0){ //salto
			aux2[j] = i;
			aux[j] = 1;
			int temp = i;
			i = j;
			j = temp-1;
		}else if(j == m->lin-1){
			if(aux2[i] == -1){
				break;
			}
			int temp = i;
			i = aux2[i];
			j = temp;
		}else{
			j++;
		}
	}
	for(i = 0; i < m->lin ; i++){
		if(aux[i] == 0){
			desconexo = 1;
		}
	}
	free(aux);
	free(aux2);
	return desconexo;
};
int isDominante(MatrizEsp *m){
    return 0;
}
int isDirecionado(MatrizEsp *m){
    return 0;
}
int comprimentoCaminho(MatrizEsp *m, char caminho[]){
    return 0;
}
