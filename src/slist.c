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

	l->max_nvl = 0;
	l->upleft = criar_no("\0", "\0");

	return l;
}

no* criar_no(char palavra[], char def[]){
	no *p;

	p = (no*) malloc(sizeof(no));

	/* aloca o tamanho e copia a string */
	p->verbete = (char*) malloc(strlen(palavra) + 1);
	strcpy(p->verbete, palavra);
	p->def = (char*) malloc(strlen(def) + 1);
	strcpy(p->def, def);

	p->prox = NULL;
	p->baixo = NULL;

	return p;
}

int random_nvl(){
	/* decide qual nível da lista será aumentado */
	int nvl = 0;

	while((rand() % 2) < 1 && nvl < num_niveis - 1)
		nvl++;

	return nvl;
}

void insercao(lista *l, char palavra[], char def[]){
	if(busca(l, palavra) != NULL){
		printf("OPERACAO INVALIDA\r\n");
		return;
	}

	no *update[num_niveis], *atual = l->upleft, *p, *new_upleft;

	for(int i = 0; i < num_niveis; i++) update[i] = NULL;

	int nvl_novo = random_nvl();

	/* procura onde deve ser inserido a próxima palavra */
	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) < 0){
			atual = atual->prox;
		}

		update[i] = atual;

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	int curr_level = 0;

	/* atualiza as listas onde for necessário */
	while(curr_level <= l->max_nvl && curr_level <= nvl_novo){
		p = criar_no(palavra, def);

		if(curr_level == 0){
			p->prox = update[curr_level]->prox;
			p->baixo = NULL;
		}
		else{
			p->prox = update[curr_level]->prox;
			p->baixo = update[curr_level - 1]->prox;
		}

		update[curr_level]->prox = p;
		curr_level++;
	}

	for(int i = l->max_nvl + 1; i <= nvl_novo; i++){
		p = criar_no(palavra, def);
		p->prox = NULL;
		p->baixo = NULL;
		if(update[i - 1] != NULL) p->baixo = update[i - 1]->prox;

		new_upleft = criar_no("\0", "\0");
		new_upleft->prox = p;
		new_upleft->baixo = l->upleft;

		l->upleft = new_upleft;
		update[i] = new_upleft;
	}

	/* atualiza o nível da lista se for necessário */
	if(nvl_novo > l->max_nvl) l->max_nvl = nvl_novo;
}

void alteracao(lista *l, char palavra[], char def[]){
	no *temp;
	
	/* busca a palavra na lista e altera a sua definição */
	temp = busca(l, palavra);

	if(temp == NULL){
		printf("OPERACAO INVALIDA\r\n");
		return;
	}

	if(temp->def != NULL)
		free(temp->def);

	/* aloca o tamanho para a string e copia */
	temp->def = (char*) malloc(strlen(def) + 1);
	strcpy(temp->def, def);
}

void remocao(lista *l, char palavra[]){
	if(busca(l, palavra) == NULL){
		printf("OPERACAO INVALIDA\r\n");
		return;
	}

	no *update[num_niveis], *atual = l->upleft, *p;
	int curr_level = 0;

	for(int i = 0; i < num_niveis; i++) update[i] = NULL;

	/* procura a palavra a ser removida da lista */
	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) < 0){
			atual = atual->prox;
		}

		update[i] = atual;

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	/* remove e atualiza a lista */
	while(curr_level <= l->max_nvl){
		p = update[curr_level]->prox;
		if(p == NULL){
			curr_level++;
			continue;
		}
		update[curr_level]->prox = update[curr_level]->prox->prox;
		liberar_no(p);

		curr_level++;
	}

	while(l->upleft->prox == NULL){
		if(l->max_nvl == 0) break;
		p = l->upleft;
		l->upleft = l->upleft->baixo;
		l->max_nvl--;
		liberar_no(p);
	}
}

no* busca(lista *l, char palavra[]){
	no *atual = l->upleft;

	/* busca a palavra na lista*/
	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) <= 0){
			atual = atual->prox;
		}

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	/* retorna somente se a palavra foi encontrada */
	if(atual != NULL && strcmp(atual->verbete, palavra) == 0){
		return atual;
	}

	return NULL;
}

void busca_definicao(lista* l, char palavra[]){
	no* res = busca(l, palavra);

	if(res == NULL){
		printf("OPERACAO INVALIDA\r\n");
		return;
	}

	printf("%s %s\n", res->verbete, res->def);
}

void impressao(lista *l, char inic){
	no *atual = l->upleft;
	char palavra[2] = {inic, '\0'};

	/* aqui, o programa procura onde deve ser inserido a palavra que possui
	 * apenas o caracter inicial dado.
	 * Dessa forma, ele acha exatamente a primeira palavra que começa com a inicial */
	for(int i = l->max_nvl; i >= 0; i--){
		while(atual->prox != NULL && strcmp(atual->prox->verbete, palavra) < 0){
			atual = atual->prox;
		}

		if(i != 0 && atual->baixo != NULL)
			atual = atual->baixo;
	}

	atual = atual->prox;

	if(atual->verbete[0] != inic){
		printf("OPERACAO INVALIDA\r\n");
	}

	/* a partir daqui, basta iterar na lista enquanto que a palavra seja da inicial
	 * dada */
	while(atual != NULL && atual->verbete[0] == inic){
		printf("%s %s\n", atual->verbete, atual->def);
		atual = atual->prox;
	}
}

void liberar_no(no* p){
	if(p == NULL) return;

	if(p->def != NULL) free(p->def);
	if(p->verbete != NULL) free(p->verbete);
	free(p);
}

void liberar_camada(no *p){
	if(p == NULL)
		return;

	/* utiliza-se função recursiva para liberar as camadas */
	liberar_camada(p->prox);

	liberar_no(p);
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
