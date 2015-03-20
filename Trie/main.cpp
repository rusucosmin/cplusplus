#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

ifstream fin("trie.in");
ofstream fout("trie.out");

const int sigma = 26;

int op, n;
char s[30];

struct trie {
    trie *sons[sigma];
    int cnt, cntsons;
    trie (){
        memset(sons, 0, sizeof(sons));
        cnt = cntsons = 0;
    }
} *root = new trie();

inline void _insert(trie *node, char *s) {
    if(!*s) {
        ++ node->cnt;
        return ;
    }
    int son = *s - 'a';
    if(!node->sons[son]) {
        ++ node->cntsons;
        node->sons[son] = new trie();
    }
    _insert(node->sons[son], s + 1);
}

inline bool _erase(trie *&node, char *s) {
    if(!*s) {
        -- node->cnt;
        if(node->cnt == 0 && node->cntsons == 0 && node != root) {
            delete node;
            node = NULL;
            return 1;
        }
        return 0;
    }
    int son = *s - 'a';
    if(!node->sons[son])
        return 0;
    if(_erase(node->sons[son], s + 1)) {
        -- node->cntsons;
        if(node->cnt == 0 && node->cntsons == 0 && root != node) {
            delete node;
            node = NULL;
            return 1;
        }
    }
    return 0;
}

inline int _find(trie *node, char *s) {
    if(!*s)
        return node->cnt;
    int son = *s - 'a';
    if(!node->sons[son])
        return 0;
    return _find(node->sons[son], s + 1);
}

inline int _prefix(trie *node, char *s) {
    if(!*s)
        return 0;
    int son = *s - 'a';
    if(node->sons[son])
        return 1 + _prefix(node->sons[son], s + 1);
    return 0;
}

int main() {
    while(fin >> op >> s) {
        //if(!root)
        //    root = new trie();
        switch(op) {
            case 0:
                _insert(root, s);
                break;
            case 1:
                _erase(root, s);
                break;
            case 2:
                fout << _find(root, s) << '\n';
                break;
            case 3:
                fout << _prefix(root, s) << '\n';
                break;
        }
    }
}
