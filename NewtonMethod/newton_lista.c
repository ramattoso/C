//Código para solução da equação diferencial dN/dt = rN (1 - N/K)(N/A-1)
// Lista 5 -  Implementação - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float h=0.1;
	float r=0.01;
	float k = 1000;
	float A = 25;
	float b = (1/A)+(1/k);
	int nmax = 100;
	int imax = 100;
	float Nk =0;
	float tol = 0.001;
	float N = 30;
	float Np;
	for (int n=1; n<nmax; n++)
	{
		Nk = N;
		int i = 0;
		do
		{
			i = i+1;
			Np = Nk;
			Nk = (r*h*(-Np*Np*b+2*Np*Np*Np/(A*k))+N)/(1-r*h*(-1+2*Np*b-3*(Np*Np)/(A*k))); // Lista 5 - Implementação - Newton
			
		}
		while(fabs(Nk-Np) >0.001 && i<imax);//
		if (i == imax)
			printf("Limite de iterações excedido\n");
		N = Nk;
		FILE* newtonarq;
		newtonarq = fopen("newtonarq","a");
		if (newtonarq == NULL)
		{
			fprintf(stderr, "Erro na abertura do arquivo!\n");
			exit(1);
		}
		fprintf(newtonarq, "%f %f\n", h*n, N);
		fclose(newtonarq);
				
	}
}