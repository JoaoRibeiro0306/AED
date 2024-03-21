/******************************************************************************
 * File Name
 *   ler_tabela.c
 * 
 * Author: Grupo 112
 * 
 * SYNOPSYS
 *  #include <stdlib.h>
 *  #include <stdio.h>
 *  #include <string.h>
 * 
 *  #include "ler_tabela1.h"
 *  #include "ler_dict.h"
 *  #include "grafo.h"
 *  #include "algoritmo.h"
 *  #include "heap.h"
 *
 * DESCRIPTION
 *   programa em que lê a tabela criada pelo dicionário, cria a lista de adjacência
 * formando o grafo com os custos e utilizando o algoritmo de dijkstra para 
 * procurar o caminho pretendido
 *
 * COMMENTS
 *   
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ler_tabela1.h"
#include "ler_dict.h"
#include "grafo.h"
#include "algoritmo.h"
#include "heap.h"

/******************************************************************************
 * open_file_read ()
 *
 * Arguments: 
 *    Nenhum
 * 
 * Returns: um ponteiro para o fle aberto
 * Side-Effects: none
 *
 * Description: Abre o ficheiro a ler
 *****************************************************************************/

FILE* open_file_read(char *file_name)
{
  FILE *fp = fopen(file_name, "r");
  if(fp == NULL){
    exit(0);
  }
  return fp;
}

/******************************************************************************
 * open_file_write()
 *
 * Arguments: 
 *    Nenhum
 * 
 * Returns: um ponteiro para o file a escrever
 * Side-Effects: none
 *
 * Description: Abre o ficheiro a escrever
 *****************************************************************************/

FILE* open_file_write(char *file_name)
{
  FILE *fp = fopen(file_name, "w");
  if(fp == NULL){
    exit(0);
  }
  return fp;
}

/******************************************************************************
 * print_error ()
 *
 * Arguments: 
 *      -char *palavra1: primeira palavra do problema
 *      -char *palavra2: segunda palavra do problema
 *      -FILE *fp: ponteiro para o ficheiro de escrita
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Escreve o problema no ficheiro quando este não é valido
 *****************************************************************************/
void print_error(char *palavra1, char *palavra2, FILE *fp)
{
  fprintf(fp, "%s -1\n", palavra1);
  fprintf(fp, "%s\n\n", palavra2);
  return;
}

/******************************************************************************
 * Procura_binaria ()
 *
 * Arguments: 
 *      - char*** dictionary(dicionario com as palavras ordenadas alfabéticamente)
 *      - int l (limite inferior do array)
 *      - int r (limite superior do array)
 *      - char* palavra (Palavra que queremos procurar)
 *      - int word_leng (tamanho da palavra que queremos procurar)
 * 
 * Returns: int mid (meio do array)
 * Side-Effects: none
 *
 * Description: função recursiva para procurar uma palavra em especifico
 *****************************************************************************/
int  procura_binaria(char*** dictionary, int l, int r, char* palavra, int word_leng, int indexes[100]){

    int mid = 0;
    int str_compare_value = 0;

    while(r>=l){
        mid = l + (r-l)/2;

        if(indexes[word_leng] == mid){
          return -1;
        }

        str_compare_value = strcmp(dictionary[word_leng][mid], palavra);
        
        if(str_compare_value == 0)
            return mid;

        else if(str_compare_value > 0)
            r = mid-1; 
        else 
          l = mid+1;
    }
    return -1; //quando o que procuramos não está lá

    
}


/*******************************************************************************************************
 * Read_Probs ()
 *
 * Arguments: 
 *      - int *probs (vetor que contem o numero de problemas referentes a um tamanho especifico)
 *      - int *biggest_muts (vetor que contém a maior mutação que se pode fazer num determinado tamanho)
 * 
 * Returns: int mid (meio do array)
 * Side-Effects: none
 *
 * Description: função recursiva para procurar uma palavra em especifico
 ******************************************************************************************************/
void read_probs(int probs[100], char *prob_name)
{
  char palavra1[100], palavra2[100];
  int wordlen=0, muts=0;
  FILE *fp = NULL;
  fp = open_file_read(prob_name);

  while(fscanf(fp, "%s  %s  %d", palavra1, palavra2, &muts) == 3){
    wordlen = strlen(palavra1);
    if(strlen(palavra2) != wordlen) continue;
    probs[wordlen]++;
  }
  fclose(fp);

  return;
}


/******************************************************************************************
 * escreve_resultados ()
 *
 * Arguments: 
 *      - char*** dictionary(dicionario com as palavras ordenadas alfabéticamente)
 *      - char *prob_name (nome do ficheiro de problemas lido da linha de comandos)
 *      - int mode (Varialvel que escolhe a ação que iremos realizar)
 *      - int biggest_word_leng (Contém o tamanho da maior palavra do dicionario)
 *      - int indexes[100] (Contém o tamanho, em numero de palavras, de cada dicionário)
 *      - node*** array_adj (array que irá conter o grafo utilizado para procurar no dijkstra)
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Lê o ficheiro de entrada .pals e chama a função de procura quando requerido
 * e executa a função do algoritmo de dijkstra
 ******************************************************************************************/
void escreve_resultados(char *prob_name, int biggest_word_len, char*** dictionary, int indexes[100], node*** array_adj, int probs[100])
{

  FILE *file_write = NULL, *file_read = NULL;
  char *ficheiro_escreve, palavra1[100], palavra2[100];
  int graph_done[100] = {0};
  int l= 0, cost=0, word_leng = 0, r = 0, mid1 = 0, mid2 = 0, prob_name_len=0, word_leng2 = 0;
  int conta_nos = 0, i=0;

  /*criação da lista de vetores mut ajuda ao controlo de grafos de adjacencias, a partir do nº de mutações*/
  int** mut = (int**)calloc(biggest_word_len, sizeof(int*)); 
  for (i = 0; i < biggest_word_len; i++)
    mut[i] = (int*)calloc(biggest_word_len, sizeof(int));

  file_read = open_file_read(prob_name);

  ficheiro_escreve =  (char*)calloc(sizeof(char), (strlen(prob_name)-5 + strlen(".paths") + 1));
  
  prob_name_len = strlen(prob_name)-5;
  memcpy(ficheiro_escreve, prob_name, prob_name_len);
  ficheiro_escreve[prob_name_len] = '\0';
  strcat(ficheiro_escreve, ".paths");

  file_write = open_file_write(ficheiro_escreve);

  while(fscanf(file_read, "%s  %s  %d", palavra1, palavra2, &cost) == 3){ 
    word_leng = strlen(palavra1);
    word_leng2 = strlen(palavra2);
    r = indexes[word_leng];

    if(word_leng != word_leng2){
      print_error(palavra1, palavra2, file_write);
      probs[word_leng]--;
      continue;
    }

    if(cost<0){
      fprintf(file_write, "%s %d\n", palavra1, cost);
      fprintf(file_write, "%s\n\n", palavra2);
      probs[word_leng]--;
      continue;
    }

    if(word_leng == strlen(palavra2) && indexes[word_leng] != 0){
      mid1 = procura_binaria(dictionary, l, r, palavra1, word_leng, indexes);
      mid2 = procura_binaria(dictionary, l, r, palavra2, word_leng, indexes);
      if(mid1 == -1 || mid2 == -1){
        print_error(palavra1, palavra2, file_write);
        probs[word_leng]--;
        continue;
      }
      
      if((cost==0) && (mid1 != mid2)){
        fprintf(file_write, "%s -1\n", palavra1);
        fprintf(file_write, "%s\n\n", palavra2);
        probs[word_leng]--;
        continue;
      }

      if(letter_diff(palavra1, palavra2, 1) == 1){
        fprintf(file_write, "%s 1\n", palavra1);
        fprintf(file_write, "%s\n\n", palavra2);
        probs[word_leng]--;
        continue;
      }
      
      if(mid1 == mid2){
        fprintf(file_write, "%s 0\n", palavra1);
        fprintf(file_write, "%s\n\n", palavra2);
        probs[word_leng]--;
        continue;
      }
 
      if(graph_done[word_leng] == 0 || mut[word_leng][cost] == 0){
       array_adj = create_list(array_adj, dictionary, biggest_word_len, indexes, cost, word_leng, &conta_nos);
      }
      graph_done[word_leng] = 1;
      mut[word_leng][cost] = 1;
      dijkstra(array_adj, conta_nos, dictionary, less_cost, word_leng, file_write, indexes, mid1, mid2, cost);
      probs[word_leng]--;
    }
    else{
     print_error(palavra1, palavra2, file_write);
     probs[word_leng]--;
    }
    if(probs[word_leng] == 0){
      free_graph(array_adj, indexes, word_leng);
    }
  }

  fclose(file_write);
  fclose(file_read);
  free(ficheiro_escreve);
  for (i = 0; i < biggest_word_len; i++)
    free(mut[i]);
  free(mut);
  free(array_adj);

  return;
}

/* void encontra_problemas(char *fp, char *file_write, int ){
  char *file_read;
  char *palavra1, *palavra2;
  int cost=0, word_leng=0, word_leng2=0;

  file_read = open_file_read(fp);

  while(fscanf(file_read, "%s  %s  %d", palavra1, palavra2, cost) == 3){ 
    word_leng = strlen(palavra1);
    word_leng2 = strlen(palavra2);

  if(word_leng != word_leng2){
      print_error(palavra1, palavra2, file_write);
      continue;
    }

} */
