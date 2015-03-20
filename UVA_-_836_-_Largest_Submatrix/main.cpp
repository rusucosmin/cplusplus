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
#include <cassert>
#include <stack>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN][MAXN];
int N, M, st[MAXN], dr[MAXN], T, C[MAXN][MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    cin.getline(s[0], MAXN);
    cin.getline(s[0], MAXN);
    while(T --) {
        N = 0;
        while(cin.getline(s[++ N] + 1, MAXN) && strlen(s[N] + 1)) ;
        -- N;
        M = strlen(s[N] + 1);
        assert(N == M);
        long long Ans = 0;
        memset(C, 0, sizeof(C));
        memset(dr, 0, sizeof(dr));
        memset(st, 0, sizeof(st));
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j) {
                if(s[i][j] == '1')
                    C[i][j] = C[i - 1][j] + 1;
                else C[i][j] = 0;
            }
        stack <int> St;
        for(int i = 1 ; i <= N ; ++ i) {
            C[i][0] = C[i][M + 1] = -1;
            St.push(0);
            for(int j = 1 ; j <= M ; ++ j) {
                while(!St.empty() && C[i][St.top()] >= C[i][j])
                    St.pop();
                st[j] = j - St.top();
                St.push(j);
            }
            while(!St.empty())
                St.pop();
            St.push(M + 1);
            for(int j = M ; j > 0 ; -- j) {
                while(!St.empty() && C[i][St.top()] >= C[i][j])
                    St.pop();
                dr[j] = St.top() - j;
                St.push(j);
            }
            while(!St.empty())
                St.pop();
            for(int j = 1 ; j <= M ; ++ j)
                Ans = max(Ans, 1LL * (dr[j] + st[j] - 1) * C[i][j]);
        }
        cout << Ans << "\n";
        if(T)
            cout << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
