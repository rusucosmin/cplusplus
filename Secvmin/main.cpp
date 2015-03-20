#include<fstream>
using namespace std;
ifstream cin("secvmin.in");
ofstream cout("secvmin.out");
int A[100005], B[100005], n, m, i, j, u ,aux, vux, sol2, maximul=1000005;
int main()
{

    cin>>n>>m;
    for(i=1;i<=n;i++)
        cin>>A[i];
    for(j=1;j<=m;j++)
        cin>>B[j];
    j=1;
    for(i=1;i<=n;i++)
          if(B[j]==A[i])
            {
                j++;
                u++;
                if(u==1)
                    sol2=i;
                else
                    if(u==m)
                       {
                        if(maximul>(i-sol2+1))
                            maximul=((i-sol2)+1);
                        u=0;
                        j=sol2;
                        i=sol2+1;
                        }
            }

    if(maximul==1000005)
        cout<<"-1\n";
    else
        cout<<maximul<<"\n";
    return 0;
}
