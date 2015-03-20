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
#include <cassert>

using namespace std;

const char infile[] = "pari.in";
const char outfile[] = "pari.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, d, S[MAXN], father[MAXN];
string s[MAXN];
bitset <MAXN> used;
bitset <MAXN> Color;
Graph G;
vector <pair<int, int> > Edges;

inline int gcd(int a, int b) {
    if(!b)
        return a;
    return gcd(b, a % b);
}

inline int getParity(string s) {
    if(s == "par")
        return 0;
    return 1;
}

int dfs(int node) {
    int ret = Color[node];
    used[node] = true;
    for(It it = G[node].begin(), fin = G[node].end(); it != fin ; ++ it)
        if(!used[*it])
            ret += dfs(*it);
    return ret;
}

void Write(int node, int val) {
    if(father[node]) {
        Write(father[node], val * -1);
        assert(1 <= node && node <= N);
        assert(1 <= father[node] && father[node] <= N);

        fout << node << ' ' << father[node] << ' ' << val << ' ';
    }
}

inline void bfsBlack(int node) {
    queue <int> Q;
    used.reset();
    memset(father, 0, sizeof(father));

    Color[node] = 0;
    Q.push(node);
    used[node] = 1;

    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();
        for(It it = G[node].begin(), fin = G[node].end(); it != fin ; ++ it)
            if(!used[*it]) {

                father[*it] = node;
                used[*it] = 1;

                if(Color[*it] == 1) {
                    int act = 1;
                    Color[*it] = 0;
                    Write(*it, 1);
                    return;
                }

                Q.push(*it);
            }
    }
}

int main() {
    fin >> N >> d;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> S[i] >> s[i];
        if(S[i] % 2 != getParity(s[i]))
            Color[i] = 1;
        for(int j = 1 ; j < i ; ++ j)
            if( (j % 2) != (i % 2) && __gcd(i, j) >= d) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
    }
    bool hasAnswer = true;
    for(int i = 1 ; i <= N && hasAnswer; ++ i)
        if(!used[i])
            if(dfs(i) % 2 == 1)
               hasAnswer = false;
    if(!hasAnswer) {
        fout << "0 0 0\n";
        fin.close();
        fout.close();
        return 0;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(Color[i])
            bfsBlack(i);
    fin.close();
    fout.close();
    return 0;
}
