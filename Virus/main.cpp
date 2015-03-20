#include <fstream>
#include <memory.h>
#include <vector>
#include <list>

using namespace std;

const int MAXL = 100005;
const int MAXN = 1005;
const int MAXK = 1005;

const int SIGMA = 2;
int L, p, u;
short N, K;
int Ans[MAXN];
char word[MAXL], s[MAXN];

struct Trie {
    Trie *sons[SIGMA];
    Trie *fail;
    int matches;
    list<short> l;
    Trie() {
        matches = 0;
        l.clear();
        fail = 0;
        memset(sons, 0, sizeof(sons));
    }
};

Trie *Root = new Trie();
Trie *Q[MAXN * MAXK];

ifstream fin("virus.in");
ofstream fout("virus.out");

void Insert(Trie * Node, char *p, const short &ind) {
    if(!*p) {
        Node -> l.push_back(ind);
        return;
    }
    bool actSon = (*p - '0');
    if(!Node -> sons[actSon])
        Node -> sons[actSon] = new Trie();
    Insert(Node -> sons[actSon], p + 1, ind);
}

inline void BFs(Trie * stNode) {
    Trie *tmp;
    stNode -> fail = stNode;
    for(Q[p = u = 1] = stNode ; p <= u ; ++ p) {
        Trie *Node = Q[p];
        for(int i = 0 ; i < SIGMA ; ++ i)
            if(Node -> sons[i]) {
                for(tmp = Node -> fail ; tmp != stNode && (!tmp -> sons[i]) ; tmp = tmp -> fail);

                if(tmp -> sons[i] && tmp -> sons[i] != Node -> sons[i])
                    tmp = tmp->sons[i];

                Node -> sons[i] -> fail = tmp;
                Q[++u] = Node -> sons[i];
            }
    }
    stNode -> fail = 0;
}

inline void revBFs(Trie *stNode) {
    for(int i = u ; i ; -- i) {
        Trie *Node = Q[i];

        if(Node -> fail)
            Node -> fail -> matches += Node -> matches;

        for(list<short> :: iterator it = Node ->l.begin(), fin = Node -> l.end(); it != fin ; ++ it)
            Ans[*it] = Node -> matches;
    }
}

int main() {
    fin >> L >> N;
    fin.get();
    fin.getline(word, MAXL);
    for(short i = 0 ; i < N ; ++ i) {
        fin >> K;
        fin.get();
        fin.getline(s, MAXK);
        Insert(Root, s, i);
    }
    BFs(Root);
    Trie *P = Root;
    for(int i = 0 ; i < L ; ++ i) {
        bool next = word[i] - '0';

        for( ; (!P -> sons[next] && P != Root ; P = P -> fail);

        if(P -> sons[next])
            P = P -> sons[next];

        ++ P -> matches;
    }
    revBFs(Root);
    for(short i = 0 ; i < N ; ++ i)
        fout << Ans[i] << '\n';
    return 0;
}
