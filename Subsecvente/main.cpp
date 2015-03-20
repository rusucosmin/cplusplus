#include <stdio.h>
#include <memory.h>
#include <fstream>

using namespace std;

const char infile[] = "subsecvente.in";
const char outfile[] = "subsecvente.out";

const int MAXN = 50005;
const int SIGMA = 2;
const int oo = 0x3f3f3f3f;

char s[MAXN];

struct Trie {
    int best;
    Trie *sons[SIGMA];
    Trie() {
        best = 0;
        memset(sons, 0, sizeof(sons));
    }
};
Trie *Root = new Trie();

void Insert(Trie *Node, const char *p, const int &last, const int &j) {
    if(Node -> best == last)
        ++ Node -> best;
    if(!*p || Node -> best < last || p - (s + j) >= 61)
        return;
    int son = *p - 'a';
    if(!Node -> sons[son])
        Node -> sons[son] = new Trie();
    Insert(Node -> sons[son], p + 1, last, j);
}

int Query(Trie *Node, const int &M) {
    if(Node -> best != M)
        return 0;
    int retMax = 0;
    for(int i = 0 ; i < SIGMA ; ++ i)
        if(Node -> sons[i])
            retMax = max(retMax, Query(Node -> sons[i], M));
    return retMax + 1;
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    int M;
    scanf("%d", &M);
    for(int i = 1 ; i <= M ; ++ i) {
        scanf("%s", s);
        //fin.getline(s, MAXN);
        int lg = strlen(s);
        for(int j = 0 ; j < lg ; ++ j)
            Insert(Root, s + j, i - 1, j);
    }
    Root -> best = M;
    printf("%d\n", Query(Root, M) - 1);
    return 0;
}
