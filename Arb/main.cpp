#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>
#include <map>

using namespace std;

ifstream cin("arb.in");
ofstream cout("arb.out");

const int MAXN = 250005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int V[MAXN], Lev[MAXN], N, Q, First[MAXN], Last[MAXN], K,  A[MAXN], B[MAXN], Sol[MAXN];
pair<int, int> Qu[3*MAXN];
int Sum[MAXN];

inline void DFs(int Node, int Level) {
    Lev[Node] = Level;
    First[Node] = ++K;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        DFs(*it, Level+1);
    Last[Node] = K;
}

inline int lsb (int x) {
    return (x ^ (x - 1)) & x;
}

inline void Add(int Node, int Value) {
    while(Node <= N) {
        Sum[Node] += Value;
        Node += lsb(Node);
    }
}

inline int Query(int Node) {
    long long Ans = 0;
    while(Node > 0) {
        Ans += Sum[Node];
        Node -= lsb(Node);
    }
    return Ans;
}

int main()
{
    cin >> N ;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> V[i];
    for(int i = 2 ; i <= N ; ++ i) {
        int x;
        cin >> x;
        G[x].push_back(i);
    }
    DFs(1, 0);
    for(int i = 1 ; i <= N ; ++ i)
        Qu[i] = make_pair(Lev[i], -i);
    //Queries
    cin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        cin >> A[i] >> B[i];
        Qu[N + i] = make_pair(Lev[A[i]] + B[i], i);
    }
    sort(Qu + 1 , Qu + N + Q + 1);
    for(int i = 1 ; i <= N + Q ; ++ i)
        if(Qu[i].second < 0)
            Add(First[-Qu[i].second], V[-Qu[i].second]);
        else Sol[Qu[i].second] = Query(Last[A[Qu[i].second]]) - Query(First[A[Qu[i].second]] - 1);
    for(int i = 1 ; i <= Q ; ++ i)
        cout << Sol[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
