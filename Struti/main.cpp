#include<fstream>
#include<deque>
#define N_MAX 1005
#define int_min -((1<<31)-1)
#define int_max -int_min
//#define debug
using namespace std;
int n, m, p, l, c, sol, nr_sol;
int A[N_MAX][N_MAX], Min[N_MAX][N_MAX], Max[N_MAX][N_MAX];

deque <int> a, b;

inline void start();
inline void solve(int l, int c);

int main()
{
    start();
    return 0;
}
inline void start()
{
    freopen("struti.in", "r", stdin);
    freopen("struti.out", "w", stdout);
    scanf("%d %d %d", &n, &m, &p);
    for( int i=1; i<=n; ++i )
        for( int j=1; j<=m; ++j )
            scanf("%d", &A[i][j]);
    for( ; p ; )
    {
        scanf("%d %d", &l, &c);
        sol=int_max;
        nr_sol=0;
        #ifdef debug
        printf("%d\n", sol);
        #endif
        solve(l, c);
        if(!(l==c))
            solve(c, l);
        --p;
        printf("%d %d\n", sol, nr_sol);
    }
}
inline void solve(int l, int c)
{
    a.clear();
    b.clear();
    for(int i=1; i<=n; ++i)
        {
            a.clear();
            b.clear();
            for(int j=1; j<=m; ++j)
            {
                while(!a.empty() && A[i][a.back()]>=A[i][j])
                    a.pop_back();
                a.push_back(j);
                if(j-a.front()>=c)
                    a.pop_front();
                if(j>=c)
                    Min[i][j]=A[i][a.front()];
                while(!b.empty() && A[i][b.back()]<=A[i][j])
                    b.pop_back();
                b.push_back(j);
                if(j-b.front()>=c)
                    b.pop_front();
                if(j>=c)
                    Max[i][j]=A[i][b.front()];
            }
        }
    #ifdef debug
    printf("MINIMUL\n");
    for(i=1; i<=n; ++i)
        {
            for(j=1; j<=m; ++j)
                printf("%d ", Min[i][j]);
            printf("\n");}
    printf("MAXIMUL\n\n");
    for(i=1; i<=n; ++i)
        {
            for(j=1; j<=m; ++j)
                printf("%d ", Max[i][j]);
            printf("\n");
        }
    #endif
    for(int j=c; j<=m ;++j)
        {
            a.clear();
            b.clear();
            for(int i=1; i<=n; ++i)
            {
                while(!a.empty() && Min[i][j]<=Min[a.back()][j])
                    a.pop_back();
                a.push_back(i);
                while(!b.empty() && Max[i][j]>=Max[b.back()][j])
                    b.pop_back();
                b.push_back(i);
                if(i-a.front()>=l)
                    a.pop_front();
                if(i-b.front()>=l)
                    b.pop_front();
                if(i >= l)
                {
                    int aux=Max[b.front()][j]-Min[a.front()][j];
                    if(aux<sol)
                        sol=aux, nr_sol=1;
                    else if(aux==sol)
                        nr_sol++;
                }

            }
        }
}
