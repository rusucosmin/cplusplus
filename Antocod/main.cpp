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

const char infile[] = "antocod.in";
const char outfile[] = "antocod.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
typedef unsigned long long ull;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline int lgPow(int a, int p, int mod) {
    int ans = 1;
    for( ; p ; p >>= 1) {
        if(p & 1)
            ans = (1LL * ans * a) % mod;
        a = (1LL * a * a) % mod;
    }
    return ans;
}

int main() {
    int sum = 0;
    int N, M;
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x;
        fin >> x;
        sum = (sum + x) % 666013;
    }
    fout << lgPow(sum, N, 666013);
    fin.close();
    fout.close();
    return 0;
}
