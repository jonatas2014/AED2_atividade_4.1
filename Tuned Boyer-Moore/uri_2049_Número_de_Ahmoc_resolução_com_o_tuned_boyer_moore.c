# include <string.h>
# include <stdio.h>

void preBmBc(char *x, int m, int bmBc[]) 
{
    int i;
    
    for (i = 0; i < 256; ++i)
        bmBc[i] = m;
    
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}
 

/* função do Tuned Boyer-Moore */
int TUNEDBM(char *x, char *y) 
{
    int j, k, shift, bmBc[256];
    
    /* Pegando tamanho da palavra e do texto coletados */
    int m = strlen(x);
    int n = strlen(y);
  
    preBmBc(x, m, bmBc);
    shift = bmBc[x[m - 1]];
    bmBc[x[m - 1]] = 0;
    memset(y + n, x[m - 1], m);
 
    j = 0;
    while (j < n) 
    {
        k = bmBc[y[j + m -1]];
        while (k !=  0) 
        {
            j += k; k = bmBc[y[j + m -1]];
            j += k; k = bmBc[y[j + m -1]];
            j += k; k = bmBc[y[j + m -1]];
        }
        
        if (memcmp(x, y + j, m - 1) == 0 && j < n) return 1;
        
        j += shift; 
   }
   return 0;
}

int main()
{
    /* Definindo variaveis pra etrada */
    char txt[300000]; // texto
    char pat[7]; // palavra
    int count = 1;
    
    /* Pegando entradas e processando */
    while (1)
    {
        /* Pegando palavra a ser verificada no texto */
        scanf("%s", pat);
      
        /* Caso de parada da entrada */
        if(strcmp(pat,"0") == 0)
        {
            break;
        }
        scanf("%s", txt);
      
        /* Impressão do resultado */
        printf("Instancia %d\n", count);
        if (TUNEDBM(pat, txt))
        {
            printf("verdadeira\n");
        }
        else
        {
            printf("falsa\n");
        }
        count++;
    }
    return 0;
}

