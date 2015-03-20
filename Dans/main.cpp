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
#include <stack>

using namespace std;

const char infile[] = "dans.in";
const char outfile[] = "dans.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int t, n, m;

class graph {
public:
    graph() {
    }
    void build(int N) {
        vector <vector <int> > ().swap(g);
        g.resize(N);
        this->n = N;
    }
    void addEdge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    bool checkEulerProperty() {
        int nb = 0;
        for(int i = 0 ; i < n - 1 ; ++ i) {
            nb += (g[i].size() & 1);
            if(g[i].size() & 1)
                addEdge(n - 1, i);
        }
        if(nb == 2)
            return true;
        else
            return false;
    }
    vector <int> getEulerianCycle(int stNode) {
        stack <int> st;
        vector <int> cycle;
        st.push(stNode);
        while(!st.empty()) {
            int node = st.top();
            if(!g[node].empty()) {
                int newnode = g[node].back();
                g[node].pop_back();
                g[newnode].erase(find(g[newnode].begin(), g[newnode].end(),(node)));
                st.push(newnode);
            }
            else {
                st.pop();
                if(st.size())
                    cycle.push_back(node);
            }
        }
        return cycle;
    }
private:
    vector <vector <int> > g;
    int n;
} g;

const int lim = (1 << 20);
char buff[lim];
int pos;

inline int getInt(int &x) {
    x = 0;
    while(!isdigit(buff[pos]))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }

}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    getInt(t);
    while(t --) {
        getInt(n);
        getInt(m);
        g.build(n + 1);
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            getInt(x);
            getInt(y);
            --x; -- y;
            g.addEdge(x, y);
        }
        if(g.checkEulerProperty() == false) {
            fout << "NU\n";
            continue;
        }
        vector <int> cycle = g.getEulerianCycle(n);
        cycle.erase(cycle.begin());
        fout << "DA\n";
        for(auto it : cycle)
            fout << it + 1 << ' ';
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
