#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matriz.h"
#include "Menu.h"

Registro reg;

int main(void){
    reg.tamanhoAtual = 0;
    menuPrincipal();
    int i = 0;
    for(i = 0; i < reg.tamanhoAtual; i++){
        DesalocaMatriz(&reg.arrayPrincipal[i]);
    };
	return 0;
}
