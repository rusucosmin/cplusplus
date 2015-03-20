#include <fstream>
#include <set>

using namespace std;

string file = "tric";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100000;

int N, M, Ans;
set< int > G[MAXN];

int main() {
    cin >> N >> M;
    for(int i = 1; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].insert(y);
        G[y].insert(x);
    }
    for(int i = 0 ; i < N ; ++ i)
        for(set<int> :: iterator j = G[i].upper_bound(i), fj = G[i].end(); j != fj ; ++ j)
            for(set<int> :: iterator k = G[*j].upper_bound(*j), jk = G[*j].end(); k != jk ; ++ k)
                /// e clar ca e muchia i -> j, j - > k => trebuie sa verific muchia k -> i
                if(G[*k].find(i) != G[*k].end())
                    ++ Ans;
    cout << Ans << '\n';
    cin.close();
    cout.close();
    return 0;
}
