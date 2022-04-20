// Trabalho 1 - Raquel Mattoso 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


/***** Declaração da Struct *****/

struct matrix {
	struct matrix* right; //ponteiro para o elemento a direita
	struct matrix* below; // ponteiro para o elemento abaixo
	int l; // linha ocupada na matriz
	int c; //coluna ocupada na matriz
	float info; 
};

/***** Funções *****/

// Cria os nós cabeças para a matriz
static Matrix* cria_no(int linha, int coluna)
{
	Matrix* nogeral = (Matrix*) malloc (sizeof(Matrix)); /* criando o nó geral */
	if (nogeral == NULL)
	{
		printf("Memória insuficiente!\n");
		exit(1);
	}
	Matrix* tmp = nogeral; /* guardando localização da matriz*/
	nogeral->l=linha;
	nogeral->c=coluna;
	
	for(int i=linha; i>=1;i--)
	{
		Matrix* nolinha = (Matrix*) malloc(sizeof(Matrix)); /* aloca espaço para a criação dos nós linha */
		
		if (nolinha == NULL)
		{
			printf("Memória insuficiente!\n");
			exit(1);
		}
		
		nolinha->c=-1;
		nolinha->l=i;
		nolinha->below=tmp;
		nolinha->right=nolinha;
		tmp=nolinha;
	}
	nogeral->below=tmp;
	tmp = nogeral;
	
	for(int j=coluna; j>=1;j--)
	{
		Matrix* nocoluna = (Matrix*) malloc(sizeof(Matrix)); /* aloca espaço para a criação dos nós coluna */
		
		if (nocoluna == NULL)
		{
			printf("Memória insuficiente!\n");
			exit(1);
		}
		
		nocoluna->l=-1;
		nocoluna->c=j;
		nocoluna->right=tmp;
		nocoluna->below=nocoluna;
		tmp=nocoluna;
	}
	nogeral->right=tmp;
	return nogeral;
}

// Lê e cria matriz como lista encadeada
int matrix_create(Matrix** m)
{
	int linha, coluna, x, y;
	float info;
	
	scanf("%d %d\n", &linha, &coluna);
	if(linha <=0 || coluna <=0)
	{
		printf("Impossível criar matriz. Número de linhas ou colunas inválido.\n \n");
		return 1;
	}
	*m = cria_no(linha, coluna);
	scanf("%d ", &x);
	while (x !=0)
	{
		scanf("%d %f\n", &y, &info);
		matrix_setelem (*m, x, y, info);
		scanf("%d ", &x);
				
	}
	printf("Matriz criada com sucesso.\n\n");
	return 0;
}

// Destrói uma matriz
int matrix_destroy(Matrix* m)
{
	if(m == NULL)
	{
		printf("Matriz não existe\n\n");
		return 1;
	}
	else
	{
		Matrix* pd = m->below;
		Matrix* qd = NULL;
		Matrix* tmp = NULL;
		while (pd != m)
		{			
			qd = pd->right;
			while (qd != pd)
			{
				tmp = qd->right;
				free(qd);
				qd = tmp;
			}
			tmp = pd->below;
			free(pd);
			pd = tmp;
		}
		pd = m->right;
		while (pd !=m)
		{
			tmp = pd->right;
			free(pd);
			pd = tmp;
		}
		free(m);
	
	printf("Matriz excluída com sucesso\n\n");
	return 0;
	}
}

// Imprime a matriz
int matrix_print( const Matrix* m)
{
	if (m == NULL) /* caso a matriz não exista */
	{
		printf("Matriz não encontrada.\n\n");
		return 1;
	}
	Matrix* nolinha = m->below; /* entra na coluna de nós linhas */
	Matrix* p = NULL;
	
	printf("A matriz é:\n");
	while (nolinha != m)
	{
		for (p=nolinha->right; p!=nolinha; p=p->right)
		{
			printf("%d %d %f\n", p->l, p->c, p->info);
		}
		nolinha=nolinha->below;
		
	}
	printf("\n");
	return 0;

}

// Soma duas matrizes
int matrix_add( const Matrix* m, const Matrix* n, Matrix** r)
{
	if (m==NULL || n==NULL)
	{
		printf("Soma não pode ser feita. Alguma matriz não existe.\n\n");
		return 1;
	}
	if(m->l==n->l) /* mesmo número de linhas */
	{
		if (m->c==n->c) /* mesmo número de colunas */
		{
			 *r = cria_no(m->l, m->c); /* cria os nós cabeças da matriz C=M+N */
			
			Matrix* p_M = m->below; /* anda nas linhas de M */
			Matrix* q_M = NULL;  /* anda nas colunas de M */
			Matrix* p_N = n->below; /* anda nas linhas de N*/
			Matrix* q_N = NULL; /* anda nas colunas de N */
									
			while(p_M != m)
			{
				if(p_M->right == p_M) /* linha da matriz M é de zeros */
				{
					if(p_N->right != p_N) /* linha da matriz N não  é de zeros*/
					{
						for( q_N=p_N->right; q_N!=p_N; q_N=q_N->right)
						{
							int x = q_N->l;
							int y = q_N->c;
							float info = q_M->info;
							matrix_setelem(*r, x, y, info);
						}
					}
				}
				else /* linha da matriz M não é de zeros */
				{
					if (p_N->right == p_N) /* linha da matriz N é de zeros */
					{
						for( q_M=p_M->right; q_M!=p_M; q_M=q_M->right)
						{
							int x = q_M->l;
							int y = q_M->c;
							float info = q_M->info;
							matrix_setelem(*r, x, y, info);
						}
					}
					if (p_N->right != p_N) /*linha da matriz N não é só de zeros*/
					{
						q_M=p_M->right;
						q_N=p_N->right;
						while(q_M->c!=-1 || q_N->c!=-1)
						{
							if(q_M->c == q_N->c) /* colunas iguais  */
							{
								int x = q_M->l;
								int y = q_M->c;
								float info = q_M->info + q_N->info;
								matrix_setelem(*r, x, y, info);
								q_M=q_M->right;
								q_N=q_N->right;
							}
							else /* colunas diferentes */
							{
								if(q_N->c == -1) /* não tem mais elementos na linha de N*/
								{
									int x = q_M->l;
									int y = q_M->c;
									float info = q_M->info;
									matrix_setelem(*r, x, y, info);
									q_M=q_M->right;
								}
								else
								{
									if(q_M->c == -1) /* não tem mais elementos na linha de M*/
									{
										int x = q_N->l;
										int y = q_N->c;
										float info = q_N->info;
										matrix_setelem(*r, x, y, info);
										q_N=q_N->right;
									}
									else
									{
										if(q_M->c < q_N->c) /*coluna da matriz M está antes da de N*/
										{
											int x = q_M->l;
											int y = q_M->c;
											float info = q_M->info;
											matrix_setelem(*r, x, y, info);
											q_M=q_M->right;
										}
										if(q_N->c < q_M->c) /* coluna da matriz N está antes da de M*/
										{
											int x = q_N->l;
											int y = q_N->c;
											float info = q_N->info;
											matrix_setelem(*r, x, y, info);
											q_N=q_N->right;
										}
									}
								}
							}
						}
					}
				}
				p_M=p_M->below; /* desce na coluna de linhas de M */
				p_N=p_N->below; /* desce na coluna de linhas de N */
			}
		}
		else 
		{
			printf("Matrizes de tamanhos diferentes.\n\n");
			return 1;
		}
	}
	else 
	{
		printf("Matrizes de tamanhos diferentes.\n\n");
		return 1;
	}
	return 0;
}

// Multiplica duas matrizes
int matrix_multiply( const Matrix* m, const Matrix* n, Matrix** r)
{
	if(m == NULL || n == NULL)
	{
		printf("Não é possível fazer a multiplicação.\n\n");
		return 1;
	}
	if(m->c != n->l)
	{
		printf("Não é possível fazer a multiplicação.\n\n");
		return 1;
	}
	else 
	{
		int linha = m->l;
		int coluna = n->c;
		*r = cria_no(linha, coluna);
		
		Matrix* p_M = m->below;
		Matrix* q_M = NULL;
		Matrix* q_N = NULL;
		Matrix* p_N = NULL;
				
		while(p_M != m)
		{
			q_N=n->right; /*voltando para primeira coluna */
			while(q_N != n)
			{
				if(p_M->right != p_M) /* linha de M tem elementos não nulos */
				{
					if(q_N->below != q_N) /* coluna de N tem elementos não nulos*/
					{
						q_M=p_M->right;
						p_N=q_N->below;
						float multi = 0.0;
						float sum = 0.0;
					
						while(q_M != p_M)
						{
							if(q_M->c == p_N->l)
							{
								multi = q_M->info * p_N->info;
								q_M=q_M->right;
								p_N=p_N->below;
								sum = sum + multi; //armazenando a soma
							}
							else 
							{
								if(p_N->l == -1)
								{
									q_M=p_M;
								}
								else 
								{
									if(q_M->c < p_N->l) /* elemento em M depois do elemento em N*/
									{
										q_M=q_M->right;
									}
									if(p_N->l < q_M->c) /* elemento em N depois do elemento em N */
									{
										p_N=p_N->below;
									}
								}
							}
							
						}
						int x = p_M->l;
						int y = q_N->c;
						matrix_setelem(*r, x, y, sum);
					}
				}
				q_N=q_N->right;
			}
			p_M=p_M->below;
		}
	}
	return 0;
}

//Transpõe uma matriz
int matrix_transpose(const Matrix* m, Matrix** r)
{
	if (m == NULL)
	{
		printf("Matriz não existe.\n\n");
		return 1;
	}
	else
	{
		int rl = m->c;
		int rc = m->l;
		*r = cria_no( rl, rc);
		
		Matrix* p_M = m->below;
		Matrix* q_M = NULL;
					
		while (p_M != m) /* andando na coluna de nós linha da matriz M */
		{
			for (q_M=p_M->right; q_M != p_M; q_M = q_M ->right) /* andando na linha de M */
			{
				int x = q_M->c;
				int y = q_M->l;
				float info = q_M->info;
				matrix_setelem(*r, x, y, info);
			}
			p_M = p_M->below;
							
		}
		return 0;
	}		
}
// Retorna o valor de um elemento específico
int matrix_getelem(const Matrix* m, int x, int y, float* elem)
{
	if(m==NULL)
	{
		printf("Matriz não existe.\n\n");
		return 1;
	}
	
	Matrix* p = m->below;
	Matrix* q = NULL;
			
	if(x > m->l)
	{
		printf("Elemento não existe na matriz.\n\n");
		return 1;
	}
	if (y > m->c)
	{
		printf("Elemento não existe na matriz.\n\n");
		return 1;
	}
	while(p->l != x)
	{
		p=p->below;
	}
	q=p->right;
	while(q != p && q->c !=y)
	{
		q=q->right;
	}
	if(q->c == y)
	{
		*elem = q->info;
	}
	if(q == p)
	{
			*elem = 0;
	}
	return 0;
}
//Atribui um valor 
int matrix_setelem(Matrix* m, int x, int y, float elem)
{
	if(m == NULL)
	{
		printf("Matriz não existe.\n\n");
		return 1;
	}
	
	if(x > m->l || x<=0)
	{
		printf("Impossível inserir elemento na matriz. Número de linha inválido.\n\n");
		return 1;
	}
	if (y > m->c || y <=0)
	{
		printf("Impossível inserir elemento na matriz. Número de coluna inválido.\n\n");
		return 1;
	}
	
	Matrix* nolinha = m->below;
	Matrix* nocoluna = m->right;
	Matrix* antl = m;
	Matrix* antc = nocoluna;
	Matrix* p = NULL;
	Matrix* q = NULL;
	
	while(nolinha->l != x) /*procurando a linha do elemento */
	{
		antl = nolinha;
		nolinha = nolinha -> below;
	}
	p = nolinha->right;
	q = nolinha;
	while(p->c !=y && p!=nolinha )
	{
		q = p;
		p=p->right;
		
	}
	if(p == nolinha) /* Elemento não existe*/
	{
		if(elem !=0.0)
		{
			Matrix* celula = (Matrix*) malloc(sizeof(Matrix));
			if (celula == NULL)
			{
				printf("Memória insuficiente!\n");
				exit(1);
			}
			celula->l=x;
			celula->c=y;
			celula->info=elem;
	
			while(nocoluna!= m && nocoluna->c !=y)
			{
					antc=nocoluna;
					nocoluna=nocoluna->right;
			}	
			if (nocoluna->c == y) /*Achou a coluna */
			{
				if(nolinha->right !=nolinha) /*Não é o primeiro elemento a ser inserido na linha */
				{
					Matrix* p = nolinha->right;
					Matrix* q = nolinha;
				while (p !=nolinha && p->c < y) /*Coluna menor do que a inserida */
				{
					q=p;
					p=p->right;
				}
				if(p==nolinha)
				{
					q->right=celula;
					celula->right=nolinha;
				}
				else 
				{
					q->right=celula;
					celula->right=p;
				}				
				}
				else /*É o primeiro */
				{
					nolinha->right=celula;
					celula->right=nolinha;
				}
				if(nocoluna->below != nocoluna) /*Não é o primeiro elemento a ser inserido na coluna */
				{
					p = nocoluna->below;
					q = NULL;
					while (p !=nocoluna && p->l < x)
					{
						q=p;
						p=p->below;
					}
					if(p==nocoluna)
					{
						q->below=celula;
						celula->below=nocoluna;
					}
					else 
					{
						q->below=celula;
						celula->below=p;
					}
				}
				else /* É o primeiro */
				{
					nocoluna->below=celula;
					celula->below=nocoluna;
				}
			}
				
		}
		return 0;
			
	}
		
	//Elemento existe e é diferente de zero
	else
	{
		if( elem != 0.0)
		{
			p->info = elem;
			return 0;
		}
		if (elem == 0.0)
		{
			q->right = p->right;
			while(antc->c!=y)
			{
				antc=antc->right;
			}
			if(antc->right == p) /* Elemento a ser apagado está diretamente ligado ao nó coluna*/
			{
				antc->below = p->below;
			}
			else /*tem alguém antes de p*/
			{
				while(antc->below !=p)
				{
					antc=antc->below;
				}
				antc->below = p->below;
			}
			free(p);
			return 0;
		}
	}	
}