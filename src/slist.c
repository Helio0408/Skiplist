#include "slist.h"

struct no_{
	char *verbete;
	char *def;
	no *prox;
	no *baixo;
};

struct lista_{
	no *upleft;
	int max_nvl;
};

lista* criar_lista(){
	lista *l = (lista*)malloc(sizeof(lista));
	if(l == NULL)
		exit(1);

	l->max_nvl = 1;
	l->upleft = (no*) malloc(sizeof(no));

	if(l->upleft == NULL)
		exit(1);

	l->upleft->verbete = '\0';
	l->upleft->def = '\0';
	l->upleft->prox = NULL;
	l->upleft->baixo = NULL;

	return l;
}

no* criar_no(char palavra[], char def[]){
	no *p;

	p = (no*) malloc(sizeof(no));
	p->verbete = palavra;
	p->def = def;
	p->prox = NULL;
	p->baixo = NULL;

	return p;
}

int random_nvl(){
	int nvl = 1;

	while((rand() % 2) < 1 && nvl < num_niveis)
		nvl++;

	return nvl;
}

void insercao(lista *l, char palavra[], char def[]){
	no *update[num_niveis], *atual = l->upleft, *p;

	int nvl_novo = random_nvl();

	for(int i = l->max_nvl - 1; i >= 0; i--){
		while( atual->prox != NULL && strcmp(atual->prox->verbete, palavra) < 0)
			atual = atual->prox;

		update[i] = atual;

		if(atual->baixo != NULL)
			atual = atual->baixo;
	}

	if(strcmp(atual->verbete, palavra) == 0){
		printf("OPERACAO INVALIDA");
		return;
	}

	if(l->max_nvl < nvl_novo){
		for(int i = (l->max_nvl); i < nvl_novo; i++){
			p = criar_no(palavra, def);
			update[i] =  criar_no('\0', '\0');

			update[i]->prox = p;
			p->baixo = update[i-1]->prox;
		}

		l->upleft = update[nvl_novo - 1];

		l->max_nvl = nvl_novo;
	}

	for(int i = 0; i < nvl_novo; i++){
		p = criar_no(palavra, def);

		p->prox = update[i]->prox;
		update[i]->prox = p;

		if(i > 0)
			p->baixo = update[i-1]->prox;
	}

}

/*
void alteracao(lista *l, char palavra[], char def[]){
	no *temp;
	
	temp = busca(l, palavra);

	temp->def = def;
}

void remocao(lista *l, char palavra[]){

}

no* busca(lista *l, char palavra[]){
	
}

void impressao(lista *l, char inic){
	
}
*/

void liberar_camada(no *p){
	if(p == NULL)
		return;

	liberar_camada(p->prox);
	free(p);
}

void liberar_lista(lista *l){
	no *n_atual = l->upleft;
    no *n_abaixo;

    while (n_atual != NULL) {
        n_abaixo = n_atual->baixo;
        liberar_camada(n_atual);
        n_atual = n_abaixo;
    }

    free(l);
}