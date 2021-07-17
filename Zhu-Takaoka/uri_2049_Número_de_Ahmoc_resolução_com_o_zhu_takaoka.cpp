#include <bits/stdc++.h>
using namespace std;

/* Testes do uri:
    1234
    837384937292379450545045672392303485065402302373543504864694450034302
    23034
    837384937292379450545045672392303485065402302373543504864694450034302 */

int ZTBC[10][10];

void ZTBCCalculation(int stringlen, int patternlen, string pattern){
    int i, j;
    for (i = 0; i < 10; ++i)
			for (j = 0; j < 10; ++j)
				ZTBC[i][j] = patternlen;
    
    for (i = 0; i < 10; ++i)
			ZTBC[i][pattern[0] - '0']
				= patternlen - 1;

    for (i = 1; i < patternlen - 1; ++i)
			ZTBC[pattern[i - 1] - '0']
				[pattern[i] - '0']
				= patternlen - 1 - i;
}

int main(){
    string pattern;
    string str;
    int h = 1;
    while (cin >> pattern && pattern != "0"){
        cin >> str;
        int i, j;
        int stringlen = str.size();
        int patternlen = pattern.size();
        ZTBCCalculation(stringlen, patternlen, pattern);
        j = 0;
        bool check = false;
        while (j <= stringlen - patternlen) {
                i = patternlen - 1;
                while (i >= 0
                    && pattern[i]
                            == str[i + j])
                    --i;
                if (i < 0) {
                    // Pattern detected
                    cout << "Instancia " << h << endl;
                    cout << "verdadeira" << endl;
                    /* cout << "Pattern Found at " << j + 1 << endl; */
                    j += patternlen;
                    check = true;
                }

                // Not detected
                else
                    j += ZTBC[str[j + patternlen - 2]
                            - '0']
                            [str[j + patternlen - 1]
                            - '0'];
        }
        if (check == false){
            cout << "Instancia " << h << endl;
            cout << "falsa" << endl;
        }
        h++;
    }
    return 0;
}