//Código para solução da equação diferencial dN/dt = rN (1 - N/K)(N/A-1)
// Lista 5 -  Implementação - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int flag = 1;
	float h=1;
	float r=0.1;
	float k = 1000;
	float A = 150;
	float p=(h*r)/k;
	float b = (1/A)+(1/k);
	int nmax = 100;
	int imax = 100;
	float Nk =0;
	float tol = 0.001;
	float N = 1500;
	float Np;
	float f;
	float flinha;
	for (int n=1; n<nmax; n++)
	{
		Nk = N;
		int i = 0;
		do
		{
			i = i+1;
			Np = Nk;
			if(flag == 0)
				Nk = (N + p*pow(Np,2))/(1-(h*r)+(2*p*Np)); //Logistico simples
			
			if(flag == 1)
				Nk = (r*h*(-Np*Np*b+2*Np*Np*Np/(A*k))+N)/(1-r*h*(-1+2*Np*b-3*(Np*Np)/(A*k))); // Newton Sharp
			
			if(flag == 2)
				Nk = N/(1-r*h*(-1+Np*b-Np*Np/(A*k))); // Lista 5 - Implementação Picard;
			
			if(flag == 3)
			{	// Newton Flat
				f = Np + Np*h*r - Np*Np*h*r*b+(h*r*Np*Np*Np)/(A*k)-N;
				flinha = 1 + h*r - Np*h*r*b+(r*h*Np*Np)/(A*k);
				Nk = Np - f/flinha;
			}
		}
		while(fabs(Nk-Np) >0.01 && i<imax);//
		if (i == imax)
			printf("Limite de iterações excedido\n");
		N = Nk;
		if(flag == 0)
		{
			FILE* logarq;
			logarq = fopen("logarq","a");
			if (logarq == NULL)
			{
				fprintf(stderr, "Erro na abertura do arquivo!\n");
				exit(1);
			}
			fprintf(logarq, "%f %f\n", h*n, N);
			fclose(logarq);
		}
		if(flag == 1)
		{
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
		if(flag == 2)
		{
			FILE* picardarq;
			picardarq = fopen("picardarq","a");
			if (picardarq == NULL)
			{
				fprintf(stderr, "Erro na abertura do arquivo!\n");
				exit(1);
			}
			fprintf(picardarq, "%f %f\n", h*n, N);
			fclose(picardarq);
		}
		if(flag == 3)
		{
			FILE* newtondiretoarq;
			newtondiretoarq = fopen("newtondiretoarq","a");
			if (newtondiretoarq == NULL)
			{
				fprintf(stderr, "Erro na abertura do arquivo!\n");
				exit(1);
			}
			fprintf(newtondiretoarq, "%f %f\n", h*n, N);
			fclose(newtondiretoarq);
		}
		
	}
}