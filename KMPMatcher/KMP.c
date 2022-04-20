// Trabalho de Algoritmos - Raquel Mattoso - KMP Search Algoritmo

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "KMP.h"

/****** Funções *****/
int* pi(const char *palavra, int n)
{
	int* tabela = (int*)malloc(n*sizeof(int));
	if (tabela == NULL)
	{
		printf("Memória Insuficiente\n.");
		exit(1);
	}
	int i = 0; 
	int j = 1;
	tabela[0] = 0;
	while(j<n)
	{
		if (palavra[j] == palavra[i])
		{
			tabela[j]=i+1;
			i = i+1;
			j = j+1;
		}
		else
		{
			tabela[j] = 0;
			j = j+1;
			if (i!=0)
			{
				i = tabela[i-2];				
			}
		}
	}
	return tabela;
}

void KMP(const char *palavra, FILE *texto, int n)
{
	int* tabela = pi(palavra, n);
	int linhas[10000]={0};
	int i = 0;
	char c = fgetc(texto);
	int k = 0;
	int nl = 1;
	while(c!=EOF) // Enquanto arquivo não termina
	{
		if(palavra[i] == tolower(c))
		{
			while(palavra[i] == tolower(c) && palavra[i]!='\0')
			{
				i = i+1;
				c = fgetc(texto);
			}
			if (palavra[i] == '\0')
			{
				linhas[k] = nl;
				k = k+1;
				i = 0;
			}
			else
			{
				i = tabela[i-1];
			}
			if(c =='\n')
			{
				nl = nl+1;
			}			
		}		
		else
		{
			i = 0;
			c = fgetc(texto);
			if(c =='\n')
			{
				nl = nl+1;
			}
		}
	}
	if(linhas[0] != 0)
	{	
		int aux = k;
		printf("O padrão procurado aparece na(s) linha(s) %d, ", linhas[0]);
		k = 1;
		while(k<aux)
		{
			printf("%d, \n", linhas[k]);
			k = k+1;			
		}
	}
	else	
	{
		printf("O padrão procurado não aparece.\n");
	}
}
void KMP_palavra(const char *palavra, FILE *texto, int n)
{
	int* tabela = pi(palavra, n);
	int linhas[10000] = {0};
	int i = 0;
	char c = fgetc(texto);
	int k = 0;
	int nl = 1;
	char auxc;
	while(c!=EOF) // Enquanto arquivo não termina
	{
		if(palavra[i] == tolower(c))
		{
			while(palavra[i] == tolower(c) && palavra[i]!='\0')
			{
				i = i+1;
				c = fgetc(texto);
			}
			if (palavra[i] == '\0' && !isalpha(c) && !isalpha(auxc))
			{
				linhas[k] = nl;
				k = k+1;
				i = 0;
			}
			else
			{
				i = tabela[i-1];
			}
			if(c =='\n')
			{
				nl = nl+1;
			}
		}			
		else
		{	
			i = 0;
			auxc = c;
			c = fgetc(texto);
			if (c == '\n')
			{
				nl = nl + 1;
			}
		}
	}
	if(linhas[0] != 0)
	{	
		int aux = k;
		printf("A palavra procurada aparece na(s) linha(s) %d, ", linhas[0]);
		k = 1;
		while(k<aux)
		{
			printf("%d, \n", linhas[k]);
			k = k+1;			
		}
	}
	else	
	{
		printf("A palavra procurada não aparece.\n");
	}
}