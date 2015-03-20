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

const char infile[] = "teren.in";
const char outfile[] = "teren.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, X, Ans, A[MAXN][MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> M >> X;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            int x;
            fin >> x;
            A[i][j] = A[i - 1][j] + x;
        }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i ; j <= N ; ++ j) {
            int st = 1, sum = 0;
            for(int dr = 1 ; dr <= M ; ++ dr) {
                sum += (A[j][dr] - A[i - 1][dr]);
                while(sum > X) {
                    sum -= (A[j][st] - A[i - 1][st]);
                    ++ st;
                }
                if(st <= dr)
                    Ans = max(Ans, (j - i + 1) * (dr - st + 1));
            }
        }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
