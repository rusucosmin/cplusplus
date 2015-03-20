#include <fstream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

ifstream cin("bal.in");
ofstream cout("bal.out");

const int MAXN = 100005;

typedef vector<int> Graph[MAXN];
typedef vector<int>::iterator It;

Graph G, Gt;
int N, M, deg[MAXN], Pair[MAXN];
queue<int> Q;
bitset<MAXN> Used;

int main()
{
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b;
        cin >> a >> b;
        ++ deg[a];
        G[a].push_back(b);
        Gt[b].push_back(a);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(deg[i] == 1)
            Q.push(i);
    for(int Node = Q.front() ; !Q.empty() ; Q.pop(), Node = Q.front() ){
        int Girl = 0;
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin && !Girl ; ++ it)
            if(!Used[*it])
                Girl = *it;
        if(!Girl){
            cout << "NU\n";
            return 0;
        }
        Pair[Node] = Girl;
        Used[Girl] = true;
        for(It it = Gt[Girl].begin(), fin = Gt[Girl].end() ; it != fin ; ++ it) {
            -- deg[*it];
            if(deg[*it] == 1)
                Q.push(*it);
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(deg[i] || !Pair[i]){
            cout << "NU\n";
            return 0;
        }
    cout << "DA\n";
    for(int i = 1 ; i <= N ; ++ i)
        cout << Pair[i] << "\n";
    cin.close();
    cout.close();
    return 0;
}
