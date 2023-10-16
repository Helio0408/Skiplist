#define tam_verb 50
#define tam_def 140
#define num_niveis 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct lista_ lista;
typedef struct no_ no;

//cria um dicionario
lista* criar_lista(void);

//cria um nó
no* criar_no(char palavra[], char def[]);

//retorna um número aleatorio de níveis
int random_nvl();

//insere palavra, com a definição def, no dicionário
void insercao(lista *l, char palavra[], char def[]);

//altera a definição de palavra para def
void alteracao(lista *l, char palavra[], char def[]);

//remove palavra do dicionário
void remocao(lista *l, char palavra[]);

// retorna o no da palavra, caso não ache, retorna NULL
no* busca(lista *l, char palavra[]);

// busca e imprime a definição da palavra
void busca_definicao(lista* l, char palavra[]);

/* 
imprime todas as palavras iniciadas pelo caractere inic seguidas por suas 
respectivas definições em ordem alfabética. Cada palavra (com sua respectiva
definição) é impressa em uma linha diferente.
*/
void impressao(lista *l, char inic);

/* DEBUG */
void imprimir_lista(lista* l);

/*
libera toda uma camada da lista
(não usar, apenas para uso recursivo em liber_lista)
*/
void liberar_camada(no *p);

//libera toda a lista
void liberar_lista(lista *l);
