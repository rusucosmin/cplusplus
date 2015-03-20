#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <cstring>
#include <cassert>

using namespace std;

const char infile[] = "sabotaj.in";
const char outfile[] = "sabotaj.out";

ifstream cin(infile);
ofstream cout(outfile);

typedef vector<int> :: iterator It;

const int MAXN = 205;
const int oo = 0x3f3f3f3f;

int F[MAXN][MAXN], C[MAXN][MAXN], Father[MAXN];
bitset <MAXN> Used;
vector <int> G[MAXN];
queue <int> Q;

inline bool BFs(const int &Source, const int &Sink) {
    Used.reset();
    for(Q.push(Source), Used[Source] = 1 ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getFlow(const int &Source, const int &Sink) {
    memset(F, 0, sizeof(F));
    memset(Father, 0, sizeof(Father));
    int maxFlow = 0;
    while(BFs(Source, Sink)) {
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!C[*it][Sink] || !Used[*it])
                continue;
            Father[Sink] = *it;
            int minFlow = oo;
            for(int i = Sink ; i != Source && minFlow ; i = Father[i])
                minFlow = min(minFlow, C[Father[i]][i] - F[Father[i]][i]);
            if(!minFlow)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i])
                F[Father[i]][i] += minFlow,
                F[i][Father[i]] -= minFlow;
            maxFlow += minFlow;
        }
    }
    return maxFlow;
}

int main() {
    const int Source = 1;
    int N, M, minCut = oo;
    vector <int> Ans;
    vector <pair<int, int> > edges;
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        C[x][y] += z;
        C[y][x] += z;
        G[x].push_back(y);
        G[y].push_back(x);
        edges.push_back(make_pair(x, y));
    }
    for(int Sink = 2 ; Sink <= N ; ++ Sink) {
        int actMaxFlow = getFlow(Source, Sink);
        if(minCut > actMaxFlow) {
            Ans.clear();
            minCut = actMaxFlow;
            for(int i = 0 ; i < M ; ++ i)
                if(Used[edges[i].first] + Used[edges[i].second] == 1)
                    Ans.push_back(i);
        }
    }
    cout << minCut << ' ' << Ans.size() << '\n';
    for(vector <int> :: iterator it = Ans.begin(), fin = Ans.end(); it != fin ; ++ it)
        cout << *it + 1 << '\n';
    cin.close();
    cout.close();
    return 0;
}
