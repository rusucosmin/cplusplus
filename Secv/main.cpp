#include <fstream>
#include <algorithm>
#include <limits.h>
using namespace std;

ifstream cin("secv.in");
ofstream cout("secv.out");
bool avem[2000000005];
int n, i, j, a[50055], k, v[50055], best=1<<30, sol;
int main()
{
    cin>>n;
    for(i=1;i<=n;++i)
        { cin>>a[i];
          if(!avem[a[i]])
          {
              ++k;
              v[k]=a[i];
              avem[a[i]]=1;
          }
        }
    sort(v+1, v+k+1);
    for(i=1;i<=n;i++)
    {
        if(a[i]==v[1])
            {
                int indice=1;

                for(j=i+1;j<=n+1; ++j)
                    {
                        if(indice==k)
                            {
                                sol=j-i;
                                if(sol<best)
                                    best=sol;
                                break;
                            }
                        if(a[j]==v[indice+1])
                            {
                                indice++;
                            }

                    }
            }
    }
    if(best==(1<<30))
        cout<<"-1\n";
    else
    cout<<best<<"\n";


    return 0;
}
