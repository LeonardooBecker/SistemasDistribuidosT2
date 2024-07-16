#include <stdio.h>
#include <stdlib.h>
#include "cisj.h"

void arvore(int raiz, int s, int dimensao)
{
    node_set* nodes;
    printf("%d\n", nodes->nodes[0]);
    int raiz_antiga;

    while (s < dimensao)
    {
        nodes = cis(raiz,s);
        raiz_antiga = raiz;
        raiz = nodes->nodes[0];

        if (s == 1)
        {
            printf("%d = folha\n", raiz);
            raiz = raiz_antiga;
        }
        else
        {
            while (s != 1)
            {
                raiz_antiga = raiz;
                nodes = cis(raiz,s - 1);
                raiz = nodes->nodes[0];

                if (s == 1)
                {
                    printf("%d = folha\n", raiz);
                    raiz = raiz_antiga;
                }
            }    
        }

        s++;
    }
    
    
    // if(s>1)
    // {
    //     arvore(nodes->nodes[0], s-1, dimensao);
    // }

    // if (s != dimensao)
    // {
    //     arvore(raiz, s + 1, dimensao);
    // }
    
    // if (s > 1)
    // {
    //     arvore(nodes->nodes[0], s - 1, dimensao);
    // }

    // if (s == 1)
    // {
    //     printf("%d = folha\n", raiz);
    // }
    
        
}


int main()
{
    printf("Hello, World!\n"); 
    int raiz = 0;
    int dimensao = 3;
    node_set* nodes;

    arvore(0,1,dimensao);

    // for (int i = 1; i <= dimensao; i++)
    // {
    //     nodes = cis(raiz,i);
    //     for (int j = 0; j < nodes->size; j++)
    //     {   
    //         // se processo correto
    //         if(1)
    //         {
    //             printf("%d", nodes->nodes[j]);
                
    //             break;
    //         }
    //     }
    //     printf("\n");
    // }


    // printf("%d", nodes->nodes[j]);

}