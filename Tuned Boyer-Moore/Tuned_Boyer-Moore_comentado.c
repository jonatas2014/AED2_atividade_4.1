# include <string.h>
# include <stdio.h>

/* função de pré processamento */
void preBmBc(char *x, int m, int bmBc[]) 
{
    int i;
    
    /* preenchendo tabela alfabeto */
    for (i = 0; i < 256; ++i)
        bmBc[i] = m;
    
    /* configurando tabela com caracteres da palavra */
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}
 

/* função do Tuned Boyer-Moore */
void TUNEDBM(char *x, int m, char *y, int n) 
{
    int j, k, shift, bmBc[256];
  
    /* pré processamento */
    preBmBc(x, m, bmBc);
    shift = bmBc[x[m - 1]];
    bmBc[x[m - 1]] = 0;
    memset(y + n, x[m - 1], m);
 
    /* Procurando palavra no texto */
    j = 0;
    while (j < n) 
    {
        k = bmBc[y[j + m -1]];
        while (k !=  0) 
        {
            /* interações iniciais */
            j += k; k = bmBc[y[j + m -1]];
            j += k; k = bmBc[y[j + m -1]];
            j += k; k = bmBc[y[j + m -1]];
        }
        
        /* Encontrando ocorrencia da palavra no texto */
        if (memcmp(x, y + j, m - 1) == 0 && j < n);
            printf("Ocorrencia na pos: %d\n", j);
        
	/* shift */
        j += shift; 
   }
}

