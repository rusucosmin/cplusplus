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

const char infile[] = "echilibru.in";
const char outfile[] = "echilibru.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 20;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, a[MAXN], M;

inline int bitCount(int x) {
    int ret = 0;
    while(x) {
        ret ++;
        x = x & (x - 1);
    }
    return ret;
}

inline long long sum(int x) {
    long long ret = 0;
    for(int i = 0 ; i < M ; ++ i)
        if(x & (1 << i))
            ret += 1LL * a[i];
    return ret;
}

inline void toBit(int x) {
    fout << x << " : " ;
    for(int i = 0 ; i < M ; ++ i)
        if(x & (1 << i))
            fout << i << ' ';
    fout << '\n';
}

int main() {
    fin >> T;
    long long Ans = 0;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N;
        for(int i = 0 ; i < 2*N ; ++ i)
            fin >> a[i];
        M = 2 * N;
        int maxConf = (1 << M);
        int ok = 0;
        for(int i = 0 ; i < maxConf && !ok ; ++ i) {
            if(bitCount(i) != N)
                continue;
            int j = ((maxConf - 1) ^ i);
            //toBit(i);
            //fout << sum(i) << '\n';
            //toBit(j);
            //fout << sum(j) << '\n';
            //fout << toBit(i) << ' ' << toBit(j) << '\n';
            if(sum(i) == sum(j))
                ok = 1;
        }
        Ans = (Ans << 1) + ok;
        //cerr << ok << ' ';
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
