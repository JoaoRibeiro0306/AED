CC = gcc
flags=  -Wall -std=c99 -O3

wrdmttns:
	$(CC) $(flags) wrdmttns.c ler_tabela1.c ler_dict.c heap.c algoritmo.c grafo.c -o wrdmttns 

clean::
	rm -f *.o core a.out wrdmttns *~

