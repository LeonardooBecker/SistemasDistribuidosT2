#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cisj.h"


typedef struct proc_info
{
    int id;
    int s;
    int visitado;
} proc_info;

typedef struct arvore_armazenada
{
    int identificador;
    int linha;
} arvore_armazenada;

// Variáveis estáticas (globais) para armazenar os identificadores e a quantidade de processos falhos (reduzindo a passagem de parametro na função principal)
static int *processos_falhos;
static int qnt_processos_falhos;

// Função para imprimir a árvore de armazenamento
void imprime_arvore(arvore_armazenada *arv, int dimensao)
{
    for (int i = 0; i <= dimensao; i++)
    {
        for(int j = 0; j < pow(2, dimensao); j++)
        {
            if(arv[j].linha == i)
            {
                printf("%2d ", arv[j].identificador);
            }
        }
        printf("\n");
    }
}

// Função para imprimir as infomações do processo
void imprime_processo(proc_info *processo)
{
    // Desabilitado
    if(!1)
        printf("%d, %d, %d\n", processo->id, processo->s, processo->visitado);
}

// Função para buscar o primeiro processo não falho dentre os processos possíveis
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

void arvore(int raiz, int s, int linha, arvore_armazenada *arv)
{
    node_set *processos_possiveis;
    proc_info *processo = (proc_info *)malloc(sizeof(proc_info));
    processo->id = raiz;
    processo->s = s;
    processo->visitado = 0;
    // Verifica se o processo é um processo correto
    if (processo->id != -1)
    {
        // Se o processo tem s > 1 então ele é um processo interno
        if (processo->s > 1)
        {
            // Percorre por todos os s processos possíveis
            for (int s = 2; s <= processo->s; s++)
            {
                // Só volta a imprimir o processo caso ele ainda não tenha sido visitado
                if (!processo->visitado)
                {
                    imprime_processo(processo);
                    processo->visitado = 1;
                }

                // Obtém os processos possíveis para o processo atual
                processos_possiveis = cis(processo->id, s - 1);
                // Obtém o primeiro processo não falho dentre os possíveis
                int processo_oficial = verifica_processo_falho(processos_possiveis);
                arv[processo_oficial].identificador = processo_oficial;
                arv[processo_oficial].linha = linha;
                arvore(processo_oficial, s - 1, linha + 1, arv);
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
    // Sessão inicial para tratar os dados obtidos por argumemnto
    if(argc < 3){
        printf("Falta argumentos\n");
        return 1;
    }
    int raiz = atoi(argv[1]);
    int dimensao = atoi(argv[2]);
    qnt_processos_falhos = atoi(argv[3]);
    if(qnt_processos_falhos > 0)
    {
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
    }
    // ======   Fim sessão recepção de dados

    // Inicializa arvore de armazenamento para imprimir posteriormente
    arvore_armazenada *arv = (arvore_armazenada *)malloc(sizeof(arvore_armazenada) * pow(2, dimensao));
    arv[raiz].identificador = raiz;
    arv[raiz].linha = 0;

    // Incia a recursão de criação da árvore a partir da raiz
    arvore(raiz, dimensao + 1, 1, arv);

    imprime_arvore(arv, dimensao);

    free(arv);
    free(processos_falhos);
}