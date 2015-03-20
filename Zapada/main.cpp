#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

string file = "zapada";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, M, cTotal, c[MAXN], start;
Graph G;
bitset <MAXN> has;

void chooseStart(int Node) {
    has[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!has[*it])
            chooseStart(*it);
    start = Node;
}

void DFs(int Node) {
    c[Node] = (++ cTotal);
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!c[*it])
            DFs(*it);
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!has[i])
            chooseStart(i);
    DFs(start);
    for(int i = 1 ; i <= N ; ++ i)
        cout << c[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
