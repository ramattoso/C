// Trabalho 1 - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main(void)
{
	/* Inicialização da aplicação...*/
	
	Matrix* A=NULL;
	Matrix* B=NULL;
	Matrix* C=NULL;
	
	
	if (!matrix_create(&A))
	{
		matrix_print(A);
	}
	else
	{
		fprintf( stderr, "Erro na alocação de A como listas encadeadas. \n");
		return 1;
	}
	
	if (!matrix_create(&B))
	{
		matrix_print(B);
	}
	else
	{
		fprintf( stderr, "Erro na alocação de B como listas encadeadas. \n");
		return 1;
	}
	
	
	if (!matrix_add(A, B, &C))
	{
		matrix_print(C);
	}
	else
	{
		fprintf( stderr, "Erro na soma C=A+B. \n");
	}
	matrix_destroy(C);
	C=NULL;
	
	if ( !matrix_multiply( A, B, &C ) )
	{
		matrix_print( C );
	}
	else
	{
		fprintf( stderr, "Erro na multiplicacao C=A*B.\n" );
	}
	matrix_destroy(C);
	C = NULL;
	
	if ( !matrix_transpose( A, &C ) )
	{
		matrix_print( C );
	}
	else
	{
		fprintf( stderr, "Erro na transposicao C=A^T.\n" );
	}
	matrix_destroy( C );
	C = NULL;
	matrix_destroy( A );
	A = NULL;
	matrix_destroy( B );
	B = NULL;
	return 0;
}
		