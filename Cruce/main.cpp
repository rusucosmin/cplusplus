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

const char infile[] = "cruce.in";
const char outfile[] = "cruce.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

/// brute
/// mai optimizat cu algoritmul lui manacher pt a caclula doua chestii de doua ori

int N, M;
char s[MAXN][MAXN];
long long Ans;

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> (s[i] + 1);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)  {
            int cx = i;
            int cy = j;
            int k1 = 0;
            int k2 = 0;
            while(cx - k1 >= 1 && cx + k1 <= N && s[cx-k1][cy] == s[cx+k1][cy])
                ++ k1;
            while(cy - k2 >= 1 && cy + k2 <= M && s[cx][cy-k2] == s[cx][cy+k2])
                ++ k2;
            Ans += 1LL * (k1 - 1) * (k2 - 1);
        }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
