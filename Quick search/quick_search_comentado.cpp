#include <iostream>
#include <string.h>
#include <map>

using namespace std;

/* Tabela do bad shift character */
map <char, int> bad_shift_table;

/* Um iterador para o mapa da tabela do bad shift character */
map <char, int> ::iterator itr;

/* Retorna a última posição do caracter no padrão */
int get_last_char_position_in_pattern(char *pattern, char ch){

    for (int i = strlen(pattern) - 1; i >= 0; i--){
        if (pattern[i] == ch)
            return i;
    }

}

/* Verifica se o caracter do texto está presente no padrão */
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

/* Pré-processamento */
void pre_processing(char *pattern, char *text){

    /* Constrói a tabela calculando para cada caracter seu deslocamento */ 
    for (int i = 0; i < strlen(text); i++){
     
        /* Se o caracter do texto está no padrão */
        if (is_in_the_pattern(pattern, text[i]) == 1){

            int shift = strlen(pattern) - get_last_char_position_in_pattern(pattern, text[i]);
            bad_shift_table.insert(pair<char, int>(text[i], shift));       
        }

        /* Se o caracter do texto não está no padrão */
        else{

            int shift = strlen(pattern) + 1;
            bad_shift_table.insert(pair<char, int>(text[i], shift));
        }         
    }
}

/* Busca */
void search(char *pattern, char *text){

    int pattern_index = 0;
    int char_matched = 0;
    int n_matched = 0;
    int pos_begin_match = 0;

    for (int text_index = 0; text_index < strlen(text); text_index++){
        
        /* Correspondência de caracter */
        if (text[text_index] == pattern[pattern_index]){

            char_matched++;
            pattern_index++;

	    /* Se o número de caracter correspondentes em sequência é igual ao tamnho do padrão,
	     * temos uma ocorrência do padrão 
	     */
            if (char_matched == strlen(pattern)){

		cout << "Pattern found!\n";
		cout << pattern << "\n";
		cout << "Between positions " << text_index + 1 - strlen(pattern) + 1
		     << " and " << text_index + 1 << "\n";
		    
		n_matched++;
            }
        }

        /* Não correspondência de caracter: aplicar o deslocamento correto */
        else {
            
            itr = bad_shift_table.find(text[text_index + (strlen(pattern) - pattern_index)]);

            /* Se não é um caracter do texto, isso significa o término do texto */
            if (itr->second == 0)
                break;

            pos_begin_match += itr->second;
            text_index = pos_begin_match - 1;
            char_matched = 0;
            pattern_index = 0;
        }
    }

    /* Se nenhuma ocorrência foi encontrada */
    if (n_matched == 0)
        cout << "Pattern not found\n";
}

int main()
{

    char text[] = "GCATCGCAGAGAGTATACAGTACG";
    
    char pattern[] = "GCAGAGAG";
    
    /* Fase de pré-processamento */
    pre_processing(pattern, text);

    /* Fase de busca */
    search(pattern, text);
    
    return 0;
}

