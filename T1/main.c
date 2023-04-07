// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ciência da Computação

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de uma estrutura Contato que será utilizada ao longo
// do programa para armazenar as informações de cada contato.
typedef struct contato Contato;

struct contato {
	char nome[100];
	char telefone[10];
	Contato *prox;
};

// Definição de uma tabela Hash com encadeamento.
static Contato **tabela = NULL;

// Definição do tamanho da tabela.
static int tamanho;

// Função Hash que recebe o nome do contato e o tamanho da tabela como parâmetros, de modo que
// retorne um valor que será utilizado na indexação da tabela.
int hash(char chave[], int tamanho) {
	int i, h = 0;

	for (i = 0; chave[i] != '\0'; i++)
		h = h + 127 * chave[i];

	h = h % tamanho;

	return h;
}

// Inicialização da tabela Hash, recebendo como parâmetro o tamanho da tabela que será criada
// e aloca e inicializa a quantidade necessária de memória.
void stInit(int tam) {
    // Atribui o valor ao tamanho da tabela.
	tamanho = tam;

	tabela = malloc(tamanho * sizeof(Contato *));

	for (int i = 0; i < tamanho; i++)
		tabela[i] = NULL;
}

// Efetua uma busca por um contato na tabela, a partir de seu nome, e exibe na tela
// as informações do contato ou se o contato não foi encontrado.
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

// Inserção de um contato na tabela, a partir do nome, telefone e um parâmetro adicional que define se é uma
// inserção de fato ou a alteração de algum contato existente. O parâmetro adicional "modo" define pelo valor 0
// uma inserção e pelo valor 1 uma edição.
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

// Remoção de um contato a partir de seu nome. Caso o contato não se encontre na tabela,
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

// Libera os espaços ocupados pela tabela e encerra sua utilização.
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
	// Inicialização da tabela com tamanho igual a 100 posições.
	stInit(100);

	// Variável utilizada para ler o comando que será executado.
	char comando = -1;

	// Alocação da string que armazenará o nome do contato.
	char *nome;
	nome = malloc(sizeof(char ) * 100);

	// Alocação da string que armazenará o número do contato.
	char *numero;
	numero = malloc(sizeof(char ) * 10);

	// Este loop é executado até encontrar o comando 0, indicando o final da cadeia
	// de entradas.
    while (comando != '0') {
        // Lê o comando a cada iteração.
        scanf("%c", &comando);

        // Execução da inserção
        if(comando == 'I') {
            // Lê o nome e o número e utiliza a função stInsert para inseri-lo na tabela.
            scanf("%s", nome);
            scanf("%s", numero);
            stInsert(nome, numero, 0);
        }
        // Execução da busca
        else if(comando == 'P') {
            // Lê o nome e utiliza a função stSearch para buscá-lo na tabela.
            scanf("%s", nome);
            stSearch(nome);
        }
        // Execução da remoção
        else if(comando == 'R') {
            // Lê o nome e utiliza a função stDelete para buscá-lo e removê-lo da tabela.
            scanf("%s", nome);
            stDelete(nome);
        }
        // Execução da alteração.
        else if(comando == 'A') {
            // Lê o nome e o número e utiliza a função stInsert para buscá-lo na tabela e editar seus dados.
            scanf("%s", nome);
            scanf("%s", numero);
            stInsert(nome, numero, 1);
        }
    }

    // Liberação do espaço ocupado pelas strings e pela tabela
    free(nome);
    free(numero);
    stFree();

	return 0;
}
