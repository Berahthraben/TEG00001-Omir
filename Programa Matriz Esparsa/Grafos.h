#include <stdio.h>
#include <stdlib.h>
#include "Matriz.h"

int mostrarGrauVertice(MatrizEsp *m, int vertice);
int comprimentoCaminho(MatrizEsp *m, char caminho[]);
int isSimples(MatrizEsp *m);
int isCompleto(MatrizEsp *m);
int isDesconexo(MatrizEsp *m);
int isDominante(MatrizEsp *m);
int isDirecionado(MatrizEsp *m);
