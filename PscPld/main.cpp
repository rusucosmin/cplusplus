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

const char infile[] = "pscpld.in";
const char outfile[] = "pscpld.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN], m[2*MAXN];
int sz, N, P[2 * MAXN];

int main() {
    fin.getline(s, MAXN);
    sz = strlen(s);
    m[++ N] = '#';
    for(int i = 0 ; i < sz ; ++ i) {
        m[++ N] = s[i];
        m[++ N] = '#';
    }
    int best = 0, ind = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        if(i <= best)
            P[i] = min(best - i, P[2 * ind - i]);
        while(i - P[i] - 1 >= 0 && i + P[i] + 1 <= N && m[i - P[i] - 1] == m[i + P[i] + 1])
            ++ P[i];
        if(i + P[i] > best) {
            best = i + P[i];
            ind = i;
        }
    }
    long long Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        Ans += (1 + P[i]) / 2;
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
