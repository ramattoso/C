//Código para solução da equação diferencial dN/dt = rN
// Lista 2 -  Implementação - Raquel Mattoso

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "euler.h"

int main( int argc, char **argv ) {

	if( argc < 5 ) {
		fprintf( stderr, "Erro: numero insuficiente de parametros:\n" );
		fprintf( stderr, "Sintaxe: %s explicito erro implicito erro \n", argv[0] );
		return 1;
	}	
	float Nini = 4000000000;
	float r = 0.01;
	float T = 60;
	for(int i=1; i<7; i++)
	{
		euler_explicito(i, Nini, r, T, argv[1], argv[2]);
	}
	euler_explicito(12, Nini, r, T, argv[1], argv[2]);
	for(int i=1; i<7; i++)
	{
		euler_implicito(i, Nini, r, T, argv[3], argv[4]);
	}
	euler_implicito(12, Nini, r, T, argv[3], argv[4]);
}