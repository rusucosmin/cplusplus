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

const char infile[] = "dame2.in";
const char outfile[] = "dame2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int N = 8;
const int M = 8 + 5;
char s[N + 5][N + 5];
pair<int, int> st[M * M], rez[M * M];
int top, reztop = oo;
int takenDS[M * M], takenDP[M * M], takencol[M * M], takenlin[M * M];

inline bool covered(const int &i, const int &j) {
    if(s[i][j] == '0' && (takencol[j] || takenlin[i] || takenDP[i - j + N] || takenDS[i + j]))
        return true;
    return false;
}

inline bool checkStep() {
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(s[i][j] == '0' && !covered(i, j))
                return false;
    return true;
}

void Back(int K) {
    if(K == N + 1) {
        if(top < reztop && checkStep()) {
            reztop = top;
            for(int i = 1 ; i <= reztop ; ++ i)
                rez[i] = st[i];
        }
        return ;
    }
    int nr = 0;
    for(int i = 1 ; i <= N ; ++ i)
        if(s[K][i] == '0' && !takencol[i] && !takenDP[K - i + N] && !takenDS[K + i]) {
            ++ nr;
            ++ takenlin[K];
            ++ takencol[i]; ++ takenDP[K - i + N]; ++ takenDS[K + i];
            st[++ top] = make_pair(K, i);
            Back(K + 1);
            -- top;
            -- takencol[i]; -- takenDP[K - i + N]; -- takenDS[K + i];
            -- takenlin[K];
        }
    Back(K + 1);
}

int main() {
    for(int i = 1 ; i <= N ; ++ i)
        fin >> (s[i] + 1);
    Back(1);
    if(reztop == oo)
        reztop = 0;
    fout << reztop << '\n';
    for(int i = 1 ; i <= reztop ; ++ i)
        fout << rez[i].first << ' ' << rez[i].second << ' ';
    fin.close();
    fout.close();
    return 0;
}
