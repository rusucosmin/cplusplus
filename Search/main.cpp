#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "search.in";
const char outfile[] = "search.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int MAXL = 5005;
const int SIGMA = 26;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, nxt[MAXN][MAXL][SIGMA], st[MAXN][MAXL];
char s[MAXN][MAXL], top;

inline void preProcess(void) {
    memset(nxt, oo, sizeof(nxt));
    for(int i = 1 ; i <= N ; ++ i) {
        int sz = strlen(s[i]);
        for(int j = sz - 1 ; j >= 0 ; -- j)
            for(int k = 0 ; k < 26 ; ++ k) {
                nxt[i][j][k] = nxt[i][j + 1][k];
                if(s[i][j] == k + 'a')
                    nxt[i][j][k] = j + 1;
            }
    }
}

inline void solve() {
    int Ans = 0;
    top = 1;
    while( M -- ) {
        char c;
        fin >> c;
        if(c == '-')
            -- top;
        else {
            for(int i = 1 ; i <= N ; ++ i)
                if(st[i][top] != oo)
                    st[i][top + 1] = nxt[i][st[i][top]][c - 'a'];
                else st[i][top + 1] = oo;
            ++ top;
        }
        Ans = 0;
        for(int i = 1 ; i <= N ; ++ i)
            if(st[i][top] != oo)
                ++ Ans;
        fout << Ans << '\n';
    }
}

int main() {
    fin >> N >> M;
    fin.get();
    for(int i = 1 ; i <= N ; ++ i) {
        s[i][0] = ' ';
        fin.getline(s[i] + 1, MAXL);
    }
    preProcess();
    solve();
    fin.close();
    fout.close();
    return 0;
}
