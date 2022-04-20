//Código para solução da equação diferencial dN/dt = rN (1 - N/K)(N/A-1)
// Lista 5 -  Implementação - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int flag = 0;
	float h=0.1;
	float r=0.1;
	float k = 1000;
	float A = 25;
	float b = (1/A)+(1/k);
	int nmax = 1000;
	int imax = 100;
	float Nk =0;
	float tol = 0.001;
	float N = 30;
	float Np;
	for (int n=1; n<nmax; n++)
	{
		Nk = N-1000;
		int i = 0;
		if(flag == 0)  // Caso normal
		{
			do
			{
				i = i+1;
				Np = Nk;
				Nk = (r*h*(-Np*Np*b+2*Np*Np*Np/(A*k))+N)/(1-r*h*(-1+2*Np*b-3*(Np*Np)/(A*k))); 
				/* Cálculo da ordem de convergência */
				FILE* conver = fopen("conver","a");
				if (conver == NULL)
				{
					fprintf(stderr, "Erro na abertura do arquivo!\n");
					exit(1);
				}
				fprintf(conver, "%d, %d %f\n", n, i, Nk);
				fclose(conver);
			}
			while(fabs(Nk-Np) > tol && i<imax);//
			if (i == imax)
				printf("Limite de iterações excedido\n");
			N = Nk;
		}
		if (flag==1) //Caso com perturbação
		{
			do
			{
				i = i+1;
				Np = Nk;
				Nk = (r*h*(-Np*Np*b+2*Np*Np*Np/(A*k))+N)/(1-r*h*(-1+2*Np*b-3*(Np*Np)/(A*k))); 
			}
			while(fabs(Nk-Np) >0.01 && i<imax);//
			if (i == imax)
				printf("Limite de iterações excedido\n");
			N = Nk;
			if(n == 49)
				N = 500;
		}
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