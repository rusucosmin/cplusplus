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

const char infile[] = "dreptpal.in";
const char outfile[] = "dreptpal.out";

ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int P[MAXN][MAXN], N, M;
int a[MAXN];
int _left[MAXN], _right[MAXN];
int col[MAXN];

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
}

inline void buildManacher(int a[], int P[], int M) {
    int ind = 0, best = 0;
    for(int i = 1 ; i <= M ; ++ i) {
        if(i <= best)
            P[i] = min(best - i, P[2 * ind - i]);
        while(i - P[i] - 1 >= 0 && i + P[i] + 1 <= M && a[i - P[i] - 1] == a[i + P[i] + 1])
            ++ P[i];
        if(i + P[i] > best) {
            best = i + P[i];
            ind = i;
        }
    }
    for(int i = 1 ; i <= M ; ++ i)
        P[i] = 2 * P[i] + 1;
}

int main() {
    freopen(infile, "r", stdin);
    get(N);
    get(M);
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= M ; ++ j)
            get(a[j]);
        buildManacher(a, P[i], M);
    }
    /// now the problem is equivalent to the largest submatrix in a histogram
    int ans = 0;
    for(int j = 1 ; j <= M ; ++ j) {
        for(int i = 1 ; i <= N ; ++ i)
            col[i] = P[i][j];
        stack <int> st;
        col[0] = col[N + 1] = -1;
        st.push(0);
        for(int i = 1 ; i <= N ; ++ i) {
            while(!st.empty() && col[st.top()] >= col[i])
                st.pop();
            _left[i] = i - st.top();
            st.push(i);
        }
        while(!st.empty()) st.pop();
        st.push(N + 1);
        for(int i = N ; i > 0 ; -- i) {
            while(!st.empty() && col[st.top()] >= col[i])
                st.pop();
            _right[i] = st.top() - i;
            st.push(i);
        }
        for(int i = 1 ; i <= N ; ++ i)
            ans = max(ans, col[i] * (_right[i] + _left[i] - 1));
    }
    fout << ans << '\n';
    fout.close();
    return 0;
}
