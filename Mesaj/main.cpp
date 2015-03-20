#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "mesaj.in";
const char outfile[] = "mesaj.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int MAXM = 1605;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, nxt[MAXM][27], dp[MAXM], lg[MAXM];
char S[MAXM], word[MAXN][25];

int main() {
    fin >> N >> M;
    fin >> (S + 1);
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> (word[i] + 1);
        lg[i] = strlen(word[i] + 1);
    }
    for(char i = 'a' ; i <= 'z' ; ++ i) {
        nxt[0][i - 'a'] = oo;
        nxt[1][i - 'a'] = oo;
    }
    nxt[1][S[1]-'a'] = 1;
    for(int i = 2 ; i <= M ; ++ i) {
        for(char j = 'a' ; j <= 'z' ; ++ j)
            nxt[i][j - 'a'] = nxt[i - 1][j - 'a'];
        nxt[i][S[i] - 'a'] = i;
    }
    for(int i = 1 ; i <= M ; ++ i) {
        dp[i] = i;
        for(int j = 1 ; j <= N ; ++ j) {
            int poz = i;
            bool ok = 1;
            for(int k = lg[j]; k >= 1 ; -- k) {
                poz = nxt[poz][word[j][k] - 'a'];
                if(poz == oo) {
                    ok = 0;
                    break;
                }
                -- poz;
            }
            if(ok)  dp[i] = min(dp[i], dp[poz] + i - poz - lg[j]);
        }
    }
    fout << dp[M] << '\n';
    fin.close();
    fout.close();
    return 0;
}
