#include <fstream>
#include <string.h>
//#define debug
using namespace std;

ifstream cin("cod.in");
ofstream cout("cod.out");
char s[1005];
int a[1005], b[1005],sol[1005], n, m, i, j, u;
int d[1005][1005];
inline int max(int a, int b)
{
    if(a>b) return a;
    return b;
}
int main()
{
    cin.getline(s, 1002);
    n=strlen(s);
    for(i=0;i<n;i++)
        a[i+1]=s[i]-'0';
    cin.getline(s, 1002);
    m=strlen(s);
    for(i=0;i<m;i++)
        b[i+1]=s[i]-'0';
    for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(a[i]==b[j])
                    d[i][j]=d[i-1][j-1]+1;
                else d[i][j]=max(d[i-1][j], d[i][j-1]);
  #ifdef debug
    for(i=1;i<=n;i++)
            {for(j=1;j<=m;j++)
                cout<<d[i][j]<<" ";
            cout<<"\n";}
    #endif
    i=n;j=m;
    while(i>=1 && j>=1)
    {
        if(a[i]==b[j])
            sol[++u]=a[i], i--, j--;
        else if(d[i-1][j]>=d[i][j-1])
            i--;
        else j--;
    }
    for(i=u;i>=1;i--)
        cout<<sol[i]<<" ";
    cin.close();
    cout.close();
    return 0;
}
