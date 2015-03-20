#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "rk.in";
const char outfile[] = "rk.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int MAXK = 32;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Trie {
    int dp;
    Trie * son[2];
    Trie() {
        dp = 0;
        memset(son, 0, sizeof(son));
    }
};

int N, k;
Trie * Root = new Trie;

void Insert(Trie * Node, const int &x, const int &K) {
    ++ Node->dp;
    if(K > MAXK)
        return;
    bool actSon = x & (1LL << K);
    if(!Node -> son[actSon])
        Node -> son[actSon] = new Trie;
    Insert(Node -> son[actSon], x, K + 1);
}

int Query(Trie *Node, const int &x, const int &K) {
    if(K == k)
        return Node -> dp;
    bool actSon = x & (1LL << K);
    if(!Node -> son[actSon])
        return 0;
    return Query(Node->son[actSon], x, K + 1);
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        Insert(Root, x, 0);
    }
    int M;
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int r;
        fin >> r >> k;
        fout << Query(Root, r, 0) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
