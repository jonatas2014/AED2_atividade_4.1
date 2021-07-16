#include <iostream>
#include <string.h>
#include <map>

using namespace std;

/* Bad shift character table */
map <char, int> bad_shift_table;

/* An iterator for the map of the bad shift character table */
map <char, int> ::iterator itr;

/* Returns last position of the char in the pattern */
int get_last_char_position_in_pattern(char *pattern, char ch){

    for (int i = strlen(pattern) - 1; i >= 0; i--){
        if (pattern[i] == ch)
            return i;
    }

}

/* Verify if a text character is present in the pattern */
int is_in_the_pattern(char *pattern, char ch){

    int it_is = 0;
    for (int i = 0; i < strlen(pattern); i++){
        if (pattern[i] == ch){
            it_is = 1;
            break;
        }
            
    }

    return it_is;
}

/* Prepocessing */
void pre_processing(char *pattern, char *text){

    /* Construct the table by calculating for each text character its shift */
    for (int i = 0; i < strlen(text); i++){
     
        /* If the text character is in the pattern */
        if (is_in_the_pattern(pattern, text[i]) == 1){

            int shift = strlen(pattern) - get_last_char_position_in_pattern(pattern, text[i]);
            bad_shift_table.insert(pair<char, int>(text[i], shift));       
        }

        /* If the text character is not in the pattern */
        else{

            int shift = strlen(pattern) + 1;
            bad_shift_table.insert(pair<char, int>(text[i], shift));
        }         
    }
}

/* Search the pattern */
void search(char *pattern, char *text){

    int pattern_index = 0;
    int char_matched = 0;
    int n_matched = 0;
    int pos_begin_match = 0;

    for (int text_index = 0; text_index < strlen(text); text_index++){
        
        /* This happens each time we have a single character match */
        if (text[text_index] == pattern[pattern_index]){

            char_matched++;
            pattern_index++;

	    /* If the number of matching characters sequence equal to pattern size */
            /* We have a pattern match */
            if (char_matched == strlen(pattern)){

		cout << "Pattern found!\n";
		cout << pattern << "\n";
		cout << "Between positions " << text_index + 1 - strlen(pattern) + 1
		     << " and " << text_index + 1 << "\n";
		    
		n_matched++;
            }
        }

        /* Appy the correct shift each time we have a single character mismatch */
        else {
            
            itr = bad_shift_table.find(text[text_index + (strlen(pattern) - pattern_index)]);

            /* If the character does not correspond to one in the table */
            /* we are no longer in the text */
            if (itr->second == 0)
                break;

            pos_begin_match += itr->second;
            text_index = pos_begin_match - 1;
            char_matched = 0;
            pattern_index = 0;
        }
    }

    /* If the pattern was not found */
    if (n_matched == 0)
        cout << "Pattern not found\n";
}

/* A test */
int main()
{

    char text[] = "GCATCGCAGAGAGTATACAGTACG";
    
    char pattern[] = "GCAGAGAG";
    
    /* Prepocessing phase */
    pre_processing(pattern, text);

    /* Searching phase */
    search(pattern, text);
    
    
    return 0;
}
