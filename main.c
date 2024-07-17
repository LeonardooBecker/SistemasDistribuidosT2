#include <stdio.h>
#include <stdlib.h>
#include "cisj.h"

#define RAIZ 0

typedef struct no
{
    int id;
    int s;
    int visitado;
} no;

// Duas variáveis estáticas para armazenar os processos falhos e a quantidade de processos falhos ( e reduzir a passagem de parametro na função principal)
static int *processos_falhos;
static int qnt_processos_falhos;

void imprime_nos(node_set *nodes)
{
    printf("nodes: ");
    for (int i = 0; i < nodes->size; i++)
    {
        printf("%d ", nodes->nodes[i]);
    }
    printf("\n");
}

void imprime_nod(no *nod)
{
    printf("%d, %d, %d\n", nod->id, nod->s, nod->visitado);
}

int verifica_processo_falho(node_set *nodes)
{
    // Todos os processos obtidos pelo cisj
    for (int j = 0; j < nodes->size; j++)
    {
        int existeFalho = 0;
        // Para cada processo do cisj, percorre todos os processos verificando se este esta na lista de falhos
        for (int i = 0; i < qnt_processos_falhos; i++)
        {
            // Seta o processo como falho
            if (nodes->nodes[j] == processos_falhos[i])
            {
                existeFalho = 1;
                break;
            }
        }
        // Se o processo não está falho, retorna a identificação deste
        if (!existeFalho)
        {
            return nodes->nodes[j];
        }
    }
    // Se todos os processos estão falhos, retorna -1 ( sem caminho a seguir )
    return -1;
}

void narvore(int raiz, int s)
{
    node_set *nodes;
    no *nod = (no *)malloc(sizeof(no));
    nod->id = raiz;
    nod->s = s;
    // Verifica se o nó é um processo correto
    if (nod->id != -1)
    {
        // Se o nó tem s > 1 então ele é um nó interno
        if (nod->s > 1)
        {
            for (int i = 2; i <= nod->s; i++)
            {
                if (!nod->visitado)
                {
                    imprime_nod(nod);
                }
                nod->visitado = 1;
                nodes = cis(nod->id, i - 1);
                int no_oficial = verifica_processo_falho(nodes);
                narvore(no_oficial, i - 1);
            }
        }
        else
        {
            imprime_nod(nod);
        }
    }
}

typedef struct infos_iniciais
{
    int raiz;
    int dimensao;
    int *processos_falhos;
    int qnt_processos_falhos;
} infos_iniciais;

int main()
{
    // Variáveis com posição estática na memória para armazenar os processos falhos
    processos_falhos = (int *)malloc(sizeof(int) * 4);
    processos_falhos = (int[]){1, 4, 8, 9};
    qnt_processos_falhos = 4;

    // Hmmm, se organizar certin da pra criar uma struct com raiz dimensao e nós falhos
    int raiz = RAIZ;
    int dimensao = 4;

    narvore(raiz, dimensao + 1);
}