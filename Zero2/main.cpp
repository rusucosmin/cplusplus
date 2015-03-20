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

const char infile[] = "zero2.in";
const char outfile[] = "zero2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 25;
const long long oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int K;
int desc[MAXN], iPow[MAXN];

inline void Factorize(int B) {
    K = 0;
    for(int i = 2 ; i * i <= B ; ++ i) {
        if(B % i)
            continue;
        desc[++ K] = i;
        iPow[K] = 0;
        while(B % i == 0) {
            B /= i;
            ++ iPow[K];
        }
    }
    if(B > 1) {
        desc[++ K] = B;
        iPow[K] = 1;
    }
}

inline long long Solve(int N, int B) {
    Factorize(B);
    long long Ans = oo * oo;
    for(int i = 1 ; i <= K ; ++ i) {
        long long temp = 0, prime = desc[i];
        while(prime <= N) {
            long long k = (N / prime);
            temp += 1LL * prime * k * (k - 1) / 2;
            temp += 1LL * (N - prime * k + 1) * k;
            prime *= desc[i];
        }
        Ans = min(Ans, 1LL * temp / (1LL * iPow[i]));
    }
    return Ans;
}

int main() {
    for(int i = 0 ; i < 10 ; ++ i) {
        int N, B;
        fin >> N >> B;
        fout << Solve(N, B) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
