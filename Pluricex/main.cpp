#include <fstream>
using namespace std;
ifstream cin("pluricex.in");
ofstream cout("pluricex.out");
int n, k, d;
int st[1000];
bool a[1000][1000];
int valid(int p)
{
    int c, i, j;
    c=0;
    for(j=1;j<=d;j++)
        for(i=1;i<=p;i++)
               if(a[st[i]][j]) {c++;  break;}
    if(c==d)   return 1;
    else return 0;

}
void afisare(int p)
{
    for(int i=1;i<=p;i++)
        cout<<st[i]<<" ";
    cout<<"\n";
}
void back(int p)
{
    int pval;
    for(pval=st[p-1]+1;pval<=n;pval++)
    {
        st[p]=pval;
        if(valid(p) && p==k)
             afisare(p);
        else back(p+1);

    }

}
int main()
{
    int i, y, x, j;
    cin>>n>>k>>d;
    for(i=1;i<=n;i++)
      { cin>>y;
       for(j=1;j<=y;j++)
           {cin>>x;
             a[i][x]=1;
            }
      }
    back(1);
    return 0;
}
