#include <fstream>

using namespace std;

ifstream cin("amedie.in");
ofstream cout("amedie.out");
int a[808][808], fr[100010], k, r, i, j, n, m, q, x, maxi;
bool ok[808][808];
char c;
inline int max(int a, int b) { if(a>b) return a; else return b;}
int main()
{
    cin>>n>>m>>q;
    k=n*m;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin>>a[i][j], fr[a[i][j]]++, maxi=max(a[i][j], maxi);
    for(i=1;i<=q;i++)
        {
            cin>>c;
            if(c=='Q')
                {
                int s=0;
                bool gasit=false;
                for(j=1;j<=maxi && !gasit;j++)
                {
                    if(s+fr[j]>=k/2+k%2)
                        cout<<j<<" ", gasit=1;
                    else s+=fr[j];
                }
                cout<<'\n';
        }
            else if(c=='L')
                {
                    cin>>r;
                    for(j=1;j<=m;j++)
                        if(!ok[r][j])
                            ok[r][j]=1, k--, fr[a[r][j]]--;
                }
            else if(c=='C')
                {
                    cin>>r;
                    for(j=1;j<=n;j++)
                        if(!ok[j][r])
                            ok[j][r], k--, fr[a[j][r]]--;
                }
        }
    cin.close();
    cout.close();
    return 0;
}
