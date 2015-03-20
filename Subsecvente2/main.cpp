#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("subsecvente2.in");
ofstream fout("subsecvente2.out");

const int maxn = 50005;
const int sigma = 2;

struct node {
    int cnt;
    node *sons[sigma];
    node () {
        memset(sons, 0, sizeof(sons));
        cnt = 0;
    }
} *root = new node();

int n;
char s[maxn];

inline void insert(node *root, char *s, int index, int level) {
    if(root->cnt < index - 1 || level >= 61)
        return ;
    root->cnt = index;
    if(!*s)
        return ;
    int son = *s - 'a';
    if(!root->sons[son])
        root->sons[son] = new node();
    insert(root->sons[son], s + 1, index, level + 1);
}

inline int dfs(node *root) {
    int ret = 0;
    if(root->sons[0] && root->sons[0]->cnt == n)
        ret = 1 + dfs(root->sons[0]);
    if(root->sons[1] && root->sons[1]->cnt == n)
        ret = max(ret, 1 + dfs(root->sons[1]));
    return ret;
}

int main() {
    fin >> n;
    fin.get();
    for(int i = 1 ; i <= n ; ++ i) {
        fin.getline(s, maxn);
        for(int j = 0 ; s[j] ; ++ j)
            insert(root, s + j, i, 0);
    }
    fout << dfs(root) << '\n';
}
