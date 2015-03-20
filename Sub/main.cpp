#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "sub.in";
const char outfile[] = "sub.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Trie {
    int vis;
    Trie *next[27];
    bool mark;
    Trie() {
        vis = 0;
        mark = 0;
        memset(next, 0, sizeof(next));
    }
};

int N, M;
bool canerase;
char s[3*MAXN];
Trie *root = new Trie;

void Insert(Trie *Node, const int &pos, const int &n, const int &i) {
    if(Node -> vis == i - 1)
        ++ Node -> vis;
    if(pos >= n || Node -> vis < i - 1)
        return;
    if(!Node -> next[s[pos] - 'a'])
        Node -> next[s[pos] - 'a'] = new Trie;
    Insert( Node -> next[s[pos] - 'a'] , pos + 1, n, i);
}

void Erase(Trie *Node, const int &pos, const int &n, const int &i) {
    if(pos >= n || !Node -> next[s[pos] - 'a'] || Node -> vis < N)
        return ;
    Node -> next[s[pos] - 'a'] -> mark = 1;
    Erase(Node -> next[s[pos] - 'a'] , pos + 1, n, i);
}

int DFs(Trie *Node, char ch = 'R') {
    if(Node -> vis < N)
        return 0;
    int ret = 0;
    //cout << ch << '\n';
    for(char it = 'a' ; it <= 'z' ; ++ it)
        if(Node -> next[it-'a'])
            ret += DFs(Node -> next[it-'a'], it);
    if(!Node -> mark)
        ++ ret;
    return ret;
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> s;
        int aux = strlen(s);
        for(int j = 0 ; j < aux ; ++ j)
            Insert(root, j, aux, i);
    }
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> s;
        int aux = strlen(s);
        for(int j = 0 ; j < aux ; ++ j)
            Erase(root, j, aux, i);
    }
    //cout << root -> vis << '\n';
    root -> mark = 1;
    cout << DFs(root) << '\n';
    cin.close();
    cout.close();
    return 0;
}
