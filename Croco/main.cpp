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

string file = "croco";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 112;
const int oo = (1<<31)-1;

int N, M, C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN], Ans, Sink;
bitset <MAXN> used, in;

bool bfs() {
    queue <int> Q;
    used.reset();
    for(Q.push(1), used[1] = true ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        if(Node == Sink)
            continue;
        for(int i = 1 ; i <= N ; ++ i)
            if(!used[i] && C[Node][i] - F[Node][i] > 0) {
                used[i] = true;
                Father[i] = Node;
                Q.push(i);
            }
    }
    return used[Sink];
}

void DFs(int Node) {
    in[Node] = true;
    for(int i = 1 ; i <= N ; ++ i)
        if(!in[i] && C[Node][i] - F[Node][i] > 0)
            DFs(i);
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> C[i][j], Ans += C[i][j];
    int minFlow = oo;
    for(Sink = 2 ; Sink <= N ; ++ Sink) {
        memset(F, 0, sizeof(F));
        int flow = 0;
        while(bfs()) {
            for(int j = 1 ; j <= N ; ++ j) {
                if(j == Sink || !C[j][Sink])
                    continue;
                int actFlow = oo;
                Father[Sink] = j;
                for(int i = Sink ; i != 1 ; i = Father[i])
                    actFlow = min(actFlow, C[Father[i]][i] - F[Father[i]][i]);
                if(!actFlow)
                    continue;
                for(int i = Sink ; i != 1 ; i = Father[i])
                    F[Father[i]][i] += actFlow,
                    F[i][Father[i]] -= actFlow;
                flow += actFlow;
            }
        }
        if(minFlow > flow) {
            in.reset();
            minFlow = flow;
            DFs(1);
        }
    }
    cout << Ans / 2 - minFlow << ' ' << in.count() << '\n';
    for(int i = 1 ; i <= N ; ++ i)
        if(in[i])
            cout << i << ' ';
    cin.close();
    cout.close();
    return 0;
}
