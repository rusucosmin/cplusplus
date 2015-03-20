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

const char infile[] = "frumoasa.in";
const char outfile[] = "frumoasa.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int MOD = 1000000007;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N, P;

int lgPut(const int &a, const long long &n) {
    if(n == 1)
        return a;
    int aux = (1LL * a * a) % MOD;
    if(n & 1)
        return (1LL * a * lgPut(aux, (n - 1)/2)) % MOD;
    return lgPut(aux, n / 2);
}

int main() {
    fin >> N >> P;
    if(P >= 26) {
        fout << "0\n";
        return 0;
    }
    int Ans = 1;
    for(int i = 1 ; i <= P ; ++ i) {
        Ans = (1LL * Ans * (26 - i + 1)) % MOD;
    }
    int Sol = (1LL * Ans * lgPut(26 - P, N - P)) % MOD;
    fout << Sol << '\n';
    fin.close();
    fout.close();
    return 0;
}
