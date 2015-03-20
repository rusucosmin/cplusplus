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

const char infile[] = "secvmax.in";
const char outfile[] = "secvmax.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, A[MAXN], st[MAXN], dr[MAXN], best[MAXN], ind[MAXN];
int Ans[MAXN];
stack <int> S;

struct classComp {
    inline bool operator() (const int &a, const int &b) const {
        return A[a] < A[b];
    }
};

inline int binarySearch(const int &Q) {
    int li = 1, ls = N;
    int ret = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(A[ind[mid]] <= Q) {
            ret = ind[mid];
            li = mid + 1;
        }
        else ls = mid - 1;
    }
    return ret;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> A[i];
        while(!S.empty() && A[S.top()] <= A[i]) {
            dr[S.top()] = i - 1;
            S.pop();
        }
        if(S.empty())
            st[i] = 1;
        else st[i] = S.top() + 1;
        S.push(i);
    }
    while(!S.empty()) {
        dr[S.top()] = N;
        S.pop();
    }
    for(int i = 1 ; i <= N ; ++ i) {
        best[i] = dr[i] - st[i] + 1;
        ind[i] = i;
    }
    sort(ind + 1, ind + N + 1, classComp());
    for(int i = 1 ; i <= N ; ++ i)
        Ans[ind[i]] = max(best[ind[i]], Ans[ind[i - 1]]);
    for(int i = 1 ; i <= M ; ++ i) {
        int Q;
        fin >> Q;
        fout << Ans[binarySearch(Q)] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
