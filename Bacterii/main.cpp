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

const char infile[] = "bacterii.in";
const char outfile[] = "bacterii.out";

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

inline int lgPow(int a,unsigned long long p, int MOD) {
    int ans = 1;
    for( ; p ; p >>= 1ULL) {
        if(p & 1ULL)
            ans = (1LL * ans * a) % MOD;
        a = (1LL * a * a) % MOD;
    }
    return ans;
}

int T;
int N, M;
unsigned long long K;

int main() {
    fin >> T;
    while( T -- ) {
        fin >> N >> K >> M;
        if(M == 3) {
            if((N - 1) % 3 == 0)
                fout << "1\n";
            else
                fout << "2\n";
            continue;
        }
        if(N == 1 || (N - 1) % M == 0) {
            fout << "1\n";
            continue;
        }
        int R = lgPow(2, K, M - 1);
        fout << ((lgPow(N - 1, 1ULL * R, M) + 1) % M) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
