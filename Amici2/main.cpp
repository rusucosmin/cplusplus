#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("amici2.in");
ofstream cout("amici2.out");

const int MAXN = 21005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, M, D, Node;
vector<int> d(MAXN, -1);
queue<int> Q;
int T;
int Ans;



int main()
{
    cin >> T;
    while(T--){
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        G[i].clear(), d[i] = -1;
    for(int i = 1 ; i <= M ; ++ i){
        int X, Y;
        cin >> X >> Y;
        //for(int i = 0 ; i < 2 ; ++ i)
        G[X].push_back(Y),
          //  swap(X, Y);
        G[Y].push_back(X);
    }
    D = 0;
    for(Q.push(1), d[1] = 0 , Node = Q.front(); !Q.empty() ; Q.pop(), Node = Q.front())
        for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
            if(-1 == d[*it])
                d[*it] = d[Node] + 1,
                D = max(D, d[*it]),
                Q.push(*it);
    for(Ans = 1 ; ( 1 << Ans ) < D; ++ Ans);
    cout << Ans << "\n";
    }
    cin.close();
    cout.close();
    return 0;
}
