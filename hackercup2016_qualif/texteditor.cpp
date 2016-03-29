#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 100005;
const int maxk = 305;
const int sigma = 26;
const int oo = 0x3f3f3f3f;

struct Trie {
    Trie *sons[sigma];
    bool end;
    int dp[maxk];
    Trie() {
        memset(sons, 0, sizeof(sons));
        end = false;
        memset(dp, oo, sizeof(dp));
    }
} *root;

int t, n, k;
char s[maxn];

void _insert(Trie *&node, char *s) {
    if(!*s) {
        node->end = 1;
        return ;
    }
    int son = *s - 'a';
    if(!node->sons[son])
        node->sons[son] = new Trie();
    _insert(node->sons[son], s + 1);
}

void dfs(Trie *&node, char ch) {
    node->dp[0] = 0;
    if(node->end)
        node->dp[1] = 1;
    for(int j = 0 ; j <= k ; ++ j) {
        int sum = 0;
        for(int i = 0 ; i < sigma ; ++ i) {
            if(node->sons[i]) {
                dfs(node->sons[i], i + 'a');
                for(int l = 0 ; l <= k ; ++ l) {
                    node->dp[j] = min(node->dp[j], node->sons[i]->dp[l]);
                }
            }
        }
    }
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    cin >> t;
    for(int test = 1 ; test <= t ; ++ test) {
        root = new Trie();
        cin >> n >> k;
        for(int i = 1 ; i <= n ; ++ i) {
            cin >> s;
            _insert(root, s);
        }
        dfs(root, ' ');
        cout << '\n';
    }
}
