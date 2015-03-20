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

const char infile[] = "perb.in";
const char outfile[] = "perb.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 605;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN][MAXN];
int freq[MAXN][5];
short v[MAXN];
char s[MAXN];
int N, M;

int main() {
    fin >> N >> M;
    memset(dp, oo, sizeof(dp));
    fin >> (s + 1);
    for(int i = 1 ; i <= N ; ++ i)
        if(s[i] == 'A')
            v[i] = 0;
            else if(s[i] == 'C')
                v[i] = 1;
                else if(s[i] == 'G') v[i] = 2;
                    else v[i] = 3;
    for(int period = 1 ; period <= N ; ++ period) {
        for(int _left = 1 ; _left + 2*period - 1 <= N ; ++ _left) {
            int nrSecv = 1;
            int best = 0;
            int R = 0;
            for(int _right = _left; _right <= N ; ++ _right) {
                ++ R;
                if(R == period)
                    R = 0;
                if(nrSecv == 1)
                    freq[R][0] = freq[R][1] = freq[R][2] = freq[R][3] = 0;
                ++ freq[R][v[_right]];
                best += nrSecv - max(max(max(freq[R][0], freq[R][1]), freq[R][2]), freq[R][3]);
                if(R == 0) {
                    if(nrSecv > 1)
                        dp[_left][_right] = min(dp[_left][_right], best);
                    best = 0;
                    ++ nrSecv;
                }
            }
        }
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        fout << dp[x][y] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
