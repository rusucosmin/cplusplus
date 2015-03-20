#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

queue <unsigned int> Q;
vector <unsigned int> A[100005], a[100005];
unsigned int d[100005], x[100005], y[100005], n, m, X, Y;
bool viz[100005];
ifstream in("painting.in");
ofstream out("painting.out");

void bfs(unsigned int no, unsigned int colour)
{
    if( d[no] == 0 )    //verific pentru nodul "MARE"
        d[no] = colour;
    for( Q.push(no) ; !Q.empty(); Q.pop() )
    {
        unsigned int node = Q.front() ;
        for(unsigned int i = 0; i < a[node].size() ; ++ i )
        {
            if(d[a[node][i]] == 0)    //DACA NU A FOST COLORAT
            {
                d[a[node][i]] = colour;
                Q.push(a[node][i]);
            }
        }
    }
}
void dfs(int nod)
{
    for( Q.push(nod) ; !Q.empty(); Q.pop() )
    {
        unsigned int node = Q.front() ;
        for(unsigned int i = 0; i < A[node].size() ; ++ i )
        if(!viz[A[node][i]])
        {
            viz[A[node][i]] = true;
            a[node].push_back(A[node][i]);
            Q.push(A[node][i]);
        }
    }
}
int main()
{
    //READ
    in>>n>>m;
    for(unsigned int  i = 1 ; i <= n - 1 ; ++ i)
    {
        in>>X>>Y;
        A[X].push_back(Y);
        A[Y].push_back(X);
    }
    viz[1]=true;
    dfs(1);
    for(unsigned int i = 1 ; i <= m ; ++ i)
        in>>x[i]>>y[i];
    //SOLVE
    for(unsigned int i = m ; i >= 1 ; -- i)
        bfs(x[i], y[i]);
    //WRITE
    for(unsigned int  i = 1 ; i <= n ; ++ i)
        if(d[i] == 0)
            out<<"1 ";
        else out<<d[i]<<" ";
    in.close();
    out.close();
    return 0;
}
