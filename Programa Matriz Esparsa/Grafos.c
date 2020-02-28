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

int hasLoop(MatrizEsp *m){
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
    int i, j = 0, vertice;
    int desconexo = 0;
    int elemAnterior = 0;
    //
    for(vertice = 0; vertice < m->lin-1 ; vertice++){
        for(i = 0; i < m->lin ; i++){
            for(j; j < m->col; j++){
                if( i < j ){
                    int a = RetornaValorPosi(m, i+1, j+1);
                    if(a > 0){ //seguir valor
                        i = j-1;
                        j = i-1;
                        break;
                    }else if(j = m->col-1 && a < 1 && a!=-1){ //desconexo
                        desconexo = 1;
                        break;
                    };
                };
            };
            if(desconexo == 1){
                break;
            };
        };
        j = 0;
        if(desconexo == 1){
            break;
        };
    };
};
int isDominante(MatrizEsp *m){
    return 0;
}
int isSimples(MatrizEsp *m){
    return 0;
}
int isDirecionado(MatrizEsp *m){
    return 0;
}
int comprimentoCaminho(MatrizEsp *m, char caminho[]){
    return 0;
}
