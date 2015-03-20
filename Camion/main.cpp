#include <fstream>
#include <vector>

#define x first
#define y second

using namespace std;

const int MAXN = 602;

vector<int> G[MAXN];
int N, M, K, C;

ifstream cin("camion.in");
ofstream cout("camion.out");

inline void Afisare() {

    cout << "\nVector:\n";
    for(int i = 1 ; i <= N ; ++ i) {
        for(vector<int> :: iterator it = G[i].begin() ; it != G[i].end(); ++ it)
            cout << *it << " ";
        cout << "\n";
    }

}

int main() {
    cin >> N >> M >> K >> C;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            G[i].push_back(j);
    for(int i = 1 ; i <= K ; ++ i) {
        pair<int, int> st, fn;
        // Afisare();
        cin >> st.x >> st.y >> fn.x >> fn.y;
        for(int x = st.x ; x <= fn.x ; ++ x)
            for(int y = st.y ; y <= fn.y ; ++ y)
                if(G[x].size() >= st.y)
                    G[x].erase(G[x].begin() + st.y - 1);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(G[i].size() >= C)
            cout << G[i][C-1] << '\n';
        else cout << "0\n";
    return 0;
}
