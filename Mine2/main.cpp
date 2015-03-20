#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "mine";

//ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.second > b.second;
    }
};

priority_queue <pair<int, int> , vector < pair<int, int> > , ClassComp > H;
bitset<MAXN> Vis;
Graph G;
int Ans;
int N, M, W;
vector<int> V;

#define DIM 10000
char buff[DIM];
int poz=0;

int parse()
{
     int numar = 0;
     //cat timp caracterul din buffer nu e cifra ignor
     while (buff[poz] < '0' || buff[poz] > '9')
          //daca am "golit" bufferul atunci il umplu
          if (++poz == DIM)
               fread(buff,1,DIM,stdin),poz=0;
     //cat timp dau de o cifra recalculez numarul
     while ('0'<=buff[poz] && buff[poz]<='9')
     {
          numar = numar*10 + buff[poz] - '0';
          if (++poz == DIM)
               fread(buff,1,DIM,stdin),poz=0;
     }
     return numar;
}

int main() {
    freopen("mine.in", "r", stdin);
    N = (parse());
    M = (parse());
    for(int i = 1 ; i <= M ; ++ i) {
        int x(parse()), y(parse()), z(parse());
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    Vis[1] = true;
    for(It it = G[1].begin(), fin = G[1].end() ; it != fin ; ++ it)
        H.push(*it);
    W = (parse());
    for(int i = 1 ; i <= W ; ++ i) {
        int x(parse());
        V.clear();
        while(H.top().second <= x && !H.empty()) {
            int Node = H.top().first;
            H.pop();
            if(Node == N) {
                cout << i << '\n';
                return 0;
            }
            Vis[Node] = true;
            V.push_back(Node);
        }
        for(int j = 0 ; j < V.size() ; ++ j)
            for(It it = G[V[j]].begin(), fin = G[V[j]].end(); it != fin ; ++ it)
                if(!Vis[it->first])
                    H.push(*it);
    }
    cout << "-1\n";
    //cin.close();
    cout.close();
    return 0;
}
