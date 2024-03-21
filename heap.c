/******************************************************************************
 *
 * File Name: heap.c
 * 
 * Author:    AED team e GR112
 *
 * NAME
 *     heap.c
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include "heap.h"
 *     #include "grafo.h"
 *
 * DESCRIPTION
 *		implementação adaptada do heap.c dado pelos professores, para
 * a melhor utilização do mesmo no nosso projeto
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "grafo.h"

/* to remove comments, just delete or comment the next line */
#define DEMO

/* A heap is represented by a structure: */
struct _heap {
  int (*less) (node*, node*);     /* Surprise! this field is a function pointer
                                 * to elements in the heap. */
  int n_elements;               /* # elements in heap */
  int size;                     /* max size of the heap. */
  node** heapdata;               /* An array of Items. */
};


/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int k)
{
  node* t;
  while ((k > 0) && (h->less) ((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;
    k = (k - 1) / 2;
  }

  return;
}


/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k)
{
  int j;
  node* t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) &&
        (h->less) (h->heapdata[j], h->heapdata[j + 1])) {
      /* second offspring is greater */
      j++;
    }
    if (!(h->less) (h->heapdata[k], h->heapdata[j])) {

    }
      /* Elements are in correct order. */

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;
  }

  return;
}


/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*less) (node*, node*))
{
  Heap *h;
  int i;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    exit(0);
  }

  h->n_elements = 0;
  h->less = less;
  h->size = size;
  h->heapdata = (node**) calloc(size , sizeof(node*));
  if (h->heapdata == NULL) {
    exit(0);
  }
  for(i=0;i<size;i++)
    h->heapdata[i] = (node*) calloc(1 , sizeof(node));

  return (h);
}

/******************************************************************************
 * FreeHeap()
 *
 * Arguments: Heap *h
 *            
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees the whole heap
 *
 *****************************************************************************/

void FreeHeap(Heap *h)
{
  int i = 0;
  for(i = 0; i < h->size; i++)
  {
    free(h->heapdata[i]);
  }
  free(h->heapdata);
  h->n_elements = 0;
  free(h);
}

/******************************************************************************
 * Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/

int Insert(Heap * h, int cost, int parent, int index)
{

  h->heapdata[h->n_elements]->cost = cost;
  h->heapdata[h->n_elements]->index = index;
  h->heapdata[h->n_elements]->parent = parent;

  h->n_elements++;
  FixUp(h, h->n_elements - 1);

  return 1;
}


/******************************************************************************
 * RemoveMax()
 *
 * Arguments: h - pointer to heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: exchange first and last element of heap, remove last element
 *              (max element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/

node* RemoveMax(Heap * h)
{
  node* t;
  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    h->n_elements--;
    FixDown(h, 0);
    return t;
  }

  return NULL;
}