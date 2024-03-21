/******************************************************************************
 *
 * File Name: wrdmttns.c
 * 
 * Author:    GR112
 * NAME
 *     wrdmttns - main 
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
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
#include "heap.h"

int main(int argc, char *argv[]){
    char ***dictionary = {0}, *dict_name = argv[1], *prob_name = argv[2];
    int indexes[100] , biggest_word_len=0, probs[100] /*copy_probs[100]*/;
    char *extensao_dict, *extensao_prob, ponto = '.', dict[6] = ".dict\0", pals[6] = ".pals\0";

    struct node*** array_adj;

    if((argc) != 3){
        exit(0);
    }


    extensao_dict = strrchr(dict_name, ponto);
    extensao_prob = strrchr(prob_name, ponto);
    if((strcmp(extensao_dict, dict) != 0) || (strcmp(extensao_prob, pals) != 0)) exit(0);

     for(int s=0; s<100; s++){
        indexes[s]=0;
        probs[s]=0;
       /* copy_probs[s]=0;*/
    }

    read_probs(probs, prob_name);

 /*    for(int s=0; s<100; s++){
        copy_probs[s]=probs[s];
    } */

    dictionary = import_dict(dict_name, dictionary, indexes, &biggest_word_len, probs);
    dictionary = shell_sort(dictionary, indexes, biggest_word_len);
    array_adj = innit_array(biggest_word_len, indexes, probs);
    escreve_resultados(prob_name, biggest_word_len, dictionary, indexes, array_adj, probs);

    freemem(dictionary, indexes, biggest_word_len, probs);  

    return 0;
}