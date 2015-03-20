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

const char infile[] = "prodiv.in";
const char outfile[] = "prodiv.out";

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

long long N, A = 1, B = 1;
long long Ans;

inline long long lgPow(long long a, long long p) {
    long long Ans = 1;
    for( ; p ; p >>= 1) {
        if(p & 1) {
            Ans = Ans * a;
        }
        a = a * a;
    }
    return Ans;
}

int main() {
    fin >> N >> A >> B;
    long long cn = N;
    for(long long i = 2 ; i * i <= cn ; ++ i) {
        if(N == 1)
            break;
        if(N % i)
            continue;
        long long iPower = 0;
        while(N % i == 0) {
            N /= i;
            ++ iPower;
        }
        long long aux = lgPow(i, iPower / 2);
        A = A * aux;
        B = B * aux;
        if(iPower & 1) {
            B *= i;
            ++ Ans;
        }
    }
    if(N > 1) {
        ++ Ans;
    }
    fout << A << ' ' << B << '\n' << (1LL << Ans) << '\n';
    fin.close();
    fout.close();
    return 0;
}
