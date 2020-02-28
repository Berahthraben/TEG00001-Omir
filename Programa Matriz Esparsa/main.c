#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matriz.h"


int main(void){
    char resp = '0';
    int regresp;
    Registro reg;
    reg.m1 = malloc(sizeof(MatrizEsp));
    reg.m2 = malloc(sizeof(MatrizEsp));
    reg.m3 = malloc(sizeof(MatrizEsp));
    reg.reg1 = 0;
    reg.reg2 = 0;
    reg.reg3 = 0;
    while(resp!='e'){
        if(resp=='0'){ //mostra menu
                printf("Bem vindo a meu programa ruim sobre matrizes esparsas! Feito para EDA0001 com o professor Rui Jorge, em 01/2019\n\n"
                       "O programa aloca duas matrizes na memoria e permite o usuario manipular seus valores,\n"
                       "bem como soma-las ou multiplica-las!\n"
                       "NOTA: O registro 3 pode ser mostrado, mas nao alterado diretamente."
                       "Digite o numero (ou letra) correspondente para acessar as opcoes:\n\n"
                        "0 - Mostrar esse dialogo novamente\n"
                        "1 - Criar Matriz em um dos registros\n"
                        "2 - Editar uma Matriz existente (digite 0 no elemento para remover uma entrada)\n"
                        "3 - Mostrar Matriz no registro dado\n"
                        "4 - Mostrar valor na posicao dada\n"
                        "5 - Somar as duas matrizes no registro\n"
                        "6 - Multiplicar matrizes no registro (permite escolher a ordem)\n"
                        "e - Sair do programa\n"
                        "Qualquer bug favor informar no Posto do Ipiranga. Um otimo ano pra voce <3!\n");

        }else if(resp=='1'){ //criar matriz
            printf("Em qual dos registros gostaria de colocar (1 ou 2)?\n");
            scanf("%d", &regresp);
            getchar();
            if(regresp == 1){
                if(reg.reg1==1){
                    printf("Ja existe uma matriz no registro! Gostaria de substituila? (S/N)\n");
                    char temp;
                    scanf("%c", &temp);
                    getchar();
                    if(temp=='S' || temp=='s'){
                        DesalocaMatriz(reg.m1);
                        reg.m1 = malloc(sizeof(MatrizEsp));
                        printf("Digite a qtd de linhas e a colunas, separadas por espaco\n");
                        int lin, col;
                        scanf("%d %d", &lin, &col);
                        getchar();
                        Inicializa_MatrizEsp(reg.m1, lin, col);
                        printf("Adicionada com sucesso! Retornando...\n");
                    }else if(temp=='N' || temp=='n'){
                        printf("Ok entao, retornando...\n");
                    }else{
                        printf("Resposta invalida! Retornando...\n");
                    }
                }else if(reg.reg1==0){
                    printf("Digite a qtd de linhas e a colunas, separadas por espaco\n");
                    int lin, col;
                    scanf("%d %d", &lin, &col);
                    getchar();
                    Inicializa_MatrizEsp(reg.m1, lin, col);
                    reg.reg1=1;
                    printf("Adicionada com sucesso! Retornando...\n");
                }
            }else if(regresp==2){
                if(reg.reg2==1){
                    printf("Ja existe uma matriz no registro! Gostaria de substituila? (S/N)\n");
                    char temp;
                    scanf("%c", &temp);
                    getchar();
                    if(temp=='S' || temp=='s'){
                        DesalocaMatriz(reg.m2);
                        reg.m2 = malloc(sizeof(MatrizEsp));
                        printf("Digite a qtd de linhas e a colunas, separadas por espaco\n");
                        int lin, col;
                        scanf("%d %d", &lin, &col);
                        getchar();
                        Inicializa_MatrizEsp(reg.m2, lin, col);
                        printf("Adicionada com sucesso! Retornando...\n");
                    }else if(temp=='N' || temp=='n'){
                        printf("Ok entao, retornando...\n");
                    }else{
                        printf("Resposta invalida! Retornando...\n");
                    }
                }else if(reg.reg2==0){
                    printf("Digite a qtd de linhas e a colunas, separadas por espaco\n");
                    int lin, col;
                    scanf("%d %d", &lin, &col);
                    getchar();
                    Inicializa_MatrizEsp(reg.m2, lin, col);
                    reg.reg2=1;
                    printf("Adicionada com sucesso! Retornando...\n");
                }
            }else{
                printf("Resposta invalida! Retornando...\n");
            }
        }else if(resp=='2'){ //editar matriz
            printf("Qual dos registros gostaria de editar? (1 ou 2)\n");
            scanf("%d", &regresp);
            getchar();
            if(regresp==1){
                if(reg.reg1!=1){
                    printf("Nao ha matriz nesse registro! Retornando...\n");
                }else{
                    int lin,col, valor;
                    printf("Digite a linha, coluna e o valor a ser colocado, separados por espaço. NOTA: VALOR = 0 REMOVERA O ELEMENTO\n");
                    scanf("%d %d %d", &lin, &col, &valor);
                    getchar();
                    EntradaMatriz en;
                    en.coluna = col;
                    en.valor = valor;
                    EditaValor(reg.m1, lin, col, &en);
                    printf("Editado com sucesso! Retornando...\n");
                }
            }else if(regresp==2){
                if(reg.reg2!=1){
                    printf("Nao ha matriz nesse registro! Retornando...\n");
                }else{
                    int lin,col, valor;
                    printf("Digite a linha, coluna e o valor a ser colocado, separados por espaço. NOTA: VALOR = 0 REMOVERA O ELEMENTO\n");
                    scanf("%d %d %d", &lin, &col, &valor);
                    getchar();
                    EntradaMatriz en;
                    en.coluna = col;
                    en.valor = valor;
                    EditaValor(reg.m2, lin, col, &en);
                    printf("Editado com sucesso! Retornando...\n");
                }
            }else{
                printf("Resposta invalida! Retornando...\n");
            }
        }else if(resp=='3'){ //mostrar matriz
            printf("Qual dos registros gostaria de mostrar? (1, 2 ou 3)\n");
            scanf("%d", &regresp);
            getchar();
            if(regresp==1){
                if(reg.reg1==0){
                    printf("Erro! Nao ha matriz nesse registro. Retornando...\n");
                }else{
                    MostraMatriz(reg.m1);
                    printf("Mostrada com sucesso! Retornando...\n");
                }
            }else if(regresp==2){
                if(reg.reg2==0){
                    printf("Erro! Nao ha matriz nesse registro. Retornando...\n");
                }else{
                    MostraMatriz(reg.m2);
                    printf("Mostrada com sucesso! Retornando...\n");
                }
            }else if(regresp==3){
                if(reg.reg3==0){
                    printf("Erro! Nao ha matriz nesse registro. Retornando...\n");
                }else{
                    MostraMatriz(reg.m3);
                    printf("Mostrada com sucesso! Retornando...\n");
                }
            }else{
                printf("Resposta invalida! Retornando...\n");
            }
        }else if(resp=='4'){ //mostrar valor na posi
            printf("Em qual dos registros se encontra o valor? (1 ou 2)\n");
            scanf("%d", &regresp);
            getchar();
            if(regresp==1){
                if(reg.reg1!=1){
                    printf("Nao ha matriz nesse registro! Retornando...\n");
                }else{
                    int lin,col;
                    printf("Digite a linha e a coluna de onde se encontra o elemento.\n");
                    scanf("%d %d", &lin, &col);
                    getchar();
                    MostraValorPosi(reg.m1, lin, col);
                }
            }else if(regresp==2){
                if(reg.reg2!=1){
                    printf("Nao ha matriz nesse registro! Retornando...\n");
                }else{
                    int lin,col;
                    printf("Digite a linha e a coluna de onde se encontra o elemento.\n");
                    scanf("%d %d", &lin, &col);
                    getchar();
                    MostraValorPosi(reg.m2, lin, col);
                }
            }else{
                printf("Resposta invalida! Retornando...");
            }
        }else if(resp=='5'){ //somar matriz
            if(reg.reg1==0 || reg.reg2==0){
                printf("Primeiro insira matrizes em ambos os registradores! Retornando...\n");
            }else{
                if(reg.reg3==1){
                    DesalocaMatriz(reg.m3);
                    reg.reg3 = 0;
                    reg.m3 = malloc(sizeof(MatrizEsp));
                }
                SomaMatriz(reg.m1, reg.m2, reg.m3);
                reg.reg3 = 1;
                printf("Operacao concluida! Retornando...\n");
            }
        }else if(resp=='6'){ //multiplicar matriz
            if(reg.reg1==0 || reg.reg2==0){
                printf("Primeiro insira matrizes em ambos os registradores! Retornando...\n");
            }else{
                printf("Deseja realizar a operacao como Reg1 * Reg2 (1) ou Reg2 * Reg1 (2)?\n");
                char temp;
                scanf("%c", &temp);
                getchar();
                if(temp=='1'){
                    if(reg.reg3==1){
                        DesalocaMatriz(reg.m3);
                        reg.reg3 = 0;
                        reg.m3 = malloc(sizeof(MatrizEsp));
                    }
                    MultiplicaMatriz(reg.m1, reg.m2, reg.m3);
                    reg.reg3 = 1;
                    printf("Operacao concluida! Retornando...\n");
                }else if(temp=='2'){
                    if(reg.reg3==1){
                        DesalocaMatriz(reg.m3);
                        reg.reg3 = 0;
                        reg.m3 = malloc(sizeof(MatrizEsp));
                    }
                    MultiplicaMatriz(reg.m2, reg.m1, reg.m3);
                    reg.reg3 = 1;
                    printf("Operacao concluida! Retornando...\n");
                }else{
                    printf("Resposta invalida! Retornando...\n");
                }
            }
        }else if(resp=='e'){
            DesalocaMatriz(reg.m1);
            DesalocaMatriz(reg.m2);
            DesalocaMatriz(reg.m3);
            break;
        }else{
            printf("Resposta invalida! Retornando...\n");
        }
        scanf("%c", &resp);
        getchar();
    }
	return 0;
}
