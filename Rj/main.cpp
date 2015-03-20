#include <fstream>
#include <limits.h>
//#define cosmin
using namespace std;
ifstream cin("rj.in");
ofstream cout("rj.out");
int n, m, q1[3][10010],q2[3][10010], i, j, r[100][100],ju[100][100], k1, k2, u1, p1, u2, p2, mini=INT_MAX, xnou, ynou, maxi, maxj;
char c , a[110];
const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
void init()
{
    cin>>n>>m;
    cin.getline(a, 10);
    for(i=1;i<=n;i++){
        cin.getline(a, 105);
        for(j=0;j<m;j++)
            {
                c=a[j];
                if(c=='R')
                    {
                        k1=1;
                        r[i][j+1]=1; //pornesc de la romeo
                        ju[i][j+1]=-3; //o gasesc pe julieta
                        q2[1][k1]=i;
                        q2[2][k1]=j+1;
                    }
                else if(c=='X')   //poarta inchisa
                    {
                        r[i][j+1]=-2;
                        ju[i][j+1]=-2;
                    }
                else if(c=='J')
                    {
                        k2++;
                        ju[i][j+1]=1; //pornesc de la julieta
                        r[i][j+1]=-3; //il gasesc pe romeo
                        q1[1][k2]=i;
                        q1[2][k2]=j+1;
                    }
                else if(c==' ')
                    {
                        r[i][j+1]=-1;
                        ju[i][j+1]=-1;
                    }
            }
    }
}
void intr1(int c, int d)
{
    u1=u1+1;
    q1[1][u1]=c;
    q1[2][u1]=d;
}
void extr1(int &c, int &d)
{
    p1=p1+1;
    c=q1[1][p1];
    d=q1[2][p1];
}
void leeJulieta()
{
    int x, y;
    u1=1;
    p1=0;
    while(p1!=u1)
    {
            extr1(x, y);
            for(i=0;i<8;i++)
                {
                    xnou=x+dx[i];
                    ynou=y+dy[i];
                    if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
                            if(ju[xnou][ynou]!=-2)
                                if(ju[xnou][ynou]>ju[x][y]+1 || ju[xnou][ynou]==-1)
                                {
                                    ju[xnou][ynou]=ju[x][y]+1;
                                    intr1(xnou, ynou);
                                }
                }
    }
}
void intr2(int c, int d)
{
    u2=u2+1;
    q2[1][u2]=c;
    q2[2][u2]=d;
}
void extr2(int &c, int &d)
{
    p2=p2+1;
    c=q2[1][p2];
    d=q2[2][p2];
}
void leeRomeo()
{
    int x, y;
    u2=1;
    p2=0;
    while(p2!=u2)
    {
            extr2(x, y);
            for(i=0;i<8;i++)
                {
                    xnou=x+dx[i];
                    ynou=y+dy[i];
                    if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
                            if(r[xnou][ynou]!=-2)
                                if(r[xnou][ynou]>r[x][y]+1 || r[xnou][ynou]==-1)
                                {
                                    r[xnou][ynou]=r[x][y]+1;
                                    intr2(xnou, ynou);
                                }
                }
    }
}
void search()
{
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(r[i][j]==ju[i][j] && r[i][j]!=-3 && r[i][j]!=-2 && r[i][j]!=-1 && r[i][j]!=0)
                {
                        if(mini>r[i][j])
                            {
                                mini=r[i][j];
                                maxi=i;
                                maxj=j;
                            }
                }
}
void afisare()
{
    if(mini==INT_MAX)
        cout<<"0"<<" "<<maxi<<" "<<maxj<<"\n";
    else
    cout<<mini<<" "<<maxi<<" "<<maxj<<"\n";
}
int main()
{
    init();
    leeJulieta();
    leeRomeo();
    #ifdef cosmin
    for(i=1;i<=n;i++){
            for(j=1;j<=m;j++)
                cout<<ju[i][j]<<" ";
            cout<<"\n";
        }
    for(i=1;i<=n;i++){
            for(j=1;j<=m;j++)
                cout<<r[i][j]<<" ";
            cout<<"\n";
        }
    #endif
    search();
    afisare();
    return 0;
}
