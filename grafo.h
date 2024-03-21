/******************************************************************************
 * File Name: grafo.h
 *	      
 * Author: Grupo 112
 * 
 * NAME
 *      algoritmo.h - protótipos
 *  
 *	
 * DESCRIPTION 
 *  contém os protótipos das funções do grafo.c
 *  contém também a definição de uma estrutura do tipo node
 *  que será a estrutura que conterá os elementos do grafo
 * 
 * COMMENTS 
 *  
 *****************************************************************************/

#ifndef _GRAFO_H
#define _GRAFO_H

typedef struct node{ 
    int index;
    int cost;
    int parent;
    node *next;
} node;

node ***innit_array(int num_pal, int indexes[100], int probs[100]);
node*** create_list(node ***listv, char ***dictionary, int biggest_word, int indexes[100], int biggest_mut, int i, int* conta_nos);
node* insert_edge(node *listv, int indice, int parent, int custo);
node * getNextNodeLinkedList(node *node);
int letter_diff(char* palavra1, char* palavra2, int max_mut);
void free_graph(node*** listv, int indexes[100], int biggest_word);
void free_linked_list(node* Node);
int getCostLinkedList(node *node);

#endif