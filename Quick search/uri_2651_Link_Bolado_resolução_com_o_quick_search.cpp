#include <iostream>
#include <string.h>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

/* Bad shift character table */
map <char, int> bad_shift_table;
map <char, int> ::iterator itr;

int get_last_char_position_in_pattern(string pattern, char ch){

    for (int i = pattern.size() - 1; i >= 0; i--){
        if (pattern[i] == ch)
            return i;
    }

}

int is_in_the_pattern(string pattern, char ch){

    int it_is = 0;
    for (int i = 0; i < pattern.size(); i++){
        if (pattern[i] == ch){
            it_is = 1;
            break;
        }
            
    }

    return it_is;
}

void pre_processing(string pattern, string text){

    
    for (int i = 0; i < text.size(); i++){
     
        if (is_in_the_pattern(pattern, text[i]) == 1){
            int shift = pattern.size() - get_last_char_position_in_pattern(pattern, text[i]);
            bad_shift_table.insert(pair<char, int>(text[i], shift));       
        }
        else{
            int shift = pattern.size() + 1;
            bad_shift_table.insert(pair<char, int>(text[i], shift));
        }        
    }
}
/* Return 1 if the pattern was found, 0 otherwise */
int search(string pattern, string text){

    int pattern_index = 0;
    int char_matched = 0;
    int n_matched = 0;
    int pos_begin_match = 0;

    for (int text_index = 0; text_index < text.size(); text_index++){

        if (text[text_index] == pattern[pattern_index]){

            char_matched++;
            pattern_index++;

	    /* Pattern found, no need to continue search */
            if (char_matched == pattern.size()){
                return 1;
        	}
        }
        else {
            itr = bad_shift_table.find(text[text_index + (pattern.size() - pattern_index)]);

            if (itr->second == 0)
                break;

            pos_begin_match += itr->second;
            text_index = pos_begin_match - 1;
            char_matched = 0;
            pattern_index = 0;  
        }
    }
    return 0;
}

int quick_search(string pattern, string tetx){

    /* Pre-processing stayed the same */
    pre_processing(pattern, tetx);

    return search(pattern, tetx);

}

int main(){

    string pattern = "zelda";

    string input;

    cin >> input;

    /* Convert input to lower_case */
    transform(input.begin(), input.end(), input.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (quick_search(pattern, input))
        cout << "Link Bolado\n";
    else
        cout << "Link Tranquilo\n";

    return 0;
}
