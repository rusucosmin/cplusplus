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

const char infile[] = "adn2.in";
const char outfile[] = "adn2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 300;
const int oo = 0x3f3f3f3f;
const int SIGMA = 4;
const int MAXM = 8;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }


struct Node {
    Node *sons[SIGMA], *fail;
    int id, setmask;
    Node() {
        memset(sons, 0, sizeof(sons));
    }
    Node(int &nrnodes) {
        ++ nrnodes;
        setmask = 0;
        id = nrnodes;
        memset(sons, NULL, sizeof(sons));
        fail = NULL;
    }
} *root;

inline int getSon(const char &s) {
    if(s == 'A')
        return 0;
    if(s == 'G')
        return 1;
    if(s == 'C')
        return 2;
    if(s == 'T')
        return 3;
    assert(false);
}

vector <Node*> Q;
int T, N, M, nrnodes;

inline void Insert(const string &s, const int &mask) {
    Node *n = root;
    for(int i = 0 ; i < s.size() ; ++ i) {
        int son = getSon(s[i]);
        if(!n->sons[son])
            n->sons[son] = new Node(nrnodes);
        n = n -> sons[son];
    }
    n->setmask |= mask;
}

inline void BFs() {
    Q.push_back(root);
    root->fail = root;
    Node *n, *k;
    for(int j = 0 ; j < Q.size() ; ++ j) {
        n = Q[j];
        for(int son = 0 ; son < SIGMA; ++ son) {
            if(n->sons[son]) {
                k = n -> fail;
                while(k != root && !k->sons[son])
                    k = k->fail;
                if(k->sons[son] && k->sons[son] != n ->sons[son])
                    k = k ->sons[son];
                n->sons[son]->fail = k;
                n->sons[son]->setmask |= k->setmask;
                Q.push_back(n->sons[son]);
            }
        }
    }
}

int dp[2][MAXM*21][1 << MAXM];
const int MOD = 666013;

inline void release(Node *&aux) {
    for(int i = 0 ; i < SIGMA ; ++ i)
        if(aux->sons[i])
            release(aux->sons[i]);
    delete aux;
}

string s;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N >> M;
        root = new Node(nrnodes);
        for(int i = 0; i < M ; ++ i) {
            fin >> s;
            Insert(s, 1 << i);
        }
        BFs();
        dp[0][1][0] = 1;
        assert(nrnodes < MAXM * 21);
        for(int i = 0 ; i < N ; ++ i) {
            memset(dp[(i & 1) ^ 1], 0, sizeof(dp[(i & 1) ^ 1]));
            for(int j = Q.size() - 1; j >= 0 ; -- j)
                for(int k = 0 ; k < (1 << M) ; ++ k) {
                    Node *act = Q[j], *now;
                    for(int son = 0 ; son < 4 ; ++ son) {
                        if(act->sons[son]) {
                            now = act->sons[son];
                            dp[(i & 1) ^ 1][now->id][(k|now->setmask)] = (dp[(i & 1) ^ 1][now->id][(k|now->setmask)] + dp[(i & 1)][act->id][k]) % MOD;
                            continue;
                        }
                        now = act->fail;
                        while(now != root && !now->sons[son])
                            now = now->fail;
                        if(now->sons[son])
                            now = now->sons[son];
                        dp[(i & 1) ^ 1][now->id][(k|now->setmask)] = (dp[(i & 1) ^ 1][now->id][(k|now->setmask)] + dp[(i & 1)][act->id][k]) % MOD;
                    }
            }
        }
        int ans = 0;
        for(int i = 1 ; i <= nrnodes ; ++ i)
            ans = (ans + dp[N & 1][i][(1 << M) - 1]) % MOD;
        fout << ans << '\n';
        vector <Node*>().swap(Q);
        nrnodes = 0;
        memset(dp, 0, sizeof(dp));
    }
    fin.close();
    fout.close();
    return 0;
}
