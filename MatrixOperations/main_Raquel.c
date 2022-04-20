// Trabalho 1 - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main(void)
{
	/* Inicialização da aplicação...*/

	Matrix* A = NULL;
	Matrix* B = NULL;
	Matrix* C = NULL;
	Matrix* D = NULL;
	
	matrix_create(&A);
	
	printf("1) Destruir uma matriz já destruída\n");
	matrix_destroy(A);
	A = NULL;
	matrix_destroy(A);
	
	printf("2) Inserir fora de ordem e inserir elemento zero no stdin\n");
	matrix_create(&B);
	
	printf("3) Setar um elemento que existe como zero e imprimí-lo\n");
	float elem;
	matrix_getelem(B, 1,2, &elem);
	printf("O elemento é: %f\n", elem);
	matrix_setelem(B, 1,2,0);
	matrix_getelem(B, 1,2, &elem);
	printf("O elemento é: %f\n", elem);
	
	printf("4) Tentar inserir na coluna ou linha 0\n");
	matrix_setelem(B, 1, 0, 5.0);
	matrix_setelem(B, 0, 2, 2.5);
	
	printf("5) Somar matrizes de tamanhos diferentes\n");
	matrix_create(&A);
	matrix_print(A);
	matrix_add(A, B, &C);
	
	printf("6) Inserir elemento numa matriz que não existe\n");
	matrix_setelem(D, 2,5, 8056);
	
	printf("7) Criar matriz com zero linhas ou colunas\n");
	matrix_create(&D);
	
	printf("8) Inserir elemento em coluna ou linha > do que as da matriz \n");
	matrix_setelem(A, 3,1, 4);
	matrix_setelem(A, 1,5,7);
	
	printf("9) Inserir elemento repetido no stdin\n");
	matrix_create(&D);
	matrix_print(D);
	
	matrix_destroy(A);
	A= NULL;
	matrix_destroy(B);
	A= NULL;
	matrix_destroy(C);
	A= NULL;
	matrix_destroy(D);
	A= NULL;
	printf("Obrigada pelo teste.\n");
}