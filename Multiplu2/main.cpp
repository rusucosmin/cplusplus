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

const char infile[] = "multiplu2.in";
const char outfile[] = "multiplu2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 10000;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int lgPow(const int &a, const int &n) {
    if(n == 1)
        return a;
    int aux = (a * a) % MOD;
    if(n & 1)
        return (a * lgPow(aux, (n - 1) / 2)) % MOD;
    return lgPow(aux, n / 2);
}

int main() {
    int Ans = 1, N, K, aux;
    fin >> N >> K;
    for(int i = 2, aux = N; i * i <= aux ; ++ i)
        if(N % i == 0) {
            int cnt = 0;
            while(N % i == 0) {
                ++ cnt;
                N /= i;
            }
            Ans = (1LL * Ans * (lgPow(cnt + 1, K) - lgPow(cnt, K) + MOD)) % MOD;
        }
    if(N > 1)
        Ans = (1LL * Ans * (lgPow(2, K) - 1 + MOD)) % MOD;
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
