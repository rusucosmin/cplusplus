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

const char infile[] = "strmatch.in";
const char outfile[] = "strmatch.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
char A[MAXN], B[MAXN];
int Prefix[MAXN];

inline void buildPrefix(const char *A, int N, int *Pi) {
    int K = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while(K > 0 && A[K + 1] != A[i])
            K = Pi[K];
        if(A[K + 1] == A[i])
            ++ K;
        Pi[i] = K;
    }
}

inline vector <int> getMatchesKMP(const char *A, int N, const char *B, int M) {
    buildPrefix(A, N, Prefix);
    vector <int> matches;
    int K = 0;
    for(int i = 1 ; i <= M ; ++ i) {
        while(K > 0 && A[K + 1] != B[i])
            K = Prefix[K];
        if(A[K + 1] == B[i])
            ++ K;
        if(K == N)
            matches.push_back(i - K);
    }
    return matches;
}

int main() {
    fin.getline(A + 1, MAXN);
    fin.getline(B + 1, MAXN);
    N = strlen(A + 1);
    M = strlen(B + 1);
    vector <int> Ans = getMatchesKMP(A, N, B, M);
    fout << Ans.size() << '\n';
    for(int i = 0 ; i < min(Ans.size(), 1000) ; ++ i)
        fout << Ans[i] << ' ';
    fout << '\n';
    fin.close();
    fout.close();
    return 0;
}
