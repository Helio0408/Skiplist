/*
Trabalho por:
Hélio Márcio Cabral Santos - NUSP: 14577862
Gabriel Martins Monteiro - NUSP: 14572099
*/

#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

int main(){
	srand(time(NULL));

	lista *l;
	char cmd[256];
	char verbete[tam_verb];
	char definicao[tam_def];
	char character;
	l = criar_lista();

	/* enquanto o usuário ainda digitar, continuamos lendo seus inputs */
	while(scanf("%s", cmd) == 1){
		if(!strcmp(cmd, "busca")){
			scanf("%s", verbete);
			busca_definicao(l, verbete);
		}
		else if(!strcmp(cmd, "insercao")){
			scanf("%s ", verbete);
			/* a função fgets é interessante nesse contexto pois ela
			   é capaz de ler strings com espaço */
			fgets(definicao, tam_def, stdin);
			definicao[strlen(definicao) - 2] = '\0'; // remover o '\n' que o fgets captura

			insercao(l, verbete, definicao);
		}
		else if(!strcmp(cmd, "alteracao")){
			scanf("%s ", verbete);
			fgets(definicao, tam_def, stdin);
			definicao[strlen(definicao) - 2] = '\0'; // remover o '\n' que o fgets captura

			alteracao(l, verbete, definicao);
		}
		else if(!strcmp(cmd, "remocao")){
			scanf("%s", verbete);
			remocao(l, verbete);
		}
		else if(!strcmp(cmd, "impressao")){
			scanf(" %c", &character);
			impressao(l, character);
		}
	}

	liberar_lista(l);
	return 0;
}
