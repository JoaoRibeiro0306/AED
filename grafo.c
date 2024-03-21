/******************************************************************************
 *
 * File Name: grafo.c
 *	      
 * Author:    GR112
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 * Ficheiro que contém a criação do grafo, e a sua inicialização
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ler_tabela1.h"
#include "ler_dict.h"
#include "grafo.h"
#include "Item.h"

/******************************************************************************
 * innit_array ()
 *
 * Arguments: 
 *      -int num_pal (nº de palavras que o nosso grafo vai ter)
 *      -int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 * 
 * Returns: node*** arr
 * Side-Effects: none
 *
 * Description: inicializa o vetor de cada tamanho de palavras
 *****************************************************************************/

node*** innit_array(int num_pal, int indexes[100], int probs[100])
{
    int i,j;
    struct node*** arr = NULL;

    arr = (node***)calloc(num_pal, sizeof(node**));
    
    for(i=0; i<num_pal; i++){
        if(indexes[i] != 0 ){
            arr[i] = (node**)calloc(indexes[i],sizeof(node*));
            for(j = 0; j < indexes[i] ; j++){
                arr[i][j] = (node*)calloc(1,sizeof(node));
                arr[i][j]->cost = 0;
                arr[i][j]->parent = -1;
                arr[i][j]->index = j;
            }
        }
    }

    return arr;
}

/******************************************************************************************
 * ***create_list ()
 *
 * Arguments: 
 *      - node ***listv
 *      - int ***dictionary (tabela de tabelas que contém o dicionário separado por tamanhos)
 *      - int biggest_word (maior palavra do dicionário)
 *      - int indexes[100] (vetor com o tamanho de cada dicionário)
 *      - int biggest_mut
 *      - int i (tamanho das palavras do grafo que estamos a criar)
 *      - int *conta_nos (contador para saber o numero de nos de cada grafo)
 * 
 * Returns: listv (vetor de vetor de lista de adjacências)
 * Side-Effects: none
 *
 * Description: Cria a lista de adjacências para um tamanho de palavra em especifico
 * inserindo também o custo e o indice do seu parente.
******************************************************************************************/
node*** create_list(node ***listv, char ***dictionary, int biggest_word, int indexes[100], int biggest_mut, int i, int* conta_nos) // cria o grafo
{
    int j, k;
    int cost = 0;

    if(indexes[i] != 0){
        for(j=0; j<indexes[i]; j++){
            for(k=j+1; k < indexes[i]; k++){
                cost = letter_diff(dictionary[i][j], dictionary[i][k], biggest_mut);
                if(cost == -1) continue;
                listv[i][k]->next = insert_edge(listv[i][k]->next, j, k, cost);
                listv[i][j]->next = insert_edge(listv[i][j]->next, k, j, cost);
                (*conta_nos)++;
            }
        }
    }
    return listv;
}

/******************************************************************************************
 * *insert_edge ()
 *
 * Arguments: 
 *      - node *listv (apenas uma lista do vetor de vetores de listas)
 *      - int indice (indice da palavra que queremos inserir no grafo)
 *      - int custo (custo de mutação entre a palavra parente e filho)
 * 
 * Returns: new (elemento da lista de adjacências)
 * Side-Effects: none
 *
 * Description: Insere uma aresta no grafo.
 ******************************************************************************************/
node* insert_edge(node *listv, int indice, int parent, int custo)
{
   node *new = (node*)calloc(1, sizeof(node)); 
   if(new == NULL){
    return NULL;
   }

   new -> cost = (custo*custo);
   new -> index = indice;
   new -> parent = parent;
   new -> next = listv;

   return new;
}

/******************************************************************************************
 * *getNextNodeLinkedList ()
 *
 * Arguments: 
 *      - node *node
 * 
 * Returns: node->next (apontador para o proximo elemento da lista) ou NULL (caso seja o
 * ultimo elemento da lista)
 * Side-Effects: none
 *
 * Description: Obtem o proximo elemento da lista.
 ******************************************************************************************/
node * getNextNodeLinkedList(node *node)
{
  return ((node == NULL) ? NULL : node->next);
}

/******************************************************************************************
 * *getCostLinkedList ()
 *
 * Arguments: 
 *      - node *node
 * 
 * Returns: node->cost (valor do custo da permutação) ou NULL
 * Side-Effects: none
 *
 * Description: Obtem o custo de uma permutação.
 ******************************************************************************************/
int getCostLinkedList(node *node){
    return ((node == NULL) ? -1 : node->cost);
}

/******************************************************************************************
 * letter_diff ()
 *
 * Arguments: 
 *      - char* palavra1 (palavra "pai")
 *      - char* palavra2 (palavra "filho")
 *      - int max_mut (maior permutação possível)
 * 
 * Returns: diff_letters*diff_letters (custo da permutação ao quadrado)
 * Side-Effects: none
 *
 * Description: Calcula o valor de uma aresta.
 ******************************************************************************************/
int letter_diff(char* palavra1, char* palavra2, int max_mut)
{
    int diff_letters=0;

   for(; *palavra1; ){
    if(diff_letters > max_mut) return -1;
    diff_letters += *(palavra1++) != *(palavra2++); 
   }
    return diff_letters;
} 

/******************************************************************************************
 * free_graph ()
 *
 * Arguments: 
 *      - node*** listv
 *      - int indexes[100]
 *      - int i (Tamanho das palavras do grafo que queremos dar free)
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Liberta a memória de um grafo.
 ******************************************************************************************/
void free_graph(node*** listv, int indexes[100], int i)
{
    int k;

    for(k = 0; k < indexes[i]; k++){
        free_linked_list(listv[i][k]);
    }
    free(listv[i]);
    
    return;
}

/******************************************************************************************
 * free_linked_list ()
 *
 * Arguments: 
 *      - node* Node (lista de adjacências)
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Liberta a memória de uma lista de adjacencias.
 ******************************************************************************************/
void free_linked_list(node* Node)
{
    node *next, *aux;

    for(aux = Node; aux != NULL; aux=next){
        next = aux -> next;
        free(aux);
    }

    return;
}
