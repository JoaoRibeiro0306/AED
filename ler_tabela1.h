/******************************************************************************
 * File Name: ler_tabela1.h
 *	      
 * Author: Grupo 112
 * 
 * NAME
 *      ler_tabela1.h - protótipos
 * 
 * SYNOPSYS
 *  #include <stdlib.h>
 *  #include <stdio.h>
 *  
 *	
 * DESCRIPTION 
 *  
 * 
 * COMMENTS 
 *  
 *****************************************************************************/

#ifndef _LER_TABELA1_H
#define _LER_TABELA1_H

typedef struct node node;

FILE* open_file_read(char *file_name);
FILE* open_file_write(char *file_name);
void print_error(char *palavra1, char *palavra2, FILE *fp);
void read_probs(int probs[100], char *prob_name);
void escreve_resultados(char *prob_name, int biggest_word_len, char*** dictionary, int indexes[100], node*** array_adj, int probs[100]);
int procura_binaria(char*** dictionary, int l, int r, char* palavra, int word_leng, int indexes[100]);

#endif