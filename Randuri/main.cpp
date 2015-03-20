#include <fstream>
#include <string.h>
using namespace std;

ifstream cin("randuri.in");
ofstream cout("randuri.out");
char a[105][105];
bool sters[105];
bool muzicalitate(char s1[], char s2[])
{
    int n=strlen(s1);
    int m=strlen(s2);
    int D[105][105];
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            D[i][j]=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            if(s1[i]==s2[j])
                D[i+1][j+1]=D[i][j]+1;
            else D[i+1][j+1]=max(D[i+1][j], D[i][j+1]);
        }
    if(D[n][m]>6) return 1;
    return 0;
}
int main()
{
    bool ok=0;

    short n=0;

    int k=0;
    int contor=0;
    int j=0;
    int x=0;
    //read
    while(cin.getline(a[++n], 105));
    //solve
    --n;
    for(int i=1;i<=n;++i)
        {
            if(!sters[i])
                {
                    if(j==0)
                        j=i;
                    else if(k==0)
                        k=i;
                        else if(x==0)
                            if(muzicalitate(a[j], a[i]))
                            {
                                x=i;
                        //        cout<<j<<" "<<k<<" "<<x<<"\n";
                                sters[k]=1;
                                ++contor;
                                i=j-1;
                                j=0;
                                k=0;
                                x=0;
                            }
                            else if(i==n-1) k=0, i=1;
                }
            //cout<<i<<"iiii\n";
        }
    cout<<contor<<"\n";
    cin.close();
    cout.close();
    return 0;
}
