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

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

int T, N, Pi[MAXN];
char A[MAXN];

inline void BuildPrefix(const char *A) {
    int K = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while(K > 0 && A[K + 1] != A[i])
            K = Pi[K];
        if(A[K + 1] == A[i])
            ++ K;
        Pi[i] = K;
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        vector <pair<int, int> > Ans;
        cin >> N;
        cin >> (A + 1);
        BuildPrefix(A);
        for(int i = 2 ; i <= N ; ++ i) {
            if(Pi[i] && (!(i % (i - Pi[i]))))
                Ans.push_back(make_pair(i, i / (i - Pi[i])));
        }
        printf("Test case #%d\n", test);
        for(vector <pair<int, int> > :: iterator it = Ans.begin(), fin = Ans.end(); it != fin ; ++ it)
            printf("%d %d\n", it->first, it->second);
        printf("\n");
    }
    fin.close();
    fout.close();
    return 0;
}
