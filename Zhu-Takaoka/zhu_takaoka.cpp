#include <bits/stdc++.h>
using namespace std;

string str = "ABCABCDEABCDEA";
string pattern = "ABCD";

int stringlen = 14;
int patternlen = 4;

int ZTBC[26][26];

void ZTBCCalculation(){
    int i, j;
    for (i = 0; i < 26; ++i)
			for (j = 0; j < 26; ++j)
				ZTBC[i][j] = patternlen;
    
    for (i = 0; i < 26; ++i)
			ZTBC[i][pattern[0] - 'A']
				= patternlen - 1;

    for (i = 1; i < patternlen - 1; ++i)
			ZTBC[pattern[i - 1] - 'A']
				[pattern[i] - 'A']
				= patternlen - 1 - i;
}

int main(){
    int i, j;
    ZTBCCalculation();
    j = 0;

    while (j <= stringlen - patternlen) {

			i = patternlen - 1;
			while (i >= 0
				&& pattern[i]
						== str[i + j])
				--i;
			if (i < 0) {

				// Pattern detected
				cout << "Pattern Found at " << j + 1 << endl;
				j += patternlen;
			}

			// Not detected
			else
				j += ZTBC[str[j + patternlen - 2]
						- 'A']
						[str[j + patternlen - 1]
						- 'A'];
		}

    return 0;
}