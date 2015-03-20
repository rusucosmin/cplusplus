#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "drumuri5.in";
const char outfile[] = "drumuri5.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 150005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G, Gt, dag, dagt, outer;
bitset <MAXN> Used, solution;
vector <int> discovered, dist(MAXN), where(MAXN), in(MAXN), out(MAXN);
int N, M, scc;

void DFp(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFp(*it);
    discovered.push_back(Node);
}

void DFm(const int &Node, const int &scc) {
    Used[Node] = true;
    where[Node] = scc;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFm(*it, scc);
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFp(i);
    Used.reset();
    for(vector <int> :: reverse_iterator it = discovered.rbegin(), fin = discovered.rend(); it != fin ; ++ it)
        if(!Used[*it])
            DFm(*it, ++ scc);
    /// Building the DAG
    for(int i = 1 ; i <= N ; ++ i)
        for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
            if(where[i] != where[*it]) {
                dag[where[i]].push_back(where[*it]);
                dagt[where[*it]].push_back(where[i]);
                ++ in[where[*it]];
                ++ out[where[i]];
            }
    queue <int> Q;
    for(int i = 1 ; i <= scc ; ++ i)
        if(!out[i])
            Q.push(i);
    for(; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        for(It it = dagt[Node].begin(), fin = dagt[Node].end(); it != fin ; ++ it) {
            -- out[*it];
            if(!out[*it])
                Q.push(*it);
            dist[*it] = max(dist[*it], dist[Node] + 1);
        }
    }
    int maxd = -1, num = 0;
    for(int i = 1 ; i <= scc ; ++ i)
        if(!in[i]) {
            ++ num;
            outer[ dist[i] ].push_back(i);
            maxd = max(maxd, dist[i]);
        }
    while( maxd >= 0 ) {
        if(num == 1)
            solution[outer[maxd][0]] = 1;
        for(int i = 0 ; i < static_cast<int>(outer[maxd].size()) ; ++ i) {
            int Node = outer[maxd][i];
            for(It it = dag[Node].begin(), fin = dag[Node].end(); it != fin ; ++ it) {
                -- in[*it];
                if(!in[*it]) {
                    outer[ dist[*it] ].push_back(*it);
                    ++ num;
                }
            }
        }
        num -= outer[ maxd ].size();
        outer[maxd].clear();
        while(maxd >= 0 && outer[maxd].size() == 0)
            -- maxd;
    }
    vector <int> Ans;
    for(int i = 1 ; i <= N ; ++ i)
        if(solution[where[i]])
            Ans.push_back(i);
    cout << Ans.size() << '\n';
    for(int i = 0 ; i < static_cast<int>(Ans.size()) ; ++ i)
        cout << Ans[i] << ' ';
    cin.close();
    cout.close();
    return 0;
}
