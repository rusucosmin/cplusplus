#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "casute.in";
const char outfile[] = "casute.out";

ofstream fout(outfile);

const int MAXN = 3005;
const int MOD = 666013;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, H[MAXN], L[MAXN];
Graph G, Gt;
bitset <MAXN> Used;
queue <int> Qu;

struct classComp {
    inline bool operator () (const int &a, const int &b) {
        return H[a] > H[b];
    }
};

priority_queue<int, vector <int> , classComp> Q;

FILE* fin=fopen("casute.in","r");
const unsigned maxb=MAXN & 10;
char buf[maxb];
unsigned ptr=maxb;

inline unsigned getInt() {
    unsigned nr=0;
    while(buf[ptr]<'0'||'9'<buf[ptr])
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    while('0'<=buf[ptr]&&buf[ptr]<='9') {
        nr=nr*10+buf[ptr]-'0';
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    return nr;
}

inline void BFs(const int &startNode) {
    for(Qu.push(startNode); !Qu.empty() ; Qu.pop()) {
        int Node = Qu.front();
        L[Node] = startNode;
        for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
            if(!Used[*it]) {
                Used[*it] = true;
                Qu.push(*it);
            }
    }
}

int main() {
    N = getInt();  M = getInt();
    for(int i = 1 ; i <= N ; ++ i)
        H[i] = getInt();
    for(int i = 1 ; i <= M ; ++ i) {
        int x = getInt(), y = getInt();
        G[x].push_back(y);
        Gt[y].push_back(x);
    }
    int tenBasePower = 1, Ans = 0;
    for(int i = N - 1 ; i ; -- i) {
        Used.reset();
        memset(L, 0, sizeof(L));
        Used[i] = true;
        for(Q.push(i) ; !Q.empty() ; Q.pop()) {
            int Node = Q.top();
            BFs(Node);
            for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
                if(!Used[*it]) {
                    Used[*it] = true;
                    Q.push(*it);
                }
        }
        for(int j = N ; j > i ; -- j) {
            Ans = (Ans + tenBasePower * L[j]) % MOD;
            tenBasePower = (tenBasePower * (N + 1)) % MOD;
        }
    }
    fout << Ans << '\n';
    fout.close();
    return 0;
}
