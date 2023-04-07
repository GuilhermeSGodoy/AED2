// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ci�ncia da Computa��o

// Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>

// Valor m�ximo para a leitura do arquivo (modeloFILE.c)
#define MAX 100

// Declara��o de um n� para o grafo
typedef struct noh Noh;

struct noh {
	// V�rtice objetivo do arco em quest�o
	int obj;
	// Aponta para o pr�ximo n�
	Noh *prox;
};

// Declara��o da estrutura grafo
typedef struct grafo *Grafo;

struct grafo {
	// Declara��o de uma lista de adjac�ncia
	Noh **Adj;
	// Quantidade de v�rtices
	int n_vert;
	// Quantidade de arestas
	int n_ar;
};

// Declara��o da estrutura fila
typedef struct fila Fila;

struct fila {
	// Vetor que armazenar� a fila
	int *vet;
	// �ndice de in�cio da fila
	int inicio;
	// �ndice do final da fila
	int fim;
};

// Inicializa��o da fila vazia
Fila *iniciaFila()
{
	Fila *F = malloc(sizeof *F);
	F->vet = (int *)malloc(MAX * sizeof(int));

	F->inicio = 0;
	F->fim = 0;

	return F;
}

// Adiciona um elemento na fila
void addFila(Fila *F, int n)
{
	F->vet[F->fim] = n;
	(F->fim)++;
}

// Remove um elemento da fila e retorna o elemento
// removido
int remFila(Fila *F)
{
	int x;

	x = F->vet[F->inicio];
	F->inicio++;

	return x;
}

// Zera a fila
void zeraFila(Fila *F)
{
	F->inicio = 0;
	F->fim = 0;
}

// Verifica se a fila est� vazia
int verificaFilaVazia(Fila *F)
{
	if (F->inicio == F->fim)
        return 1;
	else
        return 0;
}

// Libera a mem�ria ocupada pela fila
Fila *liberaFila(Fila *F)
{
	free(F->vet);
	free(F);

	F = NULL;

	return F;
}

// Inicializa o grafo
Grafo iniciaGrafo(int n)
{
	int i;

	Grafo G = malloc(sizeof *G);

	G->n_vert = n;
	G->n_ar = 0;
	G->Adj = malloc(n * sizeof(Noh *));

	for (i = 0; i < n; i++)
        G->Adj[i] = NULL;

	return G;
}

// Adiciona um elemento no grafo
void addGrafo(Grafo G, int v, int w)
{
	Noh *p;

	for (p = G->Adj[v]; p != NULL; p = p->prox)
		if (p->obj == w)
            		return;

	p = malloc(sizeof(Noh));

	p->obj = w;
	p->prox = G->Adj[v];

	G->Adj[v] = p;
	G->n_ar++;
}

// Libera a mem�ria ocupada pelo grafo
Grafo liberaGrafo(Grafo G)
{
	int i;
	Noh *p;

	for (i = 0; i < G->n_vert; i++)
    	{
		p = G->Adj[i];

		while (p != NULL)
		{
			G->Adj[i] = p;
			p = p->prox;
			free(G->Adj[i]);
		}

		G->Adj[i] = NULL;
	}

	free(G->Adj);
	G->Adj = NULL;
	free(G);

	G = NULL;

	return G;
}

// Verifica se o grafo � bipartido
int verificacaoGBipartido(Grafo G)
{
	int inicio, p_grafo, p_fila;
	int *dist;
	Fila *fila;
	Noh *p;

	dist = malloc(G->n_vert * sizeof(int));
	fila = iniciaFila();

	for (p_grafo = 0; p_grafo < G->n_vert; p_grafo++)
        dist[p_grafo] = -1;

	for (inicio = 0; inicio < G->n_vert; inicio++)
    	{
		dist[inicio] = 0;

		addFila(fila, inicio);

		while (!verificaFilaVazia(fila))
	        {
			p_grafo = remFila(fila);
			p = G->Adj[p_grafo];

			while (p != NULL)
			{
				p_fila = p->obj;

				if (dist[p_fila] == -1)
				{
					dist[p_fila] = dist[p_grafo] + 1;
					addFila(fila, p_fila);
				}
                		else
               			{
					if (dist[p_fila]%2 != (dist[p_grafo] + 1) % 2)
					{
						fila = liberaFila(fila);
						return 0;
					}
				}

				p = p->prox;
			}
		}

		for (p_grafo = 0; p_grafo < G->n_vert; p_grafo++)
            		dist[p_grafo] = -1;

		zeraFila(fila);
	}

	fila = liberaFila(fila);

	return 1;
}

// C�digo presente no arquivo modeloFILE.c
int main(int argc, char *argv[])
{
	char file_name[MAX];
	FILE *entrada;

	int i, j, qtde_alunos, qtde_perguntas, pergunta;
	Grafo alunos;

	if (argc != 1)
    	{
        	printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        	return 0;
    	}

	scanf("%s", file_name);

    	entrada = fopen(file_name, "r");

    	if (entrada == NULL)
    	{
        	printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        	exit(EXIT_FAILURE);
    	}

    	// Fim do c�digo presente no arquivo modeloFILE.c

    	// Leitura dos dados de entrada
    	fscanf(entrada, "%d", &qtde_alunos);
		alunos = iniciaGrafo(qtde_alunos);

	// Constru��o do grafo a partir das fun��es apresentadas
	// anteriormente
	for (i = 0; i < qtde_alunos; i++)
    	{
		fscanf(entrada, "%d", &qtde_perguntas);

		for (j = 0; j < qtde_perguntas; j++)
        	{
			fscanf(entrada, "%d", &pergunta);
			addGrafo(alunos, i, pergunta);
		}
	}

	// Verifica��o do resultado
    	if (verificacaoGBipartido(alunos) == 0)
        	printf("Impossivel\n");
    	else
        	printf("Vai ter debate\n");

    	// Libera a mem�ria alocada, fecha o arquivo e encerra
    	// o programa
    	alunos = liberaGrafo(alunos);

    	fclose(entrada);

    	return 0;
}
