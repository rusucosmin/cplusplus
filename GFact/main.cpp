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

const char infile[] = "gfact.in";
const char outfile[] = "gfact.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MAXK = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int K, F[MAXK], iPower[MAXN];

inline void Factorize(int N, int Q) {
    for(int i = 2 ; 1LL * i * i <= N ; ++ i) {
        if(N % i)   continue;
        F[++ K] = i;
        while(N % i == 0) {
            N /= i;
            iPower[K] += Q;
        }
    }
    if(N > 1) {
        F[++ K] = N;
        iPower[K] = Q;
    }
}

inline bool Check(const long long valueToCheck) {
    for(int i = 1 ; i <= K ; ++ i) {
        long long actFact = F[i];
        long long sum = 0;
        while(valueToCheck >= actFact && sum < 1LL * iPower[i]) {
            sum += valueToCheck / actFact;
            actFact *= F[i];
        }
        if(sum < 1LL * iPower[i])
            return false;
    }
    return true;
}

inline long long binarySearch() {
    long long li = 0;
    long long ls = (1LL << 62);
    long long Ans = ls;
    while(li <= ls) {
        long long mid = ((li + ls) >> 1);
        if(Check(mid)) {
            ls = mid - 1;
            Ans = mid;
        }
        else li = mid + 1;
    }
    return Ans;
}

int main() {
    int P, Q;
    fin >> P >> Q;
    Factorize(P, Q);
    fout << binarySearch() << '\n';
    fin.close();
    fout.close();
    return 0;
}
