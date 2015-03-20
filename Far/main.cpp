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

const char infile[] = "far.in";
const char outfile[] = "far.out";

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

int N, M, P, T;

inline long long Count(int x, int p) {
    long long ret = 0, fc = p;
    while(fc <= x) {
        ret += x / fc;
        fc *= p;
    }
    return ret;
}

inline string Solve() {
    fin >> N >> M >> P;
    for(int i = 2 ; i * i <= P ; ++ i) {
        if(P % i)
            continue;
        int iPow = 0;
        while(P % i == 0) {
            P /= i;
            ++ iPow;
        }
        if(iPow > Count(N + M - 2, i) - Count(N - 1, i) - Count(M - 1, i))
            return "0";
    }
    if(P != 1 && 1 > Count(N + M - 2, P) - Count(N - 1, P) - Count(M - 1, P))
        return "0";
    return "1";
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test)
        fout << Solve() << '\n';
    fin.close();
    fout.close();
    return 0;
}
