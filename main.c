#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cisj.h"

typedef struct proc_info
{
    int id;
    int s;
    int visitado;
} proc_info;

// Duas variáveis estáticas para armazenar os processos falhos e a quantidade de processos falhos ( e reduzir a passagem de parametro na função principal)
static int *processos_falhos;
static int qnt_processos_falhos;

void imprime_processo(proc_info *processo)
{
    printf("%d, %d, %d\n", processo->id, processo->s, processo->visitado);
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

void arvore(int raiz, int s)
{
    node_set *processos_possiveis;
    proc_info *processo = (proc_info *)malloc(sizeof(proc_info));
    processo->id = raiz;
    processo->s = s;
    // Verifica se o processo é um processo correto
    if (processo->id != -1)
    {
        // Se o processo tem s > 1 então ele é um processo interno
        if (processo->s > 1)
        {
            // Percorre por todos os s processos possíveis
            for (int i = 2; i <= processo->s; i++)
            {
                if (!processo->visitado)
                {
                    imprime_processo(processo);
                    processo->visitado = 1;
                }
                processos_possiveis = cis(processo->id, i - 1);
                int no_oficial = verifica_processo_falho(processos_possiveis);
                arvore(no_oficial, i - 1);
            }
        }
        else
        {
            if (!processo->visitado)
            {
                imprime_processo(processo);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if(argc < 3){
        printf("Falta argumentos\n");
        return 1;
    }
    int raiz = atoi(argv[1]);
    int dimensao = atoi(argv[2]);
    qnt_processos_falhos = atoi(argv[3]);
    processos_falhos = (int *)malloc(sizeof(int) * qnt_processos_falhos);
    memset(processos_falhos, -1, sizeof(int) * qnt_processos_falhos);
    char *processos = argv[4];
    int count = 0;
    char *procs = strtok(processos, " ");
    while (procs != NULL)
    {
        processos_falhos[count] = atoi(procs);
        procs = strtok(NULL, " ");
        count++;
    }

    arvore(raiz, dimensao + 1);
}