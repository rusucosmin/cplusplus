/*
    Cuplaj
*/
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("drumuri2.in");
ofstream cout("drumuri2.out");


const int MAXN = 104;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

bitset <MAXN> G[MAXN], Used;
vector<int> r(MAXN, -1);
int N, M, Ans;

inline bool pairup(int Node){
    if(Node == -1)
        return true;
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(int i = 1 ; i <= N ; ++ i)
        if( G[Node][i] && pairup(r[i])) {
            r[i] = Node;
            return true;
        }
    return false;
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x][y] = true;
    }
    /// royfloyd
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            for(int k = 1 ; k <= N ; ++ k)
                G[i][k] = ((G[i][j] && G[j][k]) || G[i][k]);  /// am drum de la i la k daca am drum de la i la j si de la j la k
    for(int i = 1 ; i <= N ; ++ i) {
        Used.reset();
        if(!pairup(i))
            ++ Ans;
    }
    cout << Ans << "\n";
    cin.close();
    cout.close();
    return 0;
}
