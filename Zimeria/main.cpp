#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

const char infile[] = "zimeria.in";
const char outfile[] = "zimeria.out";

ifstream fin(infile);
ofstream fout(outfile);

const int BASE = 12;

int P, N, ans, complexity[26];
char letter[12], word[6], sol[6];
int _count[1 + BASE*BASE*BASE*BASE*BASE];

inline int getCode(const char *s) {
    int ret = 0;
    for(int i = 0 ; i < 5 ; ++ i)
        ret = ret * BASE + complexity[s[i] - 'a'];
    return ret;
}

inline void toString(int nr) {
    sol[5] =  NULL;
    for(int i = 4 ; i >= 0 ; -- i) {
        sol[i] = letter[nr%12];
        nr = nr / BASE;
    }
}

int main() {
    fin >> P >> N;
    fin >> letter;
    for(int i = 0 ; i < 12 ; ++ i)
        complexity[letter[i] - 'a'] = i;
    for(int i = 0 ; i < N ; ++ i) {
        fin >> word;
        int nr = getCode(word);
        if(!_count[nr])
            ++ ans;
        ++ _count[nr];
    }
    if(P == 1)
        fout << ans << '\n';
    else {
        for(int j = 0 ; j < BASE * BASE * BASE * BASE * BASE + 1; ++ j) {
            if(_count[j] == 0)
                continue;
            toString(j);
            for(int i = 0 ; i < _count[j] ; ++ i)
                fout << sol << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
