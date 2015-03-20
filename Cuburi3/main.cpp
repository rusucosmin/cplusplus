#include<fstream>
#include<algorithm>
using namespace std;

ifstream cin("cuburi3.in");
ofstream cout("cuburi3.out");
int n, l[20005], g[20005], i, j, aux, c, maxi, best[1000], a[10000], k;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>l[i]>>g[i];
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            {   c++;
                if(l[i]<l[j])
                    {
                        aux=l[i];
                        l[i]=l[j];
                        l[j]=aux;
                        aux=g[i];
                        g[i]=g[j];
                        g[j]=aux;
                    }
                if(l[i]==l[j])
                    if(g[i]<g[j])
                    {
                        aux=g[i];
                        g[i]=g[j];
                        g[j]=aux;
                    }

            }
    for(i=1;i<=n;i++)
        {
        for(j=1;j<=i;j++)
           {
            if(maxi<best[j] && g[i]<g[j])
                {
                    maxi=best[j];
                    k++;
                    a[k]=j;

                }
            best[i]=maxi+l[i];
            }
        }

    cout<<best[n]<<"\n";
    for(i=1;i<=k;i++)
        cout<<a[i]<<"\n";
}
