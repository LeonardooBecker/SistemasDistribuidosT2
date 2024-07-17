#include <stdio.h>
#include <stdlib.h>
#include "cisj.h"

#define RAIZ 0

typedef struct no {
	int id;
    int s;
    int visitado;
} no;

void imprime_nos(node_set* nodes)
{
    printf("nodes: ");
    for(int i = 0; i < nodes->size; i++)
    {
        printf("%d ", nodes->nodes[i]);
    }
    printf("\n");
}

void imprime_nod(no* nod)
{
    printf("%d, %d, %d\n", nod->id, nod->s, nod->visitado);
}

int verifica_processo_falho(node_set* nodes)
{
    int qnt_processos_falhos = 4;
    int *processosFalhos = (int*)malloc(sizeof(int)*qnt_processos_falhos);
    processosFalhos = (int[]){20,20,20,20};
    for(int j = 0; j < nodes->size; j++)
    {
        int existeFalho = 0;
        for(int i = 0; i < qnt_processos_falhos; i++)
        {
            if(nodes->nodes[j] == processosFalhos[i])
            {
                existeFalho = 1;
                break;
            }
        }
        if(!existeFalho)
        {
            return nodes->nodes[j];
        }
    }
    return -1;
}

void narvore(int raiz, int s, int dimensao)
{
    node_set* nodes;
    no *nod = (no*)malloc(sizeof(no));
    nod->id = raiz;
    nod->s = s;
    if(nod->id == RAIZ)
    {
        imprime_nod(nod);
        while(nod->s <= dimensao)
        {
            nodes = cis(raiz,nod->s);
            int no_oficial = verifica_processo_falho(nodes);
            narvore(no_oficial,nod->s,dimensao);
            nod->s += 1;
        }
    }
    else
    {
        if(nod->s > 1)
        {
            for(int i = 2; i <= nod->s; i++)
            {
                if(!nod->visitado && nod->id != -1)
                {
                    imprime_nod(nod);
                }
                nod->visitado = 1;
                nodes = cis(nod->id,i-1);
                int no_oficial = verifica_processo_falho(nodes);
                narvore(no_oficial,i-1,dimensao);
            }
        }
        else
        {
            if(nod->id != -1)
                imprime_nod(nod);
        }
    }


}

int main()
{
    int raiz = RAIZ;
    int dimensao = 4;
    narvore(raiz,1,dimensao);

}