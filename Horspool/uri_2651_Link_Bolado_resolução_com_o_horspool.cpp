#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
#include<cstring>
#include <iostream>
 
using namespace std;

const unsigned char* boyermoore_horspool_memmem(const unsigned char* haystack, 
                                                size_t hlen,
                                                const unsigned char* needle,  
                                                size_t nlen)
{
    size_t scan = 0;
    size_t bad_char_skip[UCHAR_MAX + 1]; // = 256
  
    if (nlen <= 0 || !haystack || !needle)
        return NULL;
  
    for (scan = 0; scan <= UCHAR_MAX; scan++) bad_char_skip[scan] = nlen;
  
    size_t last = nlen - 1;
  
    for (scan = 0; scan < last; scan++) bad_char_skip[needle[scan]] = last - scan;
  
    while (hlen >= nlen)
    {
      
        for (scan = last; haystack[scan] == needle[scan]; scan--)
        {
            
            if (scan == 0) 
            {
                    return haystack;
            }
        }
  
        hlen     -= bad_char_skip[haystack[last]];
        haystack += bad_char_skip[haystack[last]];
    }
  
    return NULL;
}
 
int main()
{
    unsigned char needle[] = "zelda";
    string input;
    cin >> input;

    for_each(input.begin(), input.end(), [](char& c) {
        c = ::tolower(c);
        });

    unsigned char haystack[input.length()+1];
    strcpy((char *)haystack, input.c_str());

    int  needle_length = 5;
    int  haystack_length = input.length()+1;  
    
    const unsigned char* result = boyermoore_horspool_memmem( haystack, haystack_length, needle, needle_length);

    if (result == NULL)
    {
        std::cout << "Link Tranquilo" << std::endl;
    }
    else
    {
        std::cout << "Link Bolado" << std::endl;
    }
}

