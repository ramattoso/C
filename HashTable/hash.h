// Trabalho 2 - Raquel Mattoso 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define A 7

typedef struct index Index;

typedef struct occ Occ;

typedef struct hash Hash;

int index_createfrom( const char *key_file, const char *text_file, Index **idx);

int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences);

int index_put( Index *idx, const char *key);

int index_print( const Index *idx);

int index_destroy( Index* idx);
