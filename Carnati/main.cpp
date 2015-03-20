#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("carnati.in");
ofstream cout("carnati.out");
int b[2500], max2=-((1<<31)-1);
struct carnat
{
    int T, P;
            }  x[2500];

inline int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
inline bool comp(carnat A, carnat B)
{
    return A.T < B.T;
}
int main()
{
    int i, N, C;

    cin>>N>>C;
    for (i = 1; i <= N; i ++)
        cin>>x[i].T>>x[i].P;
    x[0].T = x[0].P = -10;

    sort(x+1,x+N+1, comp);   //sortare

    for(int j=1;j<=N;++j)
    {

        int u=1;

        for(int i=0;i<=x[N].T;++i)
        {

            b[i]=b[i-1]-C;

            while(x[u].T==i)
                if(x[u++].P>=x[j].P)
                    b[i]+=x[j].P;

        }

        int min2=0;

        for(int i=0;i<=x[N].T;++i)
            min2=min(min2,b[i]),max2=max(max2,b[i]-min2);//cout<<b[i]<<"\n";

    }

    cout<<max2<<"\n";

    return 0;

}
