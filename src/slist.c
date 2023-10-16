#include "slist.h"

struct no_{
	char *verbete;
	char *def;
	no *prox;
	no *baixo;
	int nivel;
};

struct lista_{
	no *upleft;
	int max_nvl;
};

lista* criar_lista(){
	lista *l = (lista*)malloc(sizeof(lista));
	if(l == NULL)
		exit(1);

	l->max_nvl = 0;
	l->upleft = criar_no("\0", "\0");

	return l;
}

no* criar_no(char palavra[], char def[]){
	no *p;

	p = (no*) malloc(sizeof(no));

	p->verbete = (char*) malloc(strlen(palavra) + 1);
	strcpy(p->verbete, palavra);
	p->def = (char*) malloc(strlen(def) + 1);
	strcpy(p->def, def);
	p->prox = NULL;
	p->baixo = NULL;

	return p;
}

int random_nvl(){
	int nvl = 0;

	while((rand() % 2) < 1 && nvl < num_niveis)
		nvl++;

	return nvl;
}

void insercao(lista *l, char palavra[], char def[]){
	no *update[num_niveis], *atual = l->upleft, *p, *new_upleft;

	for(int i = 0; i < num_niveis; i++) update[i] = NULL;

	int nvl_novo = random_nvl();

	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) <= 0){
			atual = atual->prox;
		}

		update[i] = atual;

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	if(atual->verbete != NULL && strcmp(atual->verbete, palavra) == 0){
		printf("OPERACAO INVALIDA\n");
		return;
	}
	//nvl_novo = 2;
	int curr_level = 0;
	//nvl_novo = 0;

	while(curr_level <= l->max_nvl && curr_level <= nvl_novo){
		p = criar_no(palavra, def);

		if(curr_level == 0){
			//if(update[curr_level] != NULL)
				p->prox = update[curr_level]->prox;
			p->baixo = NULL;
		}
		else{
			//if(update[curr_level] != NULL)
				p->prox = update[curr_level]->prox;
			//if(update[curr_level] != NULL)
				p->baixo = update[curr_level - 1]->prox;
		}

		//if(update[curr_level] != NULL)
			update[curr_level]->prox = p;
		curr_level++;
	}

	for(int i = (l->max_nvl) + 1; i <= nvl_novo; i++){
		// prox e baixo
		p = criar_no(palavra, def);
		p->prox = NULL;
		if(update[i - 1] != NULL) p->baixo = update[i - 1]->prox;

		new_upleft = criar_no("\0", "\0");
		new_upleft->prox = p;
		new_upleft->baixo = l->upleft;

		l->upleft = new_upleft;
		update[i] = new_upleft;
	}


	if(nvl_novo > l->max_nvl) l->max_nvl = nvl_novo;
}

void alteracao(lista *l, char palavra[], char def[]){
	no *temp;
	
	temp = busca(l, palavra);

	if(temp->def != NULL)
		free(temp->def);

	temp->def = (char*) malloc(strlen(def) + 1);
	strcpy(temp->def, def);
}

void remocao(lista *l, char palavra[]){

}

no* busca(lista *l, char palavra[]){
	no *atual = l->upleft;

	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) <= 0){
			atual = atual->prox;
		}

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	if(atual != NULL && strcmp(atual->verbete, palavra) == 0){
		return atual;
	}

	return NULL;
}

void busca_definicao(lista* l, char palavra[]){
	no* res = busca(l, palavra);

	if(res == NULL){
		printf("OPERACAO INVALIDA\n");
		return;
	}

	printf("%s\n", res->def);
}

void impressao(lista *l, char inic){
	
}

void imprimir_lista(lista* l){
	no *atual = l->upleft;

	for(int i = l->max_nvl; i >= 0; i--){
		no* old_atual = atual;

		while(1){
			if(atual == NULL) break;

			printf("%s ", atual->verbete);
			atual = atual->prox;
		}
		printf("\n");

		if(old_atual->baixo != NULL)
			atual = old_atual->baixo;
	}
}

void liberar_camada(no *p){
	if(p == NULL)
		return;

	liberar_camada(p->prox);
	if(p->def != NULL) free(p->def);
	if(p->verbete != NULL) free(p->verbete);
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
