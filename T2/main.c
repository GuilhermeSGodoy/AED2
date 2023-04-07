// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ciência da Computação

// Declaração de bibliotecas.
#include <stdio.h>
#include <stdlib.h>

// Constante que define o tamanho máximo do nome de um arquivo.
#define MAX 100

// Função que conta a quantidade de inversoes, recebendo como parâmetros o vetor,
// e três parâmetros que limitam suas partes.
unsigned long long contaInversoes(int v[], int p, int q, int r)
{
    // Declaração das variáveis que serão utilizadas ao longo da função.
    int i, j, k, tam;

    // Declaração do contador que receberá o resultado final. A utilização dos
    // identificadores long long se faz necessária por conta do tamanho das entradas
    // do problema.
    unsigned long long contInv = 0;

    // Atribuição dos parâmetros que serão utilizados nas iterações da função.
    i = p;
    j = q;
    k = 0;

    // Cálculo do tamanho do vetor.
    tam = r - p;

    // Alocação de um vetor auxiliar.
    int *w = malloc(tam * sizeof(int));

    // Loop que será utilizada para efetuar as devidas inversões.
    while (i < q && j < r)
    {
        // Caso a ordem já esteja certa, apenas copia no vetor auxiliar.
        if (v[i] <= v[j])
            w[k++] = v[i++];
        // Caso esteja fora de ordem, copia o outro valor e acrescenta no contador
        // de inversões.
        else {
            w[k++] = v[j++];
            contInv += q - i;
        }
    }

    // Atribuições finais ao vetor auxiliar.
    while (i < q)
        w[k++] = v[i++];

    while (j < r)
        w[k++] = v[j++];

    for (k = 0; k < tam; k++)
        v[p + k] = w[k];

    // Liberação da memória ocupada pelo vetor auxiliar.
    free(w);

    // Retorna o valor obtido.
    return contInv;
}

// Função auxiliar para a contagem de inversões, funcionando de maneira
// recursiva e ajustando os devidos parâmetros a cada iteração.
unsigned long long inverteRec(int v[], int p, int r)
{
    // Definição da variável que armazenará a metade do tamanho do vetor.
    int m;

    // Variável utilizada no cálculo da contagem de inversões.
    unsigned long long contInv = 0;

    // Caso ainda haja elementos a serem invertidos, segue a condição.
    if (r - p > 1)
    {
        // Definição da metade do tamanho do vetor, utilizado para dividi-lo
        // em duas partes utilizadas na chamada da função.
        m = (p + r) / 2;

        // Chamadas recursivas.
        contInv += inverteRec(v, p, m);
        contInv += inverteRec(v, m, r);

        // As inversões são calculadas a cada iteração.
        contInv += contaInversoes(v, p, m, r);
    }

    // Retorno do resultado calculado.
    return contInv;
}

// Função auxiliar que ajusta os parâmetros da primeira chamada da
// função recursiva que calcula o resultado.
unsigned long long inverteAux(int v[], int n)
{
    return inverteRec(v, 0, n);
}

// Programa principal
int main(int argc, char *argv[])
{
    // Abertura do arquivo e declaração de variáveis.
    char file_name[MAX];
    FILE *entrada;
    int i, n;
    unsigned long long contInv = 0;

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

    // Lê o tamanho do vetor do arquivo como primeiro parâmetro.
    fscanf(entrada, "%d", &n);

    // Aloca um vetor adequado.
    int *v = (int *)malloc(n * sizeof(int));

    // Leitura dos valores subsequentes.
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v[i]);

    // Chama a função para o cálculo do valor.
    contInv = inverteAux(v, n);

    // Exibe o valor na tela.
    printf("%llu\n", contInv);

    // Fecha o arquivo e encerra o programa.
    fclose(entrada);

    return 0;
}
