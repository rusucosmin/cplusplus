#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("trilant.in");
ofstream cout("trilant.out");

const int MAXN = 100010;
const long long oo = (1LL<<60)-1;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

Graph G;
int pathA[MAXN], pathB[MAXN], pathC[MAXN], N, M, A, B, C;
long long minTime = oo;
int minNode;
vector<long long> dA(MAXN, oo), dB(MAXN, oo), dC(MAXN, oo);
vector<int>sol;

priority_queue< pair<long long, int> , vector<pair<long long, int> >, greater<pair<long long, int> > > Q;

inline void Dijkstra(int Source, vector<long long> &d , int f[MAXN]){
    for(Q.push(make_pair(0, Source)), d[Source] = 0, f[Source] = -1 ; !Q.empty() ; Q.pop() ){
        int Node = Q.top().second;
        for(It it = G[Node].begin() , fin = G[Node].end() ; it != fin ; ++ it)
            if(d[it->first] > d[Node] + it->second){
                d[it->first] = d[Node] + it->second;
                Q.push(make_pair(d[it->first], it->first));
                f[it->first] = Node;
            }
    }
}

int main() {
    cin >> N >> M;
    cin >> A >> B >> C;
    for(int i = 1 ; i <= M ; ++ i){
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    Dijkstra(A, dA, pathA);
    Dijkstra(B, dB, pathB);
    Dijkstra(C, dC, pathC);

    for(int i = 1 ; i <= N ; ++ i)
        if(minTime > dA[i] + dB[i] + dC[i])
            minTime = dA[i] + dB[i] + dC[i],
            minNode = i;
    cout << minTime << "\n";

    for(int x = minNode ; x != pathA[A] ; x = pathA[x])
        sol.push_back(x);
    cout << sol.size() << " ";
    for(vector<int>::iterator it = sol.begin() , fin = sol.end() ; it != fin ; ++ it)
        cout << *it << " ";
    cout << "\n";


    sol.clear();


    for(int x = minNode ; x != pathB[B] ; x = pathB[x])
        sol.push_back(x);
    cout << sol.size() << " ";
    for(vector<int>::iterator it = sol.begin() , fin = sol.end() ; it != fin ; ++ it)
        cout << *it << " ";
    cout << "\n";

    sol.clear();

    for(int x = minNode ; x != pathC[C] ; x = pathC[x])
        sol.push_back(x);
        cout << sol.size() << " ";
    for(vector<int>::iterator it = sol.begin() , fin = sol.end() ; it != fin ; ++ it)
        cout << *it << " ";
    cout << "\n";
    cin.close();
    cout.close();
    return 0;
}
