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
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int SIGMA = 26;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
char s[25];
unordered_map<int, string> dic;

struct Trie {
    Trie *sons[SIGMA];
    int _end;
    Trie() {
        memset(sons, 0, sizeof(sons));
        _end = -1;
    }
};

Trie *Root = new Trie();

inline void Insert(Trie *Node, char *s, int ind) {
    if(!*s) {
        if(Node -> _end == -1)
            Node->_end = ind;
        return;
    }
    int son = *s - 'a';
    if(Node->sons[son] == 0)
        Node->sons[son] = new Trie();
    Insert(Node->sons[son], s + 1, ind);
}

inline void DFs(Trie *Node) {
    if(Node -> _end != -1)
        cout << dic[Node->_end] << '\n';
    for(int i = 0 ; i < SIGMA ; ++ i)
        if(Node->sons[i])
            DFs(Node->sons[i]);
}

inline bool Query(Trie *Node, char *s) {
    if(!*s) {
        bool ret = false;
        for(int i = 0 ; i < SIGMA ; ++ i)
            if(Node -> sons[i])
                DFs(Node->sons[i]), ret = true;
        return ret;
    }
    int son = *s - 'a';
    if(Node->sons[son] == 0)
        return false;
    return Query(Node->sons[son], s + 1);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> s;
        dic[i] = s;
        Insert(Root, s, i);
    }
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> s;
        cout << "Case #" << i << ":\n";
        bool ok = Query(Root, s);
        if(!ok)
            cout << "No match.\n";
    }
    fin.close();
    fout.close();
    return 0;
}
