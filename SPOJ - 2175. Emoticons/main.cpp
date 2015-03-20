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

vector <string> Emoticons;

class FiniteAutomaton {
private:
    struct Node {
        map<char, Node*> sons;
        int index;
        Node *fail;
        Node() {
            index = -1;
            fail = NULL;
        }
    };
    Node *Root;
    void _insert(Node *n, const string &s, const int &pos, const int &ind) {
        if(s.size() == pos) {
            n->index = ind;
            return;
        }
        if(n->sons[s[pos]] == NULL)
            n->sons[s[pos]] = new Node();
        _insert(n->sons[s[pos]], s, pos + 1, ind);
    }
    void BFs(Node *Root) {
        Root->fail = Root;
        Node *K = Root;
        queue <Node*> Q;
        Q.push(Root);
        while(!Q.empty()) {
            Node *n = Q.front();
            Q.pop();
            for(map<char, Node*> :: iterator it = n->sons.begin(), fin = n->sons.end(); it != fin ; ++ it) {
                K = n->fail;
                while(K != Root && !K->sons[it->first])
                    K = K -> fail;
                if(K->sons[it->first] && K -> sons[it->first] != it->second)
                    K = K -> sons[it->first];
                it->second->fail = K;
                Q.push(it->second);
            }
        }
    }
public:
    FiniteAutomaton() {
        Root = new Node();
    }
    void insert(string s, int index) {
        _insert(Root, s, 0, index);
    }
    void buildFails() {
        BFs(Root);
    }
    vector <pair<int, int> >  getMatches(const string &s) {
        Node *K = Root;
        vector <pair<int, int> > ans;
        for(int i = 0 ; i < s.size() ; ++ i) {
            while(K != Root && !K -> sons[s[i]])
                K = K -> fail;
            if(K->sons[s[i]])
                K = K->sons[s[i]];
            if(K->index != -1)
                ans.push_back(make_pair(K->index, i));
        }
        return ans;
    }
};

string s;

void simplifyKeywords(vector <string> &keywords) {
    int K = keywords.size();
    // Remove duplicate keywords
    sort(keywords.begin(), keywords.end());
    keywords.resize(unique(keywords.begin(), keywords.end()) - keywords.begin());

    K = keywords.size();
    vector<bool> rm(K, false);
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            if (i == j) continue;
            if (keywords[i].find(keywords[j]) != string::npos) {
                // keywords[j] is a substring of keywords[i], delete i
                rm[i] = true;
            }
        }
    }

    vector<string> newKeywords;
    for (int i = 0; i < K; ++i) {
        if (!rm[i]) newKeywords.push_back(keywords[i]);
    }
    keywords = newKeywords;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int N, M;
    while(cin >> N >> M) {
        if(N == 0 && M == 0)
            break;
        FiniteAutomaton Trie;
        cin.get();
        for(int i = 0 ; i < N ; ++ i) {
            getline(cin, s);
            Emoticons.push_back(s);
        }
        //sort(Emoticons.begin(), Emoticons.end());
        //Emoticons.resize(unique(Emoticons.begin(), Emoticons.end()) - Emoticons.begin());
        simplifyKeywords(Emoticons);
        for(int i = 0 ; i < Emoticons.size() ; ++ i)
            Trie.insert(Emoticons[i], i);
        Trie.buildFails();
        int ans = 0;
        for(int j = 0 ; j < M ; ++ j) {
            getline(cin, s);
            vector <pair<int, int> > intervals = Trie.getMatches(s);
            int last = -1;
            for(int i = 0 ; i < intervals.size() ; ++ i) {
                int u = intervals[i].second - Emoticons[intervals[i].first].size() + 1, v = intervals[i].second;
                if(last < u) {
                    last = v;
                    ++ ans;
                }
            }
        }
        cout << ans << '\n';
        vector <string>().swap(Emoticons);
    }
    fin.close();
    fout.close();
    return 0;
}
