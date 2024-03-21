/******************************************************************************
 * File Name: algoritmo.h
 *	      
 * Author:    Grupo 112
 * 
 * NAME
 *      ler_dict.h - protótipos
 *  
 *	
 * DESCRIPTION 
 *  contém todos os protótipos de funções do ficheiro dict.c
 * 
 * COMMENTS 
 *  
 *****************************************************************************/

#ifndef _LER_DICT_H
#define _LER_DICT_H

char*** import_dict (char *dict_name, char ***dictionary, int indexes[100], int *biggest_word_len, int probs[100]);
char*** shell_sort(char ***dictionary, int indexes[100], int biggest_word_len);
void freemem(char ***dictionary, int indexes[100], int biggest_word_len, int probs[100]);



#endif