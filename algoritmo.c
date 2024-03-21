/******************************************************************************
 * File Name: algoritmo.c
 *	      
 * Author:    Grupo 112
 * 
 * NAME
 *      algoritmo.c
 * 
 * SYNOPSYS
 *  #include <stdlib.h>
 *  #include <stdio.h>
 *  #include "ler_tabela1.h"
 *  #include "ler_dict.h"
 *  #include "grafo.h"
 *  #include "Item.h"
 *  #include "algoritmo.h"
 *  #include "heap.h"
 *  
 *	
 * DESCRIPTION 
 *  ficheiro do algortimo, onde executamos o algoritmo de dijkstra com auxilio
 * do heap
 * 
 * COMMENTS 
 *  
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "ler_tabela1.h"
#include "ler_dict.h"
#include "grafo.h"
#include "Item.h"
#include "algoritmo.h"
#include "heap.h"

/******************************************************************************************
 * less_cost()
 *
 * Arguments: 
 *      - node* cost1 (custo associado ao nó que está ligado ao nó mãe)
 *      - node* cost2 (custo associado a outro nó que está ligado ao nó mãe)
 * 
 * Returns: int
 * Side-Effects: none
 *
 * Description: faz a comparação entre os custos das ligações do nó mãe com cada um deles
 ******************************************************************************************/
int less_cost(node* cost1, node* cost2){
    if(cost1->cost >= cost2->cost) return 1;
    else return 0;
} 

/******************************************************************************************
 * dijkstra()
 *
 * Arguments: 
 *      - node* cost1 (custo associado ao nó que está ligado ao nó mãe)
 *      - node*** listv (lista de listas de listas com os vetor de cada tamanho de palavras
 * e em cada posição do vetor temos uma lista com a palvra mãe ligada aos seus adjacentes)
 *      - int tamanho_heap (contém um inteiro que será o tamanho a usar na criação do heap, sendo
 * o tamanho do mesmo) 
 *      - char*** dictionary (dicionario com as palavras ordenadas alfabéticamente)
 *      - int(*less_cost)(node* cost1 , node* cost2) função que compara custos
 *      - int word_size (será o tamanho das palavras do problema)
 *      - FILE *fp (ponteiro para o ficheiro a escrever)
 *      - int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 *      - int mid1 (posição da primeira palavra lida na tabela das palavras ordenadas)
 *      - int mid2 (posição da segunda palavra lida na tabela das palavras ordenadas)
 *      - int cost (mutações que podemos executar de cada vez)
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: implementação do algoritmo de dijkstra com a ajuda do heap
 ******************************************************************************************/
void dijkstra(node ***listv, int tamanho_heap, char ***dictionary, int(*less_cost)(node* cost1 , node* cost2), int word_size, FILE *fp, int indexes[100], int mid1, int mid2, int cost) //algoritmo de dijkstra
{
    
    int cost_graph;
    int prox_graph;
    int prox_indice = 0;
    Heap *pq;
    int i, j;
    int *visit; /*vetor onde marcamos como vistos os nós já visitados*/
    int *backtrack;
    int w=0, w_graph=0;
    int *weight;
    int idx1, cnt = 0;

    visit = (int*)calloc(indexes[word_size],sizeof(int));
    backtrack = (int*)calloc(indexes[word_size],sizeof(int));
    weight = (int*)calloc(indexes[word_size],sizeof(int)); /*Vetor de peso*/

    for (i = 0; i < indexes[word_size]; i++)
        weight[i] = 1000000;/*Pesos inicializadas a um valor muito alto*/


    pq = NewHeap(tamanho_heap, less_cost);

    /* peso do vértice 0 a si próprio é 0*/
    node* source = listv[word_size][mid1];
    Insert(pq, 0, source->parent, source->index);
    weight[mid1] = 0; /*inicializa o peso da fonte à fonte como 0*/
    backtrack[mid2] = -1;
    
    while(1){
        node* prox = RemoveMax(pq);
        if(prox == NULL) break;
        prox_indice = prox->index;

        /*Se o nó já foi visitado, retira-se o próximo elemento do heap*/
        if(visit[prox_indice] == 1) continue;
 
        if (prox_indice != mid1 && visit[prox_indice] == 0){
            backtrack[prox_indice] = prox->parent;
            w = prox->cost;
            visit[prox_indice] = 1;
        }

        if(prox_indice == mid1) visit[mid1] = 1;

        /*Se o nó retirado do heap for o destino, sai-se do ciclo*/
        if (prox_indice == mid2) break;

        node* aux = listv[word_size][prox_indice];

        /*Percorrer a lista de adjacencias da palavra atual*/
        while(aux->next != NULL){
            aux = getNextNodeLinkedList(aux);
            cost_graph = getCostLinkedList(aux);
            prox_graph = aux->index;
            w_graph = cost_graph + w;

            /*Se o prox_graph for o indice de uma palavra que ainda nao foi visitada
              e a distancia atual desta palavra à origem (w_graph) for menor ou igual 
              à que existe no vetor de distancias (weight), então faz sentido inserir 
              esta palavra no heap e atualiza-se a distancia no vetor de distancias*/
            if(visit[prox_graph] != 1 && cost_graph <= (cost*cost)){
                Insert(pq, w_graph, aux->parent, aux->index);
                weight[prox_graph] = w_graph;
            }
        }
    }
    
    idx1 = mid2;

    /*Se o destino está ligado a uma palavra, então encontrou-se um caminho entre destino e origem*/
    if(backtrack[mid2] != -1){
        fprintf(fp, "%s %d\n", dictionary[word_size][mid1], w);
        while (idx1 != mid1){
            idx1 = backtrack[idx1];
            cnt++;
        }

        for(i = 0; i < cnt; i++){
            idx1 = mid2;
            for(j = i+1; j < cnt; j++){
                idx1 = backtrack[idx1];
            }
            fprintf(fp, "%s\n", dictionary[word_size][idx1]);
        }
        fprintf(fp,"\n");
    }
    else{
        fprintf(fp, "%s %d\n", dictionary[word_size][mid1], -1);
        fprintf(fp, "%s\n\n", dictionary[word_size][mid2]);
    }

    free(visit);
    free(backtrack);
    free(weight);
    FreeHeap(pq);
    return;
}
