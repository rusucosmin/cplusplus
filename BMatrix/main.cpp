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

const char infile[] = "bmatrix.in";
const char outfile[] = "bmatrix.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 202;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
char a[MAXN][MAXN];
int up[MAXN][MAXN], aux[MAXN][MAXN];
int _left[MAXN], _right[MAXN];
int dp[MAXN][MAXN];

inline int Solve(int x1, int y1, int x2, int y2) {
    stack <int> st;
    int _area = 0;
    for(int i = x1 ; i <= x2 ; ++ i) {
        aux[i][y1-1] = -1;
        aux[i][y2+1] = -1;
        st.push(y1 - 1);
        for(int j = y1 ; j <= y2 ; ++ j) {
            aux[i][j] = min(up[i][j], i - x1 + 1);
            while(aux[i][st.top()] >= aux[i][j])
                st.pop();
            _left[j] = j - st.top();
            st.push(j);
        }
        while(!st.empty())
            st.pop();
        st.push(y2+1);
        for(int j = y2 ; j >= y1 ; -- j) {
            while(aux[i][st.top()] >= aux[i][j])
                st.pop();
            _right[j] = st.top() - j;
            st.push(j);
        }
        for(int j = y1 ; j <= y2 ; ++ j)
            _area = max(_area, aux[i][j] * (_left[j] + _right[j] - 1));
    }
    return _area;
}

int main() {
    fin >> N >> M;
    fin.get();
    for(int i = 1 ; i <= N ; ++ i) {
        fin.getline(a[i] + 1, MAXN);
        for(int j = 1 ; j <= M ; ++ j)
            if(a[i][j] == '0')
                up[i][j] = 1 + up[i - 1][j];
            else up[i][j] = 0;
    }
    int Ans = 0;
    for(int i = 1; i + 1 <= N ; ++ i) {
        Ans = max(Ans, Solve(1, 1, i, M) + Solve(i + 1, 1, N, M));
    //    cerr << "lin " << i << ' ' << Solve(1, 1, i, M) << ' ' << Solve(i + 1, 1, N, M) << '\n';
    }
    for(int i = 1; i + 1 <= M ; ++ i) {
        Ans = max(Ans, Solve(1, 1, N, i) + Solve(1, i + 1, N, M));
    //    cerr << "col " << i << ' ' << "1 1 " << N << ' ' << i << ' ' << Solve(1, 1, N, i) << ' ' << Solve(1, i + 1, N, M) << '\n';
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
