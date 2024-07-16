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

void narvore(int raiz, int s, int dimensao)
{
    node_set* nodes;
    no *nod = (no*)malloc(sizeof(no));
    nod->id = raiz;
    nod->s = s;
    if(nod->id == RAIZ)
    {
        nodes = cis(raiz,s);
        narvore(nodes->nodes[0],s,dimensao);
        while(nod->s < dimensao)
        {
            nodes = cis(raiz,nod->s+1);
            nod->s += 1;
            narvore(nodes->nodes[0],nod->s,dimensao);
        }
    }
    else
    {
        if(nod->s > 1)
        {
            for(int i = 2; i <= nod->s; i++)
            {
                if(!nod->visitado)
                {
                    imprime_nod(nod);
                }
                nod->visitado = 1;
                nodes = cis(nod->id,i-1);
                narvore(nodes->nodes[0],i-1,dimensao);
            }
        }
        else
        {
            imprime_nod(nod);
        }
    }


}

int main()
{
    int raiz = 0;
    int dimensao = 4;
    narvore(raiz,1,dimensao);

}