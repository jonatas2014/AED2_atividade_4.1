#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <iostream>

using namespace std;

const unsigned char* boyermoore_horspool_memmem(const unsigned char* haystack,
    size_t hlen,
    const unsigned char* needle,
    size_t nlen)
{
    size_t scan = 0;
    size_t bad_char_skip[UCHAR_MAX + 1]; // = 256

    /* Check para garantir que existe uma string, uma subtring e que a substring é maior que a string */
    if (nlen <= 0 || !haystack || !needle)
        return NULL;

    /* Pré-processamento */
    /* Inicializa a bad character table */
    /* Quando um caracter que não esta na needle é
     * encontrada, podemos pular todo o tamanho da
     * needle com segurança
     */
    for (scan = 0; scan <= UCHAR_MAX; scan++) bad_char_skip[scan] = nlen;

    /* Ultimo elemento da substring */
    size_t last = nlen - 1;

    /* Preenchendo a bad character table com os valores retirados da substring */
    for (scan = 0; scan < last; scan++) bad_char_skip[needle[scan]] = last - scan;

    /* Matching */

    /* Procurando na string enquanto a substring ainda pode ser contida nela */
    while (hlen >= nlen)
    {
        /* Scan do final da substring */
        for (scan = last; haystack[scan] == needle[scan]; scan--)
        {
            /* Se o primeiro byte bater, foi encontrado */
            if (scan == 0)
            {
                return haystack;
            }
        }

        /* Senão, precisamos pular alguns bytes e comlar novamente */
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

