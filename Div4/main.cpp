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

const char infile[] = "div4.in";
const char outfile[] = "div4.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int MAXK = 1000005;
const int MOD = 1000003;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN];
int K, fact[MAXK];
long long Ans;
/// ultimele doua cifre sunt fixate...
/// deci fixez doua cifre din primele K
/// cifrele impare de pe ultima cifra
/// iau o cifra para si o combin cu una din fata ei cu alta
/// C[N - 2][K - 2] +

inline bool check(char x, char y) {
    return ((10 * (x - '0') + (y - '0')) % 4 == 0);
}

int lgPut(const int &A, const int &N) {
    if(N == 1)
        return (1LL*A) % MOD;
    int Square = (1LL * A * A) % MOD;
    if(N % 2)
        return (A * 1LL * lgPut(Square, (N - 1)/ 2)) % MOD;
    return lgPut(Square, N / 2);
}

inline int Comb(int N, int K) {
    int aux1 = lgPut(fact[K], MOD - 2);
    int aux2 = lgPut(fact[N - K], MOD - 2);
    return (1LL * fact[N] * aux1 * aux2) % MOD;
}

int main() {
    fact[0] = fact[1] = 1;
    for(int i = 2 ; i < MAXK ; ++ i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    fin >> (s + 1) >> K;
    int N = strlen(s + 1);
    for(int i = N ; i >= 1 ; -- i)
        if(((s[i] - '0') % 2) == 0) {
            if(K - (N - i) >= i - 1) {
                if((s[i] - '0') % 4 == 0) {
                    ++ Ans;
                    //Ans += Comb(K - (N - i), K - i);
                    //continue;
                }
            }
            for(int j = i - 1, aux = 0 ; j >= 1 && K - (N - i) - aux >= 0 ; -- j, ++ aux) {
                if(check(s[j], s[i])) {
                    //fout << j << ' ' << i << '\n';
                    Ans += Comb(N - 2, K - (N - i) - aux);
                }
        }
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
