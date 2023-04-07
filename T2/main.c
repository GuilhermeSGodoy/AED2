// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ci�ncia da Computa��o

// Declara��o de bibliotecas.
#include <stdio.h>
#include <stdlib.h>

// Constante que define o tamanho m�ximo do nome de um arquivo.
#define MAX 100

// Fun��o que conta a quantidade de inversoes, recebendo como par�metros o vetor,
// e tr�s par�metros que limitam suas partes.
unsigned long long contaInversoes(int v[], int p, int q, int r)
{
    // Declara��o das vari�veis que ser�o utilizadas ao longo da fun��o.
    int i, j, k, tam;

    // Declara��o do contador que receber� o resultado final. A utiliza��o dos
    // identificadores long long se faz necess�ria por conta do tamanho das entradas
    // do problema.
    unsigned long long contInv = 0;

    // Atribui��o dos par�metros que ser�o utilizados nas itera��es da fun��o.
    i = p;
    j = q;
    k = 0;

    // C�lculo do tamanho do vetor.
    tam = r - p;

    // Aloca��o de um vetor auxiliar.
    int *w = malloc(tam * sizeof(int));

    // Loop que ser� utilizada para efetuar as devidas invers�es.
    while (i < q && j < r)
    {
        // Caso a ordem j� esteja certa, apenas copia no vetor auxiliar.
        if (v[i] <= v[j])
            w[k++] = v[i++];
        // Caso esteja fora de ordem, copia o outro valor e acrescenta no contador
        // de invers�es.
        else {
            w[k++] = v[j++];
            contInv += q - i;
        }
    }

    // Atribui��es finais ao vetor auxiliar.
    while (i < q)
        w[k++] = v[i++];

    while (j < r)
        w[k++] = v[j++];

    for (k = 0; k < tam; k++)
        v[p + k] = w[k];

    // Libera��o da mem�ria ocupada pelo vetor auxiliar.
    free(w);

    // Retorna o valor obtido.
    return contInv;
}

// Fun��o auxiliar para a contagem de invers�es, funcionando de maneira
// recursiva e ajustando os devidos par�metros a cada itera��o.
unsigned long long inverteRec(int v[], int p, int r)
{
    // Defini��o da vari�vel que armazenar� a metade do tamanho do vetor.
    int m;

    // Vari�vel utilizada no c�lculo da contagem de invers�es.
    unsigned long long contInv = 0;

    // Caso ainda haja elementos a serem invertidos, segue a condi��o.
    if (r - p > 1)
    {
        // Defini��o da metade do tamanho do vetor, utilizado para dividi-lo
        // em duas partes utilizadas na chamada da fun��o.
        m = (p + r) / 2;

        // Chamadas recursivas.
        contInv += inverteRec(v, p, m);
        contInv += inverteRec(v, m, r);

        // As invers�es s�o calculadas a cada itera��o.
        contInv += contaInversoes(v, p, m, r);
    }

    // Retorno do resultado calculado.
    return contInv;
}

// Fun��o auxiliar que ajusta os par�metros da primeira chamada da
// fun��o recursiva que calcula o resultado.
unsigned long long inverteAux(int v[], int n)
{
    return inverteRec(v, 0, n);
}

// Programa principal
int main(int argc, char *argv[])
{
    // Abertura do arquivo e declara��o de vari�veis.
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

    // L� o tamanho do vetor do arquivo como primeiro par�metro.
    fscanf(entrada, "%d", &n);

    // Aloca um vetor adequado.
    int *v = (int *)malloc(n * sizeof(int));

    // Leitura dos valores subsequentes.
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v[i]);

    // Chama a fun��o para o c�lculo do valor.
    contInv = inverteAux(v, n);

    // Exibe o valor na tela.
    printf("%llu\n", contInv);

    // Fecha o arquivo e encerra o programa.
    fclose(entrada);

    return 0;
}
