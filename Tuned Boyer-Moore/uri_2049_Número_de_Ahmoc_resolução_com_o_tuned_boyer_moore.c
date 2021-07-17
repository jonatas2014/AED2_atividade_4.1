# include <string.h>
# include <stdio.h>

// função de pré processamento
void preBmBc(char *x, int m, int bmBc[]) 
{
    int i;
    
    // preenchendo tabela alfabeto
    for (i = 0; i < 256; ++i)
        bmBc[i] = m;
    
    // configurando tabela com caracteres da palavra
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}
 

// função do Tuned Boyer-Moore
int TUNEDBM(char *x, char *y) 
{
    int j, k, shift, bmBc[256];
    
    // pegando tamanho da palavra e do texto coletados
    int m = strlen(x);
    int n = strlen(y);
  
    // pré processamento
    preBmBc(x, m, bmBc);
    shift = bmBc[x[m - 1]];
    bmBc[x[m - 1]] = 0;
    memset(y + n, x[m - 1], m);
 
    // Procurando palavra no texto
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
        
        // Encontrando ocorrencia da palavra no texto
        if (memcmp(x, y + j, m - 1) == 0 && j < n) return 1;
        
        
        j += shift; /* shift */
   }
   return 0;
}

int main()
{
    // definindo variaveis pra etrada
    char txt[300000]; // texto
    char pat[7]; // palavra
    int count = 1;
    
    // pegando entradas e processando
    while (1)
    {
        // pegando palavra a ser verificada no texto
        scanf("%s", pat);
      
        // caso de parada da entrada
        if(strcmp(pat,"0") == 0)
        {
        break;
        }
        scanf("%s", txt);
      
        // impressão do resultado
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
