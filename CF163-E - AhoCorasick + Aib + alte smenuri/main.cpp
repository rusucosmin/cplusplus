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

class aib {
private:
    int n;
    vector <int> arb;
public:
    aib(int N) {
        n = N;
        arb.resize(n + 1, 0);
    }
    inline int lsb(int x) {
        return x & (-x);
    }
    inline void add(int pos, int value) {
        for(int i = pos ; i <= n ; i += lsb(i)) {
            arb[i] += value;
        }
    }
    inline int sum(int pos) {
        int _sm = 0;
        for(int i = pos ; i > 0 ; i -= lsb(i))
            _sm += arb[i];
        return _sm;
    }
};

class FiniteAutomaton {
public:
    static const int SIGMA = 26;
    struct Node {
        vector <Node*> sons;
        vector <Node*> tree;
        Node *fail;
        int is;
        int a, b;
        Node() {
            sons.resize(SIGMA, NULL);
            is = 0;
        }
    };
    FiniteAutomaton() {
        Root = new Node();
        euler = 0;
    }
    inline int getCode(const char &s) {
        return s - 'a';
    }
    inline void addString(Node *n, const string &s, const int &pos, const int &ind) {
        if(s.size() == pos) {
            where.push_back(n);
            return;
        }
        int son = getCode(s[pos]);
        if(!n->sons[son])
            n->sons[son] = new Node();
        addString(n->sons[son], s, pos + 1, ind);
    }
    inline void buildPi() {
        Root->fail = Root;
        queue <Node*>Q;
        Q.push(Root);
        Node *n, *k;
        while(!Q.empty()) {
            n = Q.front();
            Q.pop();
            if(n != Root)
                n->fail->tree.push_back(n);
            for(int i = 0 ; i < SIGMA ; ++ i)
                if(n->sons[i]) {
                    k = n->fail;
                    while(k != Root && !k->sons[i])
                        k = k->fail;
                    if(k->sons[i] && k->sons[i] != n->sons[i])
                        k = k->sons[i];
                    n->sons[i]->fail = k;
                    Q.push(n->sons[i]);
                }
        }
    }
    inline void dfs(Node *n) {
        n->a = ++ euler;
        for(vector <Node*> :: iterator it = n->tree.begin(), fin = n->tree.end(); it != fin ; ++ it)
            dfs(*it);
        n->b = ++ euler;
    }
    inline long long AhoCorasick(const string &s) {
        Node *K = Root;
        long long sum = 0;
        for(int i = 0 ; i < s.size() ; ++ i) {
            int son = getCode(s[i]);
            while(K != Root && !K->sons[son])
                K = K -> fail;
            if(K->sons[son])
                K = K -> sons[son];
            sum += a->sum(K->a);
        }
        return sum;
    }
    inline Node* getRoot() {
        return Root;
    }
    inline void buildAIB() {
        a = new aib(euler);
    }
    inline void Add(Node *x, int value) {
        if(x->is == value)
            return;
        x->is = value;
        a->add(x->a,  value);
        a->add(x->b, -value);
    }
    inline Node *getNode(int ind) {
        return where[ind];
    }
private:
    aib *a;
    Node *Root;
    vector <Node*> where;
    int euler;
} Trie;

int N, M;
string line;


int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> M >> N;
    cin.get();
    for(int i = 0 ; i < N ; ++ i) {
        getline(cin, line);
        Trie.addString(Trie.getRoot(), line, 0, i);
    }
    Trie.buildPi();
    Trie.dfs(Trie.getRoot());
    Trie.buildAIB();
    for(int i = 0 ; i < N ; ++ i)
        Trie.Add(Trie.getNode(i), 1);
    for(int i = 0 ; i < M ; ++ i) {
        char c;
        int x;
        do {
            cin.get(c);
        }while(c == ' ' || c == '\n');
        switch(c) {
            case '+':
                cin >> x;
                //cerr << "+" << x << "\n";
                Trie.Add(Trie.getNode(x-1), 1);
                break;
            case '-':
                cin >> x;
                //cerr << "-" << x << "\n";
                Trie.Add(Trie.getNode(x-1), -1);
                break;
            case '?':
                getline(cin, line);
                //cerr << "?" << line << "\n";
                cout << Trie.AhoCorasick(line) << '\n';
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
