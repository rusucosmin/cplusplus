#include <fstream>
#include <set>s

using namespace std;

ifstream cin("rmvc.in");
ofstream cout("rmvc.out");

typedef set<int> Graph[55];
typedef set<int>:: iterator It;

int st[55];
Graph G;
int N, M;
vector<int> sol, v;


inline void Back(int p){
    for(int pval = 1 ; pval <= N ; ++ pval) {
        st[p] = pval;
        if(valid(p)){
            sol = v;
        }
        back(p+1);
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].insert(y);
        G[y].insert(x);
    }
    Back(1);
    cin.close();
    cout.close();
    return 0;
}
