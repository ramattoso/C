// Trabalho 2 - Raquel Mattoso 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void KMP_palavra(const char *palavra, FILE *texto, int n);

void KMP(const char *palavra, FILE *texto, int n);

int* pi(const char *palavra, int n);