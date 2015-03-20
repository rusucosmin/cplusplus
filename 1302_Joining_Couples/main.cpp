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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int father[MAXN], dp[MAXN];

#define fin cin
#define fout cout

inline int BFs(const int &A, const int &B) {
    memset(dp, -1, sizeof(dp));
    memset(father, 0, sizeof(father));
    dp[A] = 0;
    dp[B] = 0;
    father[A] = A;
    father[B] = B;
    queue <int> Q;
    Q.push(A);
    Q.push(B);
    if(A == B)
        return 0;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(dp[*it] == -1) {
                dp[*it] = dp[Node] + 1;
                father[*it] = father[Node];
                Q.push(*it);
            }
            else if(father[Node] != father[*it])
                return dp[Node] + dp[*it] + 1;
    }
    return -1;
}

int main() {
    cin.sync_with_stdio(false);
    int N, Q;
    while(fin >> N) {
        for(int i = 1 ; i <= N ; ++ i)
            vector<int>().swap(G[i]);
        for(int i = 1 ; i <= N ; ++ i) {
            int x;
            fin >> x;
            G[i].push_back(x);
        }
        fin >> Q;
        for(int i = 1 ; i <= Q ; ++ i) {
            int A, B;
            fin >> A >> B;
            fout << BFs(A, B) << '\n';
        }
    }
    return 0;
}
