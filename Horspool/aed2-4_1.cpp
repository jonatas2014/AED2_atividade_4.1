#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <iostream>

/* Returns a pointer to the first occurrence of "needle"
 * within "haystack", or NULL if not found. Works like
 * memmem().
 */

using namespace std;
/* Returns a pointer to the first occurrence of "needle"
 * within "haystack", or NULL if not found. Works like
 * memmem().
 */

 /* Note: In this example needle is a Cstring. The ending
  * 0x00 will be cut off, so you could call this example with
  * boyermoore_horspool_memmem(haystack, hlen, "abc", sizeof("abc"))
  */
const unsigned char* boyermoore_horspool_memmem(const unsigned char* haystack,
    size_t hlen,
    const unsigned char* needle,
    size_t nlen)
{
    size_t scan = 0;
    size_t bad_char_skip[UCHAR_MAX + 1]; // = 256

    /* Check para garantir que existe uma string, uma subtring e que a substring � maior que a string */
    if (nlen <= 0 || !haystack || !needle)
        return NULL;

    /* ---- Preprocess ---- */
    /* Inicializa a bad character table */
    /* Quando um caracter que n�o esta na needle �
     * encontrada, podemos pular todo o tamanho da
     * needle com seguran�a.
     */
    for (scan = 0; scan <= UCHAR_MAX; scan++) bad_char_skip[scan] = nlen;

    /* Ultimo elemento da substring*/
    size_t last = nlen - 1;

    /* Preenchendo a bad character table com os valores retirados da substring
       O calculo � feito com base nessa equa��o: Valor = tamanho da substring - index da letra na substring - 1,
       nesse caso temos Valor = nLen - 1 - index.
    */
    for (scan = 0; scan < last; scan++) bad_char_skip[needle[scan]] = last - scan;

    /* ---- Do the matching ---- */

    /* Procurando na string enquanto a substring ainda pode ser contida nela */
    while (hlen >= nlen)
    {
        /* Scan do final da substring */
        for (scan = last; haystack[scan] == needle[scan]; scan--)
        {
            /* Se o primeiro byte bater, foi encontrado. */
            if (scan == 0)
            {
                return haystack;
            }
        }

        /* Sen�o, precisamos pular alguns bytes e comlar novamente.
        *  Nota-se que pulamos um valor baseado no ultimo byte da substring
        *  n�o importa onde n�o bateu. Ent�o se a substring for "abcd"
        *  pulamos baseado no "d" e esse valor ser� 4.
        */
        hlen -= bad_char_skip[haystack[last]];
        haystack += bad_char_skip[haystack[last]];
    }

    return NULL;
}

int main()
{
    unsigned char needle[] = "capivara";
    unsigned char haystack[] = "isso e um texto capivara para testes";

    const unsigned char* result = boyermoore_horspool_memmem(haystack, 36, needle, 8);
    std::cout << result << std::endl;
}