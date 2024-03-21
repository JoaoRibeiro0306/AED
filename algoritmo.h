/******************************************************************************
 * File Name: algoritmo.h
 *	      
 * Author: Grupo 112
 * 
 * NAME
 *      algoritmo.h - protótipos
 *  
 *	
 * DESCRIPTION 
 *  contém os protótipos das funções do algoritmo.c
 * 
 * COMMENTS 
 *  
 *****************************************************************************/
#ifndef _ALGORITMO_H
#define _ALGORITMO_H

#include "heap.h"

typedef struct node node;

int less_cost(node* cost1, node* cost2);
void dijkstra(node ***listv, int tamanho_heap, char ***dictionary, int(*less_cost)(node* cost1 , node* cost2), int word_size, FILE *fp, int indexes[100], int mid1, int mid2, int cost);

#endif