// Trabalho 1 - Raquel Mattoso
/* Registro das funções do Matrix */

typedef struct matrix Matrix;

// Lê e cria matriz numa lista encadeada (DONE)!
int matrix_create(Matrix** m);

// Destrói uma matriz (DONE)!
int matrix_destroy(Matrix* m);

// Imprime a matriz (DONE)!
int matrix_print( const Matrix* m);

// Soma duas matrizes (DONE)!
int matrix_add( const Matrix* m, const Matrix* n, Matrix** r);

// Multiplica duas matrizes (DONE)!
int matrix_multiply( const Matrix* m, const Matrix* n, Matrix** r);

//Transpõe uma matriz (DONE)!
int matrix_transpose(const Matrix* m, Matrix** r);

// Retorna o valor de um elemento específico (DONE)!
int matrix_getelem(const Matrix* m, int x, int y, float* elem);

//Atribui um valor (DONE)!
int matrix_setelem(Matrix* m, int x, int y, float elem);


	

