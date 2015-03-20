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
#include <stack>

using namespace std;

const char infile[] = "compact.in";
const char outfile[] = "compact.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int n;
int p[MAXN], leftmin[MAXN], leftmax[MAXN], level[MAXN], mini[MAXN];
stack <int> stmax, stmin;
long long sol = 0;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        fin >> p[i];

        mini[i] = i;

        while(!stmin.empty() && p[stmin.top()] >= p[i])
            stmin.pop();
        if(!stmin.empty())
            leftmin[i] = stmin.top();
        else leftmin[i] = 0;

        stmin.push(i);

        level[i] = level[leftmin[i]] + 1;

        while(!stmax.empty() && p[stmax.top()] <= p[i]) {
            if(p[mini[i]] > p[mini[stmax.top()]])
                mini[i] = mini[stmax.top()];
            stmax.pop();
        }
        if(!stmax.empty())
            leftmax[i] = stmax.top();
        else leftmax[i] = 0;
        stmax.push(i);
        if(i - mini[i] + 1 >= 3) {
            sol += (level[i] - level[mini[i]]);
            if(p[i] > p[i - 1])
                -- sol;
        }
    }
    fout << sol << '\n';
    fin.close();
    fout.close();
    return 0;
}
