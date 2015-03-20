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
#include <deque>

using namespace std;

const char infile[] = "nrsubsecv.in";
const char outfile[] = "nrsubsecv.out";

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

int N, M, A[MAXN], nrst[MAXN], nrdr[MAXN], top;
long long Sum[MAXN];

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> A[i];
        ++ A[i];
    }
    stack<int> St;
    for(int i = 1 ; i <= N ; ++ i) {
        while(!St.empty() && A[St.top()] > A[i]) {
            nrdr[St.top()] = i - 1;
            St.pop();
        }
        if(St.empty())
            nrst[i] = 1;
        else nrst[i] = St.top() + 1;
        St.push(i);
    }
    while(!St.empty()) {
        nrdr[St.top()] = N;
        St.pop();
    }
    for(int i = 1 ; i <= N ; ++ i)
        Sum[A[i]] += 1LL * (nrdr[i] - i + 1) * (i - nrst[i] + 1);
    for(int i = 1 ; i < MAXN ; ++ i)
        Sum[i] += Sum[i - 1];
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        ++ x; ++ y;
        fout << Sum[y] - Sum[x - 1] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
