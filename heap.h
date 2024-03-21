/******************************************************************************
 *
 * File Name: heap.h
 * 
 * Author:    AED team e GR112
 * 
 * NAME
 *     heap.h - prototypes
 *
 * SYNOPSIS
 *     #include "Item.h"
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include "Item.h"

typedef struct _heap Heap;

typedef struct node node;

Heap *NewHeap(int tamanho, int (*less) (node*, node*));

void FreeHeap(Heap * h);

int Insert(Heap * h, int cost, int parent, int index);

node* RemoveMax(Heap * h);

