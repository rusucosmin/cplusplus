#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 105;
const int sigma = 26;

struct trie {
    trie *sons[sigma];
    int cnt[2];
    trie () {
        memset(sons, 0, sizeof(sons));
        memset(cnt, 0, sizeof(cnt));
    }
} *root;

int n;
char s[maxn];

inline void insert(trie *node, char *s, int where) {
    ++ node->cnt[where];
    if(!*s)
        return ;
    int son = *s - 'A';
    if(!node->sons[son])
        node->sons[son] = new trie();
    insert(node->sons[son], s + 1, where);
}

inline int dfs(trie *node) {
    if(!node)
        return 0;
    int sum = min(node->cnt[0], node->cnt[1]);
    for(int i = 0 ; i < sigma ; ++ i)
        if(node->sons[i])
            sum += dfs(node->sons[i]);
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE

    while(cin >> n) {
        if(n == -1)
            return 0;
        root = new trie();
        for(int i = 0 ; i < n ; ++ i) {
            cin >> s;
            insert(root, s, 0);
        }
        for(int i = 0 ; i < n ; ++ i) {
            cin >> s;
            insert(root, s, 1);
        }
        cout << dfs(root) - min(root->cnt[0], root->cnt[1]) << '\n';
    }
}
