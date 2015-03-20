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

const char infile[] = "raci.in";
const char outfile[] = "raci.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 500005;
const int SIGMA = 26;
const char begLetter = 'a';
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

string s;
char st[MAXN], fn[MAXN];
int N, K, dp[MAXN];
deque <int> dq[SIGMA];
int ans;

inline int getCode(char a) {
    return a - begLetter;
}

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> s;
        dp[i] = 1;
        st[i] = s[0];
        fn[i] = s[s.size() - 1];
        int code = getCode(st[i]);
        while(!dq[code].empty() && i - dq[code].front() > K)
            dq[code].pop_front();
        if(!dq[code].empty())
            dp[i] = dp[dq[code].front()] + 1;
        code = getCode(fn[i]);
        while(!dq[code].empty() && dp[dq[code].back()] <= dp[i])
            dq[code].pop_back();
        dq[code].push_back(i);
        ans = max(ans, dp[i]);
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
