#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

int main(){
	srand(time(NULL));

	lista *l;

	l = criar_lista();

	liberar_lista(l);
	return 0;
}