// Trabalho 2 - Raquel Mattoso 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

/***** Declaração da Struct *****/

struct index
{
	char arquivo[100]; //Guarda nome do arquivo textos
	char indice[100]; //Guarda nome do arquivo de palavras chaves
	int total_palavras; 
	struct hash* tabela;
};
struct hash
{
	int chave; //chave numérica 
	char palavra[17];
	struct hash* prox_chave; // ponteiro para key igual com palavra diferente
	struct occ* occurrences; //ponteiro para lista de linhas 
	int num_occ; // guarda número de linhas em que a palavra aparece
};
struct occ
{
	int linha;
	struct occ* prox;
};

/****** Funções *****/
static int chave_hash(char *palavra)
{
	int i=0;
	int soma = 0;
	while(palavra[i] !='\0')
	{
		int letra = palavra[i];
		soma = letra + soma;
		i++;
	}
	int chave = soma%A;
	return chave;
}
static Hash* cria_hash()
{
	Hash* tabela = (Hash*)malloc(A*sizeof(Hash));
	if (tabela == NULL)
	{
		printf("Memória Insuficiente\n.");
		exit(1);
	}
	int i = 0;
	for(i; i < A; i++)
	{
		tabela[i].chave = -1;
		tabela[i].palavra[0] = '\0';
		tabela[i].prox_chave = NULL;
		tabela[i].occurrences = NULL;
		tabela[i].num_occ = 0;
	}
	return tabela;
}
int index_createfrom(const char *key_file, const char *text_file, Index **idx)
{
	FILE* indice;
	indice = fopen(key_file,"rt");	
	if (indice == NULL) 
	{
		fprintf(stderr, "Erro na abertura do arquivo!\n");
		exit(1);
	}
	*idx=(Index*)malloc(sizeof(Index)); // aloca o struct index 
	Index* idx2 = (*idx);
	if(*idx == NULL)
	{
		printf("Memória Insuficiente\n.");
		exit(1);
	}
	strcpy((*idx)->arquivo, text_file);
	strcpy((*idx)->indice, key_file);
	(*idx)->total_palavras = 0;
	(*idx)->tabela = cria_hash();
	/**** Lendo indice ****/
	//Criando chaves númericas hash
	char c = fgetc(indice);
	while(c!=EOF) // Enquanto arquivo não termina
	{
		char palavra[17];
		int i = 0;
		while(c!='\n' && c!=EOF) //Enquanto não acaba a palavra
		{	
			palavra[i] = tolower(c); //pega as letras e, caso for maiúsculo, vira minúsculo.
			i++;
			c = fgetc(indice);
		}
		palavra[i]='\0';
		index_put(idx2, palavra);
		c = fgetc(indice);
	}
	fclose(indice);
	return 0;
}
static int procura(char* key, FILE* texto, Hash* tabela, Occ** occurrences, int* num_occ)
{
	char procura[17];
	char c = fgetc(texto);
	int j=0;
	int nl=1;
	Hash* auxtabela = tabela;
	while(c!=EOF) // Enquanto arquivo não termina
	{
		while(c!='\n' && c!=EOF)
		{
			int i=0;
			if(isalpha(c))
			{
				while(isalpha(c))
				{
					procura[i]=tolower(c);
					i++;
					c=fgetc(texto);
				}
				procura[i]='\0';
				if(!strcmp(procura,key)) 
				{
					if(tabela->occurrences == NULL)
					{
						Occ* elem = (Occ*)malloc(sizeof(Occ));
						if (elem == NULL)
						{	 
							printf("Memória Insuficiente.\n");
							exit(1);
						}
						elem->linha = nl;
						elem->prox = NULL;
						*occurrences = elem;
					}
					else
					{
						Occ* elem = (Occ*)malloc(sizeof(Occ));
						if (elem == NULL)
						{	 
							printf("Memória Insuficiente.\n");
							exit(1);
						}
						Occ* aux = tabela->occurrences;
						while(aux->prox!= NULL)
						{
							aux=aux->prox;
						}
						aux->prox = elem;
						elem->prox = NULL;
						elem->linha = nl;
						*occurrences = tabela->occurrences;
					}
					while(c!='\n' && c!= EOF)
					{
						c=fgetc(texto);
					}
				}
			}
			else
			{
				c=fgetc(texto);
			}
		}
		nl++;
		c=fgetc(texto);
	}
	int i=0;
	Occ* aux = tabela->occurrences;
	while(aux != NULL)
	{
		aux=aux->prox;
		i++;
	}
	*num_occ = i;
	return 0;
}
int index_get(const Index *idx, const char *key, int **occurrences, int *num_occurrences)
{
	char palavra[17] = "";
	strcpy(palavra,key);
	int i=0;
	for(i; i<16; i++)
	{
		palavra[i] = tolower(palavra[i]);
	}
	palavra[i] = '\0';
	int chave = chave_hash(palavra);
	Hash* hash = &idx->tabela[chave];
	while(hash!= NULL && strcmp(hash->palavra,palavra) !=0)
	{
		hash=hash->prox_chave;
	}
	if(hash!=NULL && !strcmp(hash->palavra,palavra))
	{
		if(hash->num_occ !=0)
		{
			*num_occurrences = hash->num_occ;
			Occ* aux = hash->occurrences;
			*occurrences = (int*)malloc((hash->num_occ)*sizeof(int)); 
			for(int i = 0; i<hash->num_occ; i++)
			{
				(*occurrences)[i] = aux->linha;
				aux = aux->prox;
			} return 0;
		}
		else
		{
			*num_occurrences =0;
			*occurrences = NULL;
			return 0;
		}
	}
	else
	{
		return 1;
	}
}
int index_put( Index *idx, const char *key)
{
	char palavra[17];
	int i=0;
	char c = key[i];
	while(c!='\n' && c!='\0') //Enquanto não acaba a palavra
	{	
		palavra[i] = tolower(c); //pega as letras e, caso for maiúsculo, vira minúsculo.
		i++;
		c = key[i];
	}
	palavra[i]='\0';
	int chave = chave_hash(palavra);
	Hash* hash = &idx->tabela[chave];
	char* texto = idx->arquivo;
	FILE* f_texto = fopen(texto, "rt");
	if (f_texto == NULL) 
	{
		fprintf(stderr, "Erro na abertura do arquivo!\n");
		exit(1);
	}
	if(hash->palavra[0] =='\0')
	{	
		hash->chave = chave;
		strcpy(hash->palavra, palavra);
		hash->prox_chave=NULL;
		procura(palavra, f_texto, hash, &hash->occurrences, &hash->num_occ);
		idx->total_palavras = idx->total_palavras +1;
		     
	}
	else //colisão
	{
		while(hash->prox_chave != NULL && strcmp(hash->palavra, key)!=0)
		{
			hash = hash->prox_chave;
		}			
		if(strcmp(hash->palavra, key) == 0) //palavra já existe no índice
		{
			return 0;
		}
		else // mesma chave com palavras distintas
		{		
			Hash* elem = (Hash*)malloc(sizeof(Hash));
			if (elem == NULL)
			{ 
				printf("Memória Insuficiente.\n");
				exit(1);
			}
			Hash* segura = hash->prox_chave;
			hash->prox_chave = elem;
			elem->chave = chave;
			strcpy(elem->palavra, palavra);
			elem->prox_chave=segura;
			elem->occurrences = NULL; 
			elem->num_occ = 0; 
			procura(palavra, f_texto, elem, &elem->occurrences, &elem->num_occ);
			idx->total_palavras = idx->total_palavras +1;
		}
	}
	fclose(f_texto);
	return 0;
}
int index_print(const Index *idx)
{
	Hash* aux;
	//Criando matriz de palavras
	char auxp[17];
	char** mat = (char**) malloc((idx->total_palavras)*sizeof(char*)); 
	int linha = 0;
	for(int i=0; i<A; i++)
	{
		aux = &idx->tabela[i];
		while(aux != NULL)
		{
			if(aux->palavra[0] !='\0')
			{
				strcpy(auxp, aux->palavra);
				mat[linha] = (char*) malloc(17*sizeof(char));
				for (int j=0; j<17; j++)
				{
					mat[linha][j]=auxp[j];
				}
				linha++;
			}
			aux=aux->prox_chave;
		}	
	}
	// ordenando alfabeticamente
	int i=0;
	int troca;
	do 
	{ 
		troca = 0;
		for( i=0; i<(idx->total_palavras)-1; i++)
		{
			if(strcmp(mat[i],mat[i+1]) > 0)
			{
				strcpy(auxp, mat[i]);
				strcpy(mat[i], mat[i+1]);
				strcpy(mat[i+1], auxp);
				troca++;
			}
		}
	} while (troca!=0);
	//imprimindo 
	int* occurrences;
	int num_occurrences;
	for (int i=0; i<(idx->total_palavras); i++)
	{
		printf("%s: ", mat[i]);
		index_get(idx, mat[i], &occurrences, &num_occurrences);
		int j=0;
		if(num_occurrences !=0)
		{
			for(j; j<num_occurrences-1; j++)
			{
				printf("%d, ", occurrences[j]);
			}
			printf("%d\n", occurrences[j]);
		}
		else
		{
			printf("\n");
		}
		free(occurrences);
	}
	// apagando matriz de char
	for(linha=0; linha<(idx->total_palavras); linha++)
	{
		free(mat[linha]);
	}
	free(mat);
	return 0;
}
int index_destroy( Index* idx)
{
	Occ* deletaocc = NULL;
	Occ* seguraocc = NULL;
	Hash* deleta = NULL;
	Hash* segura = NULL;
	
	for(int i=0; i<A; i++)
	{
		deleta = &idx->tabela[i];
		while(deleta!=NULL)
		{
			segura = deleta->prox_chave;
			deletaocc = deleta->occurrences;
			while(deletaocc!=NULL)
			{
				seguraocc = deletaocc->prox;
				free(deletaocc);
				deletaocc = seguraocc;				
			}
			free(deleta);
			deleta = segura;
		}
	}
	free(idx->tabela);
	free(idx);
}
