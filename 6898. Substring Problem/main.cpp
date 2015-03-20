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
        Node *fail;
        bool match;
        vector <int> where;
        Node() {
            match = false;
            fail = NULL;
        }
    };
    FiniteAutomaton() {
        Root = new Node();
    }
    void insertString(const string &s, const int &position) {
        _insert(Root, s, 0, position);
    }
    void buildFails() {
        BFs();
    }
    vector <bool> getMatches(const string &s) {
        AhoCorasick(s);
        antiBFs();
        return ans;
    }
private:
    void AhoCorasick(const string &s) {
        Node *K = Root;
        for(int i = 0 ; i < s.size() ; ++ i) {
            while(K != Root && !K->sons[s[i]])
                K = K ->fail;
            if(K->sons[s[i]])
                K = K ->sons[s[i]];
            K->match |= true;
        }
    }
    void antiBFs() {
        Node *n;
        for(int i = Q.size() - 1 ; i >= 0 ; -- i) {
            n = Q[i];
            n->fail->match |= n->match;
            for(vector<int> :: iterator it = n->where.begin() ; it != n->where.end(); ++ it)
                ans[*it] = n->match;
        }
    }
    void _insert(Node *n, const string &s, const int &pos, const int &i) {
        if(s.size() == pos) {
            n->where.push_back(i);
            ans.push_back(false);
            return;
        }
        if(!n->sons[s[pos]])
            n->sons[s[pos]] = new Node();
        _insert(n->sons[s[pos]], s, pos + 1, i);
    }
    void BFs() {
        Node *n, *K;
        Root->fail = Root;
        Q.push_back(Root);
        for(int i = 0 ; i < Q.size() ; ++ i) {
            n = Q[i];
            for(map<char, Node*> :: iterator it = n->sons.begin(); it != n -> sons.end(); ++ it) {
                K = n->fail;
                while(K != Root && !K->sons[it->first])
                    K = K->fail;
                if(K->sons[it->first] && K->sons[it->first] != it->second)
                    K = K->sons[it->first];
                it->second->fail = K;
                Q.push_back(it->second);
            }
        }
    }
    vector <bool> ans;
    vector <Node *> Q;
    Node *Root;
} Trie;

string s, p;
int M;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> s;
    cin >> M;
    for(int i = 0 ; i < M ; ++ i) {
        cin >> p;
        Trie.insertString(p, i);
    }
    Trie.buildFails();
    vector <bool> ans = Trie.getMatches(s);
    for(vector<bool> :: iterator it = ans.begin(), fin = ans.end(); it != fin ; ++ it)
        if(*it)
            cout << "Y\n";
        else cout << "N\n";
    fin.close();
    fout.close();
    return 0;
}
