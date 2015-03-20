#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 27;

char s[maxn];
int in[maxn];
vector <int> g[maxn];
priority_queue <int, vector <int>, greater <int> > q;

int main() {
    ifstream fin("relatii.in");
    ofstream fout("relatii.out");
    int n, m;
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        char a, b, c;
        fin >> a >> b >> c;

        if(b == '>')
            swap(a, c);
        g[a - 'a'].push_back(c - 'a');
        ++ in[c - 'a'];
        n = max(n, max(a - 'a', c - 'a'));/**/
    }
    for(int i = 0 ; i < n ; ++ i)
        if(!in[i])
            q.push(i);
    while(!q.empty()) {
        int node = q.top();
        fout << (char)(node + 'a');
        q.pop();
        for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
            if(-- in[*it] == 0)
                q.push(*it);
        }
    }
}
