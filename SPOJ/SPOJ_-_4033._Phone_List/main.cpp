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
const int SIGMA = 10;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Trie {
    Trie *sons[SIGMA];
    int _end;
    Trie() {
        memset(sons, 0, sizeof(sons));
        _end = false;
    }
};

bool Insert(Trie *Node, const int pos, const string s) {
    if(pos == s.size()) {
        ++ Node -> _end;
        return true;
    }
    int son = s[pos] - '0';
    if(!Node -> sons[son])
        Node -> sons[son] = new Trie();
    else if(Node -> sons[son] -> _end != 0)
        return false;
    return Insert(Node -> sons[son], pos + 1, s);
}

int N, T;
char s[25];
Trie *Root = new Trie();

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d", &N);
        Root = new Trie();
        bool ok = true;
        vector <string> V;
        for(int i = 1 ; i <= N ; ++ i) {
            scanf("%s", &s);
            V.push_back(s);
        }
        sort(V.begin(), V.end());
        for(int i = 0 ; i < N ; ++ i)
            if(!Insert(Root, 0, V[i])) {
                ok = false;
                break;
            }
        if(ok)
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
