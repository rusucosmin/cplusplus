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

const char infile[] = "ahocorasick.in";
const char outfile[] = "ahocorasick.out";

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

char s[MAXN * 10], p[10005];
int n;

class FiniteAutomation {
private:
    static const int SIGMA = 26;
    static const char startLetter = 'a';
    struct Node {
        vector <Node *> sons;
        vector <int> where;
        Node *fail;
        int matches;
        int endings;
        Node() {
            sons.resize(SIGMA, NULL);
            fail = NULL;
            matches = 0;
            endings = 0;
        }
    } *Root;
    vector <Node *> Q;
    vector <int> Ans;
    void Insert(Node *n, char *s) {
        if(!*s) {
            n->where.push_back(Ans.size());
            Ans.push_back(0);
            return;
        }
        int son = *s - 'a';
        if(n->sons[son] == NULL)
            n->sons[son] = new Node();
        Insert(n->sons[son], s + 1);
    }
    void buildFails() {
        Q.push_back(Root);
        Root->fail = Root;
        Node *K;
        for(int i = 0 ; i < Q.size() ; ++ i) {
            Node *n = Q[i];
            for(int i = 0 ; i < SIGMA ; ++ i)
                if(n->sons[i]) {
                    K = n->fail;
                    while(K != Root && !K->sons[i])
                        K = K->fail;
                    if(K->sons[i] && K->sons[i] != n->sons[i])
                        K = K -> sons[i];
                    n->sons[i]->fail = K;
                    Q.push_back(n->sons[i]);
                }
        }
    }
    void AhoCorasick(char *s) {
        Node *K = Root;
        for(int i = 0 ; s[i] ; ++ i) {
            int son = s[i] - 'a';
            while(K != Root && !K->sons[son])
                K = K->fail;
            if(K->sons[son])
                K = K->sons[son];
            ++ K->matches;
        }
    }
    vector <int> antiBfs() {
        int ret = 0;
        Node *n;
        for(int i = Q.size() - 1 ; i >= 0 ; -- i) {
            n = Q[i];
            if(n->matches)
                n->fail->matches += n->matches;
            for(auto it : n->where)
                Ans[it] = n->matches;
        }
        return Ans;
    }
public:
    FiniteAutomation(){
        Root = new Node();
    }
    void insertString(char *s) {
        Insert(Root, s);
    }
    vector <int> getMatches(char *s) {
        buildFails();
        AhoCorasick(s);
        return antiBfs();
    }
} Trie;

int main() {
    fin >> s >> n;
    for(int i = 0 ; i < n ; ++ i) {
        fin >> p;
        Trie.insertString(p);
    }
    for(auto it : Trie.getMatches(s))
        fout << it << '\n';
    fin.close();
    fout.close();
    return 0;
}
