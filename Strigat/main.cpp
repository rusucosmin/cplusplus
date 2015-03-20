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
#include <unordered_map>

using namespace std;

const char infile[] = "strigat.in";
const char outfile[] = "strigat.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;
const int SIGMA = 26;
const char begAlpha = 'a';

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }


inline int getCode(const char &s) {
    return s - begAlpha;
}
int nrNodes;

struct Node {
    Node *sons[SIGMA], *fail;
    int value, id;
    Node() {
        value = id = 0;
        memset(sons, NULL, sizeof(sons));
        fail = NULL;
    }
    Node(int &number) {
        ++ number;
        id = number;
        value = 0;
        memset(sons, NULL, sizeof(sons));
        fail = NULL;
    }
} *Root;
unordered_map <int, Node*> nodes;
vector <int> level[MAXN];
vector <Node*> Q;

inline void Insert(const string &s, const int &value) {
    Node *n = Root;
    int sz = s.size();
    for(int i = 0 ; i < sz ; ++ i) {
        int son = getCode(s[i]);
        if(!n->sons[son]) {
            n->sons[son] = new Node(nrNodes);
            //level[son].push_back(nrNode);
            nodes[nrNodes] = n->sons[son];
        }
        n = n->sons[son];
    }
    n->value += value;
}

inline void BFs() {
    Q.push_back(Root);
    Node *n, *k;
    Root->fail = Root;
    for(int j = 0 ; j < Q.size() ; ++ j) {
        n = Q[j];
        for(int i = 0 ; i < SIGMA ; ++ i)
            if(n->sons[i]) {
                k = n->fail;
                while(k != Root && !k->sons[i])
                    k = k -> fail;
                if(k->sons[i] && k->sons[i] != n->sons[i])
                    k = k -> sons[i];
                n->sons[i]->fail = k;
                n->sons[i]->value += k->value;
                Q.push_back(n->sons[i]);
            }
    }
}

int dp[MAXN][MAXN * MAXN];
int father[MAXN][MAXN * MAXN];
char ch[MAXN][MAXN * MAXN];

inline void write(int n, int state) {
    if(!n)
        return;
    if(father[n][state])
        write(n - 1, father[n][state]);
    fout << ch[n][state];
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    Root = new Node(nrNodes);
    nodes[nrNodes] = Root;
    int N, M;
    fin >> N >> M;
    for(int i = 0 ; i < M ; ++ i) {
        string s;
        int value;
        fin >> s >> value;
        Insert(s, value);
    }
    BFs();
    memset(dp, -1, sizeof(dp));
    dp[0][1] = 0;
    for(int i = 0 ; i < N ; ++ i) {
        for(int j = Q.size() - 1 ; j >= 0 ; -- j) {
            Node *act = Q[j], *now;
            if(dp[i][act->id] == -1)
                continue;
            for(int son = 0 ; son < SIGMA ; ++ son) {
                if(act->sons[son]) {
                    now = act->sons[son];
                    if(dp[i + 1][now->id] < dp[i][act->id] + now ->value) {
                        dp[i + 1][now->id] = dp[i][act->id] + now ->value;
                        father[i + 1][now->id] = act->id;
                        char s = son + 'a';
                        ch[i + 1][now->id] = s;
                    }
                }
                else {
                    now = act->fail;
                    while(now != Root && !now->sons[son])
                        now = now -> fail;
                    if(now->sons[son])
                        now = now->sons[son];
                    if(dp[i + 1][now->id] < dp[i][act->id] + now->value) {
                        dp[i + 1][now->id] = dp[i][act->id] + now ->value;
                        father[i + 1][now->id] = act->id;
                        char s = son + 'a';
                        ch[i + 1][now->id] = s;
                    }
                }
            }
        }
    }
    int ans = 1;
    for(int i = 1 ; i <= nrNodes ; ++ i) {
        if(dp[N][i] > dp[N][ans]) {
            ans = i;
        }
    }
    fout << dp[N][ans] << "\n";
    write(N, ans);
    fin.close();
    fout.close();
    return 0;
}
