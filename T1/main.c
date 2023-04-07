// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ci�ncia da Computa��o

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o de uma estrutura Contato que ser� utilizada ao longo
// do programa para armazenar as informa��es de cada contato.
typedef struct contato Contato;

struct contato {
	char nome[100];
	char telefone[10];
	Contato *prox;
};

// Defini��o de uma tabela Hash com encadeamento.
static Contato **tabela = NULL;

// Defini��o do tamanho da tabela.
static int tamanho;

// Fun��o Hash que recebe o nome do contato e o tamanho da tabela como par�metros, de modo que
// retorne um valor que ser� utilizado na indexa��o da tabela.
int hash(char chave[], int tamanho) {
	int i, h = 0;

	for (i = 0; chave[i] != '\0'; i++)
		h = h + 127 * chave[i];

	h = h % tamanho;

	return h;
}

// Inicializa��o da tabela Hash, recebendo como par�metro o tamanho da tabela que ser� criada
// e aloca e inicializa a quantidade necess�ria de mem�ria.
void stInit(int tam) {
    // Atribui o valor ao tamanho da tabela.
	tamanho = tam;

	tabela = malloc(tamanho * sizeof(Contato *));

	for (int i = 0; i < tamanho; i++)
		tabela[i] = NULL;
}

// Efetua uma busca por um contato na tabela, a partir de seu nome, e exibe na tela
// as informa��es do contato ou se o contato n�o foi encontrado.
void stSearch(char nome[]) {
	int chave = hash(nome, tamanho);

	Contato *ptr;

	ptr = tabela[chave];

	while (ptr != NULL && strcmp(ptr->nome, nome) != 0)
		ptr = ptr->prox;

	if (ptr == NULL)
		printf("Contatinho nao encontrado\n");
	else
		printf("Contatinho encontrado: telefone %s\n", ptr->telefone);
}

// Inser��o de um contato na tabela, a partir do nome, telefone e um par�metro adicional que define se � uma
// inser��o de fato ou a altera��o de algum contato existente. O par�metro adicional "modo" define pelo valor 0
// uma inser��o e pelo valor 1 uma edi��o.
void stInsert(char nome[], char telefone[], int modo) {
	Contato *ptr;

	int chave = hash(nome, tamanho);

	ptr = tabela[chave];

	while (ptr != NULL && strcmp(ptr->nome, nome))
		ptr = ptr->prox;

	if (ptr == NULL){
        if (modo == 0) {
			ptr = malloc(sizeof(*ptr));

			strcpy(ptr->nome, nome);

			ptr->prox = tabela[chave];

			tabela[chave] = ptr;

			strcpy(ptr->telefone, telefone);
		}
		else
			printf("Operacao invalida: contatinho nao encontrado\n");
	}
	else {
		if (modo == 0)
			printf("Contatinho ja inserido\n");
		else
			strcpy(ptr->telefone, telefone);
	}
}

// Remo��o de um contato a partir de seu nome. Caso o contato n�o se encontre na tabela,
// exibe uma mensagem de erro.
void stDelete(char nome[]) {
	Contato *ptr, *aux;

	int key = hash(nome, tamanho);

	ptr = tabela[key];

	if(ptr == NULL) {
		printf("Operacao invalida: contatinho nao encontrado\n");
		return;
	}

	if(strcmp(ptr->nome, nome) == 0) {
		tabela[key] = ptr->prox;
		free(ptr);
		return;
	}

	while(ptr->prox != NULL && strcmp((ptr->prox)->nome, nome) != 0)
		ptr = ptr->prox;

	if(ptr->prox != NULL) {
		aux = ptr->prox;
		ptr->prox = aux->prox;
		free(aux);
	}
	else {
		printf("Operacao invalida: contatinho nao encontrado\n");
		return;
	}
}

// Libera os espa�os ocupados pela tabela e encerra sua utiliza��o.
void stFree(){
	Contato *p = NULL, *q = NULL;

	for (int i = 0; i < tamanho; i++) {
		p = tabela[i];
		while (p != NULL){
			q = p;
			p = p->prox;
			free(q);
		}
	}

	free(tabela);
	tabela = NULL;
}

int main() {
	// Inicializa��o da tabela com tamanho igual a 100 posi��es.
	stInit(100);

	// Vari�vel utilizada para ler o comando que ser� executado.
	char comando = -1;

	// Aloca��o da string que armazenar� o nome do contato.
	char *nome;
	nome = malloc(sizeof(char ) * 100);

	// Aloca��o da string que armazenar� o n�mero do contato.
	char *numero;
	numero = malloc(sizeof(char ) * 10);

	// Este loop � executado at� encontrar o comando 0, indicando o final da cadeia
	// de entradas.
    while (comando != '0') {
        // L� o comando a cada itera��o.
        scanf("%c", &comando);

        // Execu��o da inser��o
        if(comando == 'I') {
            // L� o nome e o n�mero e utiliza a fun��o stInsert para inseri-lo na tabela.
            scanf("%s", nome);
            scanf("%s", numero);
            stInsert(nome, numero, 0);
        }
        // Execu��o da busca
        else if(comando == 'P') {
            // L� o nome e utiliza a fun��o stSearch para busc�-lo na tabela.
            scanf("%s", nome);
            stSearch(nome);
        }
        // Execu��o da remo��o
        else if(comando == 'R') {
            // L� o nome e utiliza a fun��o stDelete para busc�-lo e remov�-lo da tabela.
            scanf("%s", nome);
            stDelete(nome);
        }
        // Execu��o da altera��o.
        else if(comando == 'A') {
            // L� o nome e o n�mero e utiliza a fun��o stInsert para busc�-lo na tabela e editar seus dados.
            scanf("%s", nome);
            scanf("%s", numero);
            stInsert(nome, numero, 1);
        }
    }

    // Libera��o do espa�o ocupado pelas strings e pela tabela
    free(nome);
    free(numero);
    stFree();

	return 0;
}
