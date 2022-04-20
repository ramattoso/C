//Código para solução da equação diferencial dN/dt = rN
// Lista 2 -  Implementação - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "euler.h"

int euler_explicito (float h, float Nini, float r, float T, char* arquivo, char* arquivoerro)
{
	float N = Nini;
	float tk = 0;
	float Nk;
	float ek;
	FILE* explicito;
	explicito = fopen(arquivo,"w+");	
	if (explicito == NULL) 
	{
		fprintf(stderr, "Erro na abertura do arquivo!\n");
		exit(1);
	}
	fprintf(explicito, " %f %f\n", tk, N);
	while(tk<=T)
	{
		Nk = (1+h*r)*N;
		tk = tk + h;
		N = Nk;
		fprintf(explicito, " %f %f\n", tk, N);
	}
	ek = fabs(N - Nini*exp(r*(tk-h)));
	FILE* explicitoer = fopen(arquivoerro, "a");
	fprintf(explicitoer, "%f %f\n", log10(h), log10(ek));
	fclose(explicito);
	fclose(explicitoer);
	return 0;
}

int euler_implicito(float h, float Nini, float r, float T, char* arquivo, char* arquivoerro) 
{
	float N = Nini;
	float tk = 0;
	float Nk;
	float ek;
	FILE* implicito;
	implicito = fopen(arquivo,"w+");	
	if (implicito == NULL) 
	{
		fprintf(stderr, "Erro na abertura do arquivo!\n");
		exit(1);
	}
	fprintf(implicito, " %f %f\n", tk, N);
	while(tk<=T)
	{
		Nk = N/(1-h*r);
		tk = tk + h;
		N = Nk;
		fprintf(implicito, " %f %f\n", tk, N);
	}
	ek = fabs(N - Nini*exp(r*(tk-h)));
	FILE* implicitoer = fopen(arquivoerro, "a");
	fprintf(implicitoer, "%f %f\n", log10(h), log10(ek));
	fclose(implicito);
	fclose(implicitoer);
	return 0;
	
}

