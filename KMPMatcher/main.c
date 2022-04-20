#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "KMP.h"

int main( int argc, char **argv ) 
{
	
	if( argc < 2 ) {
		fprintf( stderr, "Erro: numero insuficiente de parametros:\n" );
		fprintf( stderr, "Sintaxe: %s txt_file_name\n", argv[0] );
		return 1;
	}
	FILE* texto = fopen(argv[1], "rt");
	if (texto == NULL) 
	{
		fprintf(stderr, "Erro na abertura do arquivo!\n");
		exit(1);
	}
	clock_t t;
	/* Qual vai ser o uso do programa?*/
	char *keyword = NULL;
	char *flag = NULL;
	printf("Quer procurar padrão ou palavra?\n" );
	scanf("%ms", &flag);
	char bandeira[10];
	strcpy(bandeira, flag);
	for(int i=0; i<10; i++)
	{
		bandeira[i] = tolower(bandeira[i]);
	}
	char aux1[] = "palavra";
	char aux2[] = "padrão";
	if (!strcmp(bandeira, aux1))
	{
		printf("Qual a palavra-chave a procurar?\n" );
		scanf("%ms",&keyword);
		int n = strlen(keyword);
		char palavra[n+1];
		strcpy(palavra,keyword);
		int i = 0;
		for(i; i<n; i++)
		{
			palavra[i] = tolower(palavra[i]);
		}
		palavra[i] = '\0';
		t = clock();
		KMP_palavra(palavra, texto, n);
		t = clock()-t;
		printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000)));
	}
	if (!strcmp(bandeira, aux2))
	{
		printf("Qual o padrão a procurar?\n" );
		scanf("%ms",&keyword);
		int n = sizeof(keyword);
		char palavra[n+1];
		strcpy(palavra,keyword);
		int i = 0;
		for(i; i<n; i++)
		{
			palavra[i] = tolower(palavra[i]);
		}
		palavra[i] = '\0';
		t = clock();
		KMP(palavra, texto, n);
		t = clock()-t;
		printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000)));
	}
	fclose(texto);
	return 0;
}