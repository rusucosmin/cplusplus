#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> :: iterator It;

int T, N, M, cuplaj[MAXN], pereche[MAXN], A[MAXN], B[MAXN];
bitset <MAXN> Used;
vector <int> G[MAXN];

#define fin cin
#define fout cout

bool pairUp(const int &Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!pereche[*it] || pairUp(pereche[*it])) {
            pereche[*it] = Node;
            cuplaj[Node] = *it;
            return true;
        }
    return false;
}

int maximumMatching() {
    memset(cuplaj, 0, sizeof(cuplaj));
    memset(pereche, 0, sizeof(pereche));
    int Ans = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= N ; ++ i)
            if(!cuplaj[i])
                if(pairUp(i)) {
                    change = true;
                    ++ Ans;
                }
    }
    return Ans;
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N;
        for(int i = 1 ; i <= N ; ++ i)
            fin >> A[i];
        fin >> M;
        for(int j = 1 ; j <= M ; ++ j)
            fin >> B[j];
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j)
                if(A[i] == 0) {
                    if(B[j] == 0) {
                        G[i].push_back(j);
                    }
                }
                else if(B[j] % A[i] == 0)
                    G[i].push_back(j);
        //int Ans = 0;
        int Ans = maximumMatching();
        fout << "Case " << test << ": " << Ans << '\n';
        for(int i = 1 ; i <= N ; ++ i)
            G[i].clear();
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
    }
    return 0;
}
