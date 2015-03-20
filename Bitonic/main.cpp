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

const char infile[] = "bitonic.in";
const char outfile[] = "bitonic.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M;
int a[MAXN];
int dp1[MAXN], dp2[MAXN];

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N;
        for(int i = 1 ; i <= N ; ++ i)
            fin >> a[i];
        for(int i = N ; i > 0 ; -- i) {
            dp1[i] = 1;
            for(int j = i + 1 ; j <= N ; ++ j)
                if(a[i] < a[j] && dp1[i] < dp1[j] + 1)
                    dp1[i] = dp1[j] + 1;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            dp2[i] = 1;
            for(int j = 1 ; j < i ; ++ j) {
                if(a[j] > a[i] && dp2[i] < dp2[j] + 1)
                    dp2[i] = dp2[j] + 1;
            }
        }
        int Ans = 0;
        for(int i = 1 ; i <= N ; ++ i)
            Ans = max(Ans, dp1[i] + dp2[i] - 1);
        for(int i = N ; i > 0 ; -- i) {
            dp2[i] = 1;
            for(int j = i + 1 ; j <= N ; ++ j)
                if(a[i] > a[j] && dp2[i] < dp2[j] + 1)
                    dp2[i] = dp2[j] + 1;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            dp1[i] = 1;
            for(int j = 1 ; j < i ; ++ j) {
                if(a[j] < a[i] && dp1[i] < dp1[j] + 1)
                    dp1[i] = dp1[j] + 1;
            }
        }
        for(int i = 1 ; i <= N ; ++ i)
            Ans = max(Ans, dp1[i] + dp2[i] - 1);
        fout << Ans << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
