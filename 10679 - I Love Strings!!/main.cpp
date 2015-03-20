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

class FiniteAutomaton {
public:
    struct Node {
        map<char, Node*> sons;
        int matching;
        Node *fail;
        vector <int> where;
        Node() {
            matching = 0;
            fail = NULL;
        }
    };
    FiniteAutomaton() {
        Root = new Node();
    }
    void Insert(Node * n, const string &s, const int &pos, const int &i) {
        if(s.size() == pos) {
            n->where.push_back(i);
            match.push_back(false);
            return;
        }
        if(n->sons[s[pos]] == NULL)
            n->sons[s[pos]] = new Node();
        Insert(n->sons[s[pos]], s, pos + 1, i);
    }
    void BuildPi() {
        Root->fail = Root;
        Node *n, *K;
        Q.push_back(Root);
        for(int i = 0 ; i < Q.size() ; ++ i) {
            n = Q[i];
            for(map<char, Node*> :: iterator it = n->sons.begin(), fin = n->sons.end(); it != fin ; ++ it) {
                K = n->fail;
                while(K != Root && !K->sons[it->first])
                    K = K -> fail;
                if(K->sons[it->first] && K->sons[it->first] != it->second)
                    K = K->sons[it->first];
                it->second->fail = K;
                Q.push_back(it->second);
            }
        }
    }
    inline Node * getRoot() {
        return Root;
    }
    void AhoCorasick(const string &s) {
        Node *K = Root;
        for(int i = 0 ; i < s.size() ; ++ i) {
            while(K != Root && !K->sons[s[i]])
                K = K->fail;
            if(K->sons[s[i]])
                K = K->sons[s[i]];
            K -> matching |= true;
        }
    }
    void antiBFS() {
        for(int i = Q.size() - 1 ; i >= 0 ; -- i) {
            Node *K = Q[i];
            K->fail->matching |= K->matching;
            for(vector <int> :: iterator it = K->where.begin(), fin = K->where.end(); it != fin ; ++ it)
                match[*it] = K->matching;
        }
    }
    vector <bool> getMatches(const string &s) {
        AhoCorasick(s);
        antiBFS();
        return match;
    }
private:
    Node *Root;
    vector <Node*>Q;
    vector <bool> match;
};

string s, p;
int q;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T;
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        FiniteAutomaton Trie;
        cin >> s >> q;
        for(int i = 0 ; i < q ; ++ i) {
            cin >> p;
            Trie.Insert(Trie.getRoot(), p, 0, i);
        }
        Trie.BuildPi();
        vector <bool> ans = Trie.getMatches(s);
        for(auto it:ans)
            if(it)
                cout << "y\n";
            else
                cout << "n\n";
    }
    fin.close();
    fout.close();
    return 0;
}
