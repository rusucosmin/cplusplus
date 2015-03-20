//v 2.0

#include <fstream>
#include <vector>
using namespace std;

ifstream cin ("cerere.in");
ofstream cout("cerere.out");

const int N_MAX = 100005;

vector <int> Graph[N_MAX], stack(N_MAX), k(N_MAX), g(N_MAX);
bool has_dad[N_MAX];
int n, top;
void dfs(int node)
{
    stack[++top] = node;
    if( k[node] ) /// isn't smart enough
        g[node] = g[ stack[top - k[node] ] ]   +   1;
    for(vector<int> :: iterator it = Graph[node].begin(), fin = Graph[node].end(); it != fin ; ++ it)
        dfs(*it);
    --top;   ///revin din recursivitate
}
int main()
{

    cin >> n;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> k[i];
    for(int i = 1 ; i != n ; ++ i)
    {
        int a, b;
        cin >> a >> b;
        has_dad[b] = true;
        Graph[a].push_back(b);
    }

    int i;
    for(i = 1 ; has_dad[i] && i <= n ;++ i) ;
    dfs(i);
    for(int i = 1 ; i <= n ; ++ i)
        cout << g[i] << " ";
    return 0;
}
