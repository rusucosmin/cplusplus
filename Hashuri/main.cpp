#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("hashuri.in");
ofstream fout("hashuri.out");

const int mod = 666013;

vector <int> g[mod];

inline bool _find(int value) {
    int key = value % mod;
    for(auto it : g[key])
        if(it == value)
            return 1;
    return 0;
}

inline void _erase(int value) {
    int key = value % mod;
    for(vector <int> :: iterator it = g[key].begin() ; it != g[key].end() ; ++ it)
        if(*it == value) {
            g[key].erase(it);
            return ;
        }
}

inline void _insert(int value) {
    if(_find(value))
        return ;
    int key = value % mod;
    g[key].push_back(value);
}


int main() {
    int n;
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        int op, x;
        fin >> op >> x;
        if(op == 1)
            _insert(x);
        if(op == 2)
            _erase(x);
        if(op == 3)
            fout << _find(x) << '\n';
    }
}
