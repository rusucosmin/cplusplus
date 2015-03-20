#include <fstream>
#include <string.h>

using namespace std;

const char infile[] = "mesaj2.in";
const char outfile[] = "mesaj2.out";

const short MAXN = 1005;
const short SIGMA = 127 - 33;

char word[MAXN];
short nxt[MAXN][SIGMA + 33 + 5], dp[MAXN];

int main() {
    int Ans, j, actPos, i, st, ch, L, N;
    ifstream fin(infile);
    ofstream fout(outfile);
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    fin.getline(word + 1, MAXN);
    L = strlen(word + 1);
    for(ch = 0 ; ch <= SIGMA ; ++ ch) {
        j = L + 1;
        nxt[L + 1][ch] = L + 1;
        for(i = L ; i ; -- i) {
            if(word[i] - 33 == ch)
                j = i;
            nxt[i][ch] = j;
        }
    }
    for(i = 1 ; i <= L + 1 ; ++ i)
        dp[i] = L + 1;
    fin >> N;
    fin.get();
    for(i = 1 ; i <= N ; ++ i) {
        fin.getline(word + 1, MAXN);
        for(st = 1 ; st <= L ; ++ st) {
            for(j = st - 1, actPos = 1 ; word[actPos] && j < dp[st] ; ++ actPos)
                j = nxt[j + 1][word[actPos] - 33];
            if(dp[st] > j)
                dp[st] = j;
        }
        Ans = 0;
        for(j = 1 ; dp[j] <= L ; ++ Ans, j = dp[j] + 1);
        fout << Ans << '\n';
    }
    return 0;
}
