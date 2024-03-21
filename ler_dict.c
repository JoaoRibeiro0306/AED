/******************************************************************************
 *
 * File Name: ler_dict.c
 * 
 * Author:  Gr112
 *
 * NAME
 *     ler_dict.c
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h
 *     #include "ler_tabela1.h"
 *     #include "ler_dict.h.h"
 *
 * DESCRIPTION
 *		ficheiro que abre o dicionário e ordena o mesmo por tamanho em listas
 * numa lista de listas de listas
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ler_tabela1.h"
#include "ler_dict.h"

//Macro equivalente à função da biblioteca string.h, strcmp (string copy)
#define _strcpy(dst, src)       \
do {                             \
    const char *_src = (src);    \
    char *_dst = (dst);          \
                                 \
    while ((*_dst++ = *_src++))  \
        ;                        \
} while (0)


/******************************************************************************************
 * import_dict ()
 *
 * Arguments: 
 *      - char*** dictionary(dicionario com as palavras ordenadas alfabéticamente)
 *      - char *dict_name (nome do ficheiro que contém o dicionário)
 *      - int biggest_word_len (Contém o tamanho da maior palavra do dicionario)
 *      - int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 * 
 * Returns: char*** dictionary
 *
 * Description: Lê o dicionário e escreve as palavras em diferentes dicionarios que 
 * contém apenas palavras do mesmo tamanho, alocando a memoria para os mesmos dinamicamente
 ******************************************************************************************/
char*** import_dict (char *dict_name, char ***dictionary, int indexes[100], int *biggest_word_len, int probs[100])
{
    char buffer1[100];
    int wordlen=0, i=0, j=0, biggest_word=0;
    FILE *fp = fopen(dict_name, "r");
    if(fp == NULL){
        fprintf ( stderr, "ERROR: cannot open file '%s'\n", dict_name);
        exit(0);
    }

    while(fscanf(fp, "%s", buffer1) != EOF){
        wordlen=strlen(buffer1);
        indexes[wordlen]++;
        if(wordlen>biggest_word){
            biggest_word=wordlen;
        }
    }

    fseek(fp, 0, SEEK_SET);
    char buffer2[biggest_word+1];

    dictionary = (char ***)calloc(biggest_word+1, sizeof(char**));
    if(dictionary == (char***)NULL){
        exit(0);
    }

    for(i=1; i<=biggest_word; i++){
        if(probs[i] == 0) continue;
        dictionary[i] = (char **)calloc(indexes[i]+1,sizeof(char*));
        if(dictionary[i] == (char**)NULL){
            exit(0);
        }
    }

    for(j=1; j<=biggest_word; j++){
        indexes[j]=0;
    }    
    
    while(fscanf(fp, "%s", buffer2) == 1 ){
        wordlen= strlen(buffer2);
        if(probs[wordlen] == 0)continue;
        dictionary[wordlen][indexes[wordlen]] = (char*)calloc(wordlen+1,sizeof(char));
        strcpy(dictionary[wordlen][indexes[wordlen]], buffer2);
        indexes[wordlen]++;   
    }
    
    fclose(fp);

    *biggest_word_len=biggest_word;

    return dictionary;
} 


/******************************************************************************************
 * shell_sort ()
 *
 * Arguments: 
 *      - char*** dictionary(dicionario com as palavras ordenadas alfabéticamente)
 *      - int biggest_word_len (Contém o tamanho da maior palavra do dicionario)
 *      - int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 * 
 * Returns: char*** dictioanary
 *
 * Description: Algoritmo que odena um vetor, de forma recursiva deixando-o n-ordenado
 * , até estar 1-ordenado retornando o array dictionary.
 ******************************************************************************************/
char*** shell_sort(char ***dictionary, int indexes[100], int biggest_word_len) // adaptado dos slides das aulas teoricas - Sort A
{
    int i=0, j=0, k=0, l=0;
    int seq[16] = {1391376, 463792, 198768, 86961, 33936,
13776, 4592, 1968, 861, 336, 112, 48,
21, 7, 3, 1};
    char temp1[biggest_word_len+1], temp2[biggest_word_len+1];

    for(l=1; l<=biggest_word_len; l++){
        if(indexes[l]==0){
            continue;
        }
        for(i=0; i<16; i++){
            int h = seq[i];
            for(j=h; j<indexes[l]; j++){
                strcpy(temp1, dictionary[l][j]);
                k=j;
                while(k-h>=0 && strcmp(dictionary[l][k],dictionary[l][k-h])<0){
                    _strcpy(temp2, dictionary[l][k]);
                    _strcpy(dictionary[l][k], dictionary[l][k-h]);
                    _strcpy(dictionary[l][k-h], temp2);
                    k-=h;
                }
                strcpy(dictionary[l][k], temp1);
            }
        }
    }
    return dictionary;
}


/******************************************************************************************
 * freemem ()
 *
 * Arguments: 
 *      - char*** dictionary(dicionario com as palavras ordenadas alfabéticamente)
 *      - int biggest_word_len (Contém o tamanho da maior palavra do dicionario)
 *      - int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 * 
 * Returns: void
 *
 * Description: Liberta toda a memória alocada para o dicionário, e futuramente para outras 
 * alocações de memória.
 ******************************************************************************************/
void freemem(char ***dictionary, int indexes[100], int biggest_word_len, int probs[100])
{
    int i=0, j=0;

    for(i=1; i<=biggest_word_len; i++){
        if(probs[i] == 0) continue;
        for(j=0; j<=indexes[i]; j++){
            free(dictionary[i][j]);
        }
        free(dictionary[i]);
    }
    free(dictionary);
}
