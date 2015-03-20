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

const char infile[] = "pavare2.in";
const char outfile[] = "pavare2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A, B;
char s[MAXN];

int Base = 10;

class Huge {
private:
    int v[MAXN];
    static const int BASE = 10;
public:
    Huge() {
        memset(v, 0, sizeof(v));
    }
    Huge(int x) {
        *this = x;
    }
    inline Huge operator = (int x) {
        memset(v, 0, sizeof(v));
        while(x) {
            v[++ v[0]] = x % BASE;
            x /= BASE;
        }
        return *this;
    }
    inline Huge operator + (Huge X) {
        int T = 0;
        Huge ret;
        int i;
        for(i = 1 ; i <= v[0] || i <= X.v[0] || T ; ++ i, T /= BASE)
            ret.v[i] = (T += v[i] + X.v[i]) % BASE;
        ret.v[0] = i - 1;
        return ret;
    }
    inline int operator == (Huge X) const {
        int i, n = v[0], m = X.v[0];
        if(n < m)
            return -1;
        if(m > n)
            return 1;
        for(i = n; i && v[i] == X.v[i]; --i);
        if(i == 0)
            return 0;
        if(v[i] < X.v[i])
            return -1;
        return 1;
    }
    inline void Print(ofstream &out) {
        for(int i = v[0] ; i ; -- i)
            out << v[i];
        out << '\n';
    }
    inline void toHuge(const char *c) {
        v[0] = 0;
        for(int i = strlen(c) - 1 ; i >= 0 ; -- i)
            v[ ++ v[0] ] = c[i] - '0';
    }
    inline void sub(const Huge B) {
        int i, t = 0;
        for (i = 1; i <= v[0]; i++) {
            v[i] -= ((i <= B.v[0]) ? B.v[i] : 0) + t;
            v[i] += (t = v[i] < 0) * BASE;
        }
      for (; v[0] > 1 && !v[v[0]]; -- v[0]);
    }
};

Huge dp[MAXN][MAXN][2], a, Ans;
char S[MAXN];

int main() {
    fin >> N >> A >> B >> (S + 1);
    a.toHuge(S + 1);
    dp[1][1][0] = dp[1][1][1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        for(int j = 2 ; j <= A ; ++ j) {
            dp[i][j][0] = dp[i - 1][j - 1][0];
            dp[i][1][1] = dp[i - 1][j - 1][0] + dp[i][1][1];
        }
        dp[i][1][1] = dp[i][1][1] + dp[i - 1][A][0];
        for(int j = 2 ; j <= B ; ++ j) {
            dp[i][j][1] = dp[i - 1][j - 1][1];
            dp[i][1][0] = dp[i - 1][j - 1][1] + dp[i][1][0];
        }
        dp[i][1][0] = dp[i][1][0] + dp[i - 1][B][1];
    }
    for(int i = 1 ; i <= A ; ++ i)
        dp[0][0][0] = dp[0][0][0] + dp[N][i][0];
    for(int i = 1 ; i <= B ; ++ i)
        dp[0][0][0] = dp[0][0][0] + dp[N][i][1];
    dp[0][0][0].Print(fout);
    int last = -1;
    for(int i = N ; i >= 1 ; ) {
        if(last != 0) {
           for(int j = A ; j ; -- j)
                if((dp[i][j][0] == a) < 0)
                    a.sub(dp[i][j][0]);
                else {
                    for(i -= j ; j ; -- j)
                        fout << "0";
                    last = 0;
                    break;
                }
        }
        if(last != 1) {
            for(int j = 1 ; j <= B && (i - j - 1) <= N ; ++ j)
                if((dp[i][j][1] == a) < 0)
                    a.sub(dp[i][j][1]);
                else {
                    for(i -= j ; j ; -- j)
                        fout << "1";
                    last = 1;
                    break;
                }
        }
    }
    fout << "\n";
    fin.close();
    fout.close();
    return 0;
}
