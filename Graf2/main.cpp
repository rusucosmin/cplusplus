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
#include <stack>

using namespace std;

const char infile[] = "graf2.in";
const char outfile[] = "graf2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 605;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bitset <MAXN> g[MAXN], gt[MAXN], dag[MAXN], used, road[MAXN];
int N, M, where[MAXN], ctc, answer, pos[MAXN], act;
vector <int> ts;
stack <int> st;

void dfs(int node) {
    used[node] = 1;
    for(int i = 1 ; i <= N ; ++ i)
        if(!used[i] && g[node][i])
            dfs(i);
    st.push(node);
}

void dfsrev(int node) {
    used[node] = 1;
    for(int i = 1 ; i <= N ; ++ i)
        if(!used[i] && gt[node][i])
            dfsrev(i);
    where[node] = ctc;
    ++ act;
}

void tsort(int node) {
    used[node] = 1;
    for(int i = 1 ; i <= ctc ; ++ i)
        if(!used[i] && dag[node][i])
            tsort(i);
    ts.push_back(node);
    pos[node] = ts.size();
}

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return pos[a] > pos[b];
    }
};

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x][y] = 1;
        gt[y][x] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!used[i])
            dfs(i);

    used.reset();

    for( ; !st.empty() ; st.pop()) {
        int node = st.top();
        if(!used[node]) {
            ++ ctc;
            act = 0;
            dfsrev(node);
            if(act > 1)
                answer += act;
        }
    }

    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(g[i][j] && where[i] != where[j])
                dag[where[i]][where[j]] = 1;


    used.reset();
    for(int i = 1 ; i <= ctc ; ++ i)
        if(!used[i])
            tsort(i);

    for(auto i: ts) {
        vector <int> aux;
        for(int j = 1 ; j <= ctc ; ++ j)
            if(dag[i][j])
                aux.push_back(j);
        sort(aux.begin(), aux.end(), classComp());
        for(It it = aux.begin(), fin = aux.end() ; it != fin ; ++ it) {
            if(!road[i][*it]) {
                road[i][*it] = 1;
                ++ answer;
            }
            road[i] = (road[i] | road[*it]);
        }
    }
    fout << answer << '\n';
    fin.close();
    fout.close();
    return 0;
}
