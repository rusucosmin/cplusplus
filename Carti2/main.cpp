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

const char infile[] = "carti2.in";
const char outfile[] = "carti2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 13;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T;
int N, H, L, G;
int a[MAXN], b[MAXN];
int dp[1 << MAXN];

inline int bitCount(const int &conf) {
    int mask = conf, ret = 0;
    while(mask) {
        mask = mask&(mask - 1);
        ++ ret;
    }
    return ret;
}

inline int lsb(const int &conf) {
    return conf & (- conf);
}

inline bool isMinLex(int i, int j) {
    return lsb(i & (~j)) < lsb(j & (~i));
}

int main() {
    fin >> T;
    while(T --) {
        int Ans = 0;
        fin >> N >> H >> L >> G;
        for(int i = 0 ; i < N ; ++ i)
            fin >> a[i] >> b[i];
        memset(dp, oo, sizeof(dp));
        for(int i = 1 ; i < (1 << N) ; ++ i) {
            int lg = 0, hm = 0;
            for(int j = 0 ; j < N ; ++ j)
                if(i & (1 << j)) {
                    lg += b[j];
                    hm = max(hm, a[j]);
                }
            if(lg <= L)
                dp[i] = hm + G;
        }
        for(int i = 1 ; i < (1 << N) ; ++ i)
            for(int j = i ; j > 0 ; j = i & (j - 1)) {
                int s1 = j;
                int s2 = i ^ j;
                dp[i] = min(dp[i], dp[s1] + dp[s2]);
            }
        for(int i = 1 ; i < ( 1 << N) ; ++ i)
            if(dp[i] <= H && (bitCount(i) > bitCount(Ans) || (bitCount(i) == bitCount(Ans) && isMinLex(i, Ans))))
                Ans = i;
        fout << bitCount(Ans) << '\n';
        for(int i = 0 ; i < N ; ++ i)
            if(Ans & (1 << i))
                fout << i + 1 << ' ';
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
