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
#include <cassert>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int SIGMA = 36;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Trie {
    Trie *sons[SIGMA];
    int cnt;
    set<string> words;
    Trie() {
        memset(sons, 0, sizeof(sons));
        cnt = 0;
    }
};

Trie *Root = new Trie();

inline void Insert(Trie *Node, string s) {
    ++ Node->cnt;
    if(s.size() == 0)
        return;
    int son = s[s.size() - 1] - 'a';
    if(Node->sons[son] == 0)
        Node->sons[son] = new Trie();
    Node->words.insert(s);
    Insert(Node->sons[son], s.substr(0, s.size() - 1));
}

inline string Query(Trie *Node, string a) {
    if(Node -> cnt == 0)
        return "";
    int son = a[a.size() - 1] - 'a';
    string ret = "" + char(son + 'a');
    if(!Node->sons[son])
        return ret;
    if(Node->sons[son]->cnt > 1)
        return Query(Node->sons[son], a.substr(0, a.size() - 1)) + char(son + 'a');
    set<string> :: iterator it = Node->words.begin();
    string tmp = *it;
    if(tmp == a) {
        ++ it;
        tmp = *it;
    }
    return tmp;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    string s;
    int N;
    while(getline(cin, s) && s != "") {
        Insert(Root, s);
    }
    while(getline(cin, s) && s != "") {
        cout << Query(Root, s) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
