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

const char infile[] = "culmi.in";
const char outfile[] = "culmi.out";

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

long long fact[MAXN];
int N, K;

int main() {
    fact[0] = 1;
    for(int i = 1 ; i <= 100 ; ++ i)
        fact[i] = 1LL * fact[i - 1] * i;
    fin >> N >> K;
    long long Ans = (1LL * fact[N] / (fact[K - 1] * fact[N - K + 1]) * fact[N - 1] / (fact[K - 1] * fact[N - K]));
    fout << Ans / K << '\n';
    fin.close();
    fout.close();
    return 0;
}
