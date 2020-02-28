#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Menu.h"

extern Registro reg;

void menuPrincipal(){
    char resp = '0';
    while(resp!='e'){
        if(resp == '0'){
            printf("----MENU PRINCIPAL, DIGITE A OPÇÃO DESEJADA----\n"
            "0 - MOSTRAR ESSE DIÁLOGO NOVAMENTE\n"
            "1 - MENU MATRIZ\n"
            "2 - MENU GRAFO\n"
            "l - LIMPAR TELA\n"
            "e - ENCERRAR EXECUCAO DO PROGRAMA\n");
        }else if(resp == '1'){
            int ret = menuOperarMatriz();
            if(ret==1){
                break;
            }
        }else if(resp == '2'){
            if(reg.tamanhoAtual != 0){
                int ret = menuGrafo();
                if(ret==1){
                    break;
                }
            }else{
                printf("ERRO, NÃO HÁ MATRIZ DIGITADA. PRIMEIRO ADICIONE UMA ANTES DE OPERAR OS GRAFOS.\n");
            }
        }else if(resp == 'l' || resp == 'L'){
            //clrscr();
        }else if(resp!='e'){
            printf("RESPOSTA INVÁLIDA! SELECIONE UMA DAS OPÇÕES DO MENU MOSTRADO ANTERIORMENTE...\n"
            "OBS: DIGITE 0 PARA VER O MENU NOVAMENTE\n");
        }
        scanf("%c", &resp);
        getchar();
    }
}

int menuOperarMatriz(){ // Permite incluir/remover/alterar uma matriz no registro
    char resp = '0';
    while(resp!='e'){
        if(resp == '0'){
            printf("----MENU DE MATRIZES, DIGITE A OPCAO DESEJADA----\n"
            "0 - MOSTRAR ESSE DIÁLOGO NOVAMENTE\n"
            "1 - CRIAR MATRIZ EM UM DOS REGISTROS\n"
            "2 - INSERIR MATRIZ DE ARQUIVO EM UM REGISTRO (NÃO FUNCIONAL)\n"
            "3 - EDITAR UMA MATRIZ EXISTENTE\n"
            "4 - MOSTRAR UMA MATRIZ NO REGISTRO DADO\n"
            "5 - MOSTRAR VALOR NA POSICAO DADA\n"
            "r - RETORNAR AO MENU PRINCIPAL\n"
            "l - LIMPAR TELA\n"
            "e - ENCERRAR EXECUCAO DO PROGRAMA\n");
        }else if(resp == '1'){
            printf("DIGITE O NRO DO REGISTRO PARA INSERIR A MATRIZ. USE MÁXIMO+1 PRA CRIAR UM NOVO REGISTRO.\n"
            "QUANTIDADE DE MATRIZES NO REGISTRO (MAXIMO): %d\n"
            "OBS: COLOCAR UM VALOR MAIOR QUE ISSO INSERE NO FIM...\n", reg.tamanhoAtual+1);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual){ //Adicionar novo registro
                if(registroSelecionado != reg.tamanhoAtual){
                    registroSelecionado = reg.tamanhoAtual+1;
                    printf("TAMANHO MÁXIMO EXCEDIDO, INSERINDO NO REGISTRO %d", registroSelecionado);
                }
                printf("DIGITE O NÚMERO DE LINHAS E COLUNAS, SEPARADOS POR ESPAÇO.\n");
                int linhas, colunas;
                scanf("%d %d", &linhas, &colunas);
                getchar();
                if(linhas < 1 || colunas < 1){
                    printf("NÚMERO INVÁLIDO DIGITADO, USANDO VALOR MÍNIMO (1)");
                    if(linhas < 1){
                        linhas = 1;
                    }
                    if(colunas < 1){
                        colunas = 1;
                    }
                }
                if(reg.tamanhoAtual == 0){
                    reg.arrayPrincipal = malloc(sizeof(MatrizEsp));
                }else{
                    reg.arrayPrincipal = (MatrizEsp *)realloc(&reg.arrayPrincipal, sizeof(MatrizEsp)*reg.tamanhoAtual + 1);
                }
                reg.tamanhoAtual++;
                Inicializa_MatrizEsp(&reg.arrayPrincipal[reg.tamanhoAtual-1], linhas, colunas);
                printf("ADICIONADA COM SUCESSO! RETORNANDO...\n");
            }else if(registroSelecionado <= reg.tamanhoAtual && registroSelecionado > 0){ //Substituir registro
                printf("JÁ EXISTE UMA MATRIZ NO REGISTRO ATUAL, GOSTARIA DE SUBSTITUI-LA? (Y/N)\n");
                char confirm;
                scanf("%c", &confirm);
                getchar();
                if(confirm == 'Y' || confirm == 'y'){
                    printf("CONFIRMADO. DIGITE O NÚMERO OPERACOES C/ DE LINHAS E COLUNAS DA NOVA MATRIZ\n");
                    int linhas, colunas;
                    scanf("%d %d", &linhas, &colunas);
                    getchar();
                    if(linhas < 1 || colunas < 1){
                        printf("NÚMERO INVÁLIDO DIGITADO, USANDO VALOR MÍNIMO (1)\n");
                        if(linhas < 1){
                            linhas = 1;
                        }
                        if(colunas < 1){
                            colunas = 1;
                        }
                    }
                    if(reg.tamanhoAtual == 0){
                        reg.arrayPrincipal = malloc(sizeof(MatrizEsp));
                    }else{
                        reg.arrayPrincipal = (MatrizEsp *)realloc(&reg.arrayPrincipal, sizeof(MatrizEsp)*reg.tamanhoAtual + 1);
                    }
                    reg.tamanhoAtual++;
                    Inicializa_MatrizEsp(&reg.arrayPrincipal[reg.tamanhoAtual-1], linhas, colunas);
                    printf("ADICIONADA COM SUCESSO! RETORNANDO...\n");
                }else{
                    printf("SUBSTITUIÇÃO CANCELADA, RETORNANDO AO MENU DE MATRIZES...\n");
                }
            } else { //Seleção inválida
                printf("REGISTRO SELECIONADO INVÁLIDO. RETORNANDO AO MENU DE MATRIZES\n\n");
            }
        }else if(resp == '2'){
            printf("FUNÇÃO INDISPONIVEL, RETORNANDO AO MENU DE MATRIZES.\n");
        }else if(resp == '3'){
            if(reg.tamanhoAtual != 0){
                printf("QUAL REGISTRO GOSTARIA DE EDITAR? (min. 1, máx. %d)\n", reg.tamanhoAtual);
                int registroSelecionado;
                scanf("%d", &registroSelecionado);
                getchar();
                if(registroSelecionado > reg.tamanhoAtual  || registroSelecionado < 0){
                    printf("ERRO! REGISTRO SELECIONADO INVÁLIDO. RETORNANDO AO MENU DE MATRIZES.\n");
                }else{
                    printf("DIGITE A LINHA, COLUNA E O VALOR A SER INSERIDO, SEPARADOS POR ESPAÇO:\n");
                    int linhas, colunas, elemento;
                    scanf("%d %d %d", &linhas, &colunas, &elemento);
                    getchar();
                    EntradaMatriz en;
                    en.coluna = colunas;
                    en.valor = elemento;
                    EditaValor(&reg.arrayPrincipal[registroSelecionado-1], linhas, colunas, &en);
                    printf("EDITADA COM SUCESSO! RETORNANDO...\n");
                }
            }else{
                printf("ERRO, NÃO HÁ MATRIZ NOS REGISTROS. PRIMEIRO ADICIONE UMA ANTES DE OPERAR OS GRAFOS.\n");
            }
        }else if(resp == '4'){
            printf("QUAL REGISTRO GOSTARIA DE MOSTRAR? (min. 1, máx. %d)\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM MATRIZ. RETORNANDO AO MENU DE MATRIZES.\n");
            }else{
                MostraMatriz(&reg.arrayPrincipal[registroSelecionado]-1);
            }
        }else if(resp == '5'){
            printf("EM QUAL REGISTRO SE ENCONTRA A MATRIZ? (min) 1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM MATRIZ. RETORNANDO AO MENU DE MATRIZES.\n");
            }else{
                printf("DIGITE A LINHA E A COLUNA DO VALOR A SER MOSTRADO:\n");
                int linhas, colunas;
                scanf("%d %d", &linhas, &colunas);
                getchar();
                MostraValorPosi(&reg.arrayPrincipal[registroSelecionado-1], linhas, colunas);
            };
        }else if(resp == 'R' || resp == 'r'){
            printf("RETORNANDO AO MENU PRINCIPAL...\n");
            return 0;
        }else if(resp == 'l' || resp == 'L'){
            //clrscr();
        }else if(resp!='e'){
            printf("RESPOSTA INVÁLIDA! SELECIONE UMA DAS OPÇÕES DO MENU MOSTRADO ANTERIORMENTE...\n"
            "OBS: DIGITE 0 PARA VER O MENU NOVAMENTE");
        }else{
            return 1;
        }
        scanf("%c", &resp);
        getchar();
    }
}

int menuGrafo(){ // Testa se uma matriz escolhida possui uma caracteristica selecionada de grafos
    char resp = '0';
    while(resp!='e'){
        if(resp == '0'){
            printf("----MENU DE GRAFOS, DIGITE A OPÇÃO DESEJADA----\n"
            "0 - MOSTRAR ESSE DIÁLOGO NOVAMENTE\n"
            "1 - MOSTRAR GRAU DE VÉRTICE\n"
            "2 - POSSUI LOOP/ARCO PARALELO\n"
            "3 - GRAFO COMPLETO\n"
            "4 - GRAFO DESCONEXO\n"
            "5 - GRAFO C/ DOMINANCIA\n"
            "6 - GRAFO SIMPLES\n"
            "7 - GRAFO DIRECIONADO\n"
            "8 - TESTAR COMPRIMENTO DE CAMINHO\n"
            "r - RETORNAR AO MENU PRINCIPAL\n"
            "l - LIMPAR TELA\n"
            "e - ENCERRAR EXECUCAO DO PROGRAMA\n");
        }else if(resp == '1'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM MATRIZ. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                if(reg.arrayPrincipal[registroSelecionado-1].lin != reg.arrayPrincipal[registroSelecionado-1].col){
                    printf("ERRO! MATRIZ SELECIONADA NAO E UM GRAFO VALIDO! RETORNANDO AO MENU DE GRAFOS.\n");
                }else{
                    int auxColunas = reg.arrayPrincipal[registroSelecionado-1].col;
                    printf("DIGITE O NUMERO DO VERTICE A SER TESTADO. MÁXIMO: %d\n", auxColunas);
                    int nroVertice;
                    scanf("%d", &nroVertice);
                    getchar();
                    if(nroVertice > auxColunas){
                        printf("ERRO! VERTICE INEXISTENTE. RETORNANDO AO MENU DE GRAFOS.\n");
                    }else{
                        int grau = mostrarGrauVertice(&reg.arrayPrincipal[registroSelecionado-1], nroVertice);
                        if(grau != -1){
                            printf("GRAU DO VERTICE: %d\n", grau);
                            printf("RETORNANDO AO MENU DE GRAFOS...");
                        };
                    };
                };
            };
        }else if(resp == '2'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int loop = hasLoop(&reg.arrayPrincipal[registroSelecionado]);
                if(loop == 1){
                    printf("GRAFO POSSUI LOOP E/OU ARCO PARALELO.\n");
                }else{
                    printf("GRAFO NAO POSSUI LOOP E/OU ARCO PARALELO.\n");
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == '3'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int completo = isCompleto(&reg.arrayPrincipal[registroSelecionado]);
                if(completo == 1){
                    printf("GRAFO COMPLETO.\n");
                }else{
                    printf("GRAFO NAO EH COMPLETO.\n");
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == '4'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int desconexo = isDesconexo(&reg.arrayPrincipal[registroSelecionado]);
                if(desconexo == 1){
                    printf("GRAFO DESCONEXO.\n");
                }else{
                    printf("GRAFO NAO EH DESCONEXO.\n");
                };
                printf("RETORNANDO AO MENU Dprintf("")E GRAFOS...\n");
            };
        }else if(resp == '5'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int dominante = isDominante(&reg.arrayPrincipal[registroSelecionado]);
                if(dominante != 0){
                    printf("GRAFO POSSUI VERTICE DOMINANTE. VERTICE: %d\n", dominante);
                }else{
                    printf("GRAFO NAO POSSUI VERTICE DOMINANTE.\n");
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == '6'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int simples = isSimples(&reg.arrayPrincipal[registroSelecionado]);
                if(simples == 1){
                    printf("GRAFO SIMPLES.\n");
                }else{
                    printf("GRAFO NAO EH SIMPLES.\n");
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == '7'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM MATRIZ. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                int direcionado = isDirecionado(&reg.arrayPrincipal[registroSelecionado]);
                if(direcionado == 1){
                    printf("GRAFO DIRECIONADO.\n");
                }else{
                    printf("GRAFO NAO EH DIRECIONADO.\n");
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == '8'){
            printf("DIGITE O REGISTRO ONDE SE ENCONTRA O GRAFO A SER TESTADO. (min)1 - (max)%d\n", reg.tamanhoAtual);
            int registroSelecionado;
            scanf("%d", &registroSelecionado);
            getchar();
            if(registroSelecionado > reg.tamanhoAtual || registroSelecionado < 0){
                printf("ERRO! REGISTRO SELECIONADO NÃO CONTEM GRAFO. RETORNANDO AO MENU DE GRAFOS.\n");
            }else{
                printf("DIGITE A STRING QUE REPRESENTA O CAMINHO A SER PERCORRIDO.\n"
                "OBS: SE O GRAFO POSSUIR 10+ VERTICES, DIGITE OS NUMEROS MENORES QUE ISSO COM 0 NA FRENTE.\n");
                char caminho[100];
                scanf("%s", caminho);
                getchar();
                int comp = comprimentoCaminho(&reg.arrayPrincipal[registroSelecionado], caminho);
                if(comp!=-1){
                    printf("COMPRIMENTO DO CAMINHO EH %d", comp);
                };
                printf("RETORNANDO AO MENU DE GRAFOS...\n");
            };
        }else if(resp == 'R' || resp == 'r'){
            printf("RETORNANDO AO MENU PRINCIPAL...\n");
            return 0;
        }else if(resp == 'l' || resp == 'L'){
            //clrscr();
        }else if(resp!='e'){
            printf("RESPOSTA INVÁLIDA! SELECIONE UMA DAS OPÇÕES DO MENU MOSTRADO ANTERIORMENTE...\n"
            "OBS: DIGITE 0 PARA VER O MENU NOVAMENTE\n");
        }else{
            return 1;
        };
        scanf("%c", &resp);
        getchar();
    };
};
