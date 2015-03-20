#include <fstream>

using namespace std;

ifstream cin("paianjen.in");
ofstream cout("paianjen.out");
int n, m, l[150][150], i, j, p_i, p_j, m_i, m_j, qu, q[3][2500], u, p, xnou, ynou;
bool a[150][150];
struct alabala{

string st;} s[150][105];
const int dx[]={1, 0, -1, 0};
const int dy[]={0, 1,  0,-1};
const string di[]={"S", "E", "N", "V"};
void read()
{
    int x, y, xx, yy;
    cin>>n>>m;
    for(i=0;i<n;++i)
        for(j=0;j<m;++j)
            l[i][j]=-1;
    cin>>p_i>>p_j;
    l[p_i][p_j]=0;
    cin>>m_i>>m_j;
    l[m_i][m_j]=-3;
    cin>>qu;
    for(i=1;i<=qu;++i)
        {
            cin>>x>>y>>xx>>yy;
            a[x][y]=a[xx][yy]=1;
        }
    q[1][1]=p_i;
    q[2][1]=p_j;
}
void intr(int c, int d)
{
    ++u;
    q[1][u]=c;
    q[2][u]=d;
}
void extr(int &c, int &d)
{
    ++p;
    c=q[1][p];
    d=q[2][p];
}
void lee()
{
    int x, y;
    u=1;
    p=0;
    while(p!=u)
    {
        extr(x, y);
        for(i=0;i<4;++i)
        {
            xnou=x+dx[i];
            ynou=y+dy[i];
            if(xnou>=0 && xnou<n && ynou>=0 && ynou<m)
                if(l[xnou][ynou]>l[x][y]+1 || l[xnou][ynou]==-1 || l[xnou][ynou]==-3)
                    if((a[xnou][ynou]==1 && a[x][y]==0) || (a[xnou][ynou]==0 && a[x][y]==1) || (a[xnou][ynou]==0 && a[x][y]==0))
                    {
                        l[xnou][ynou]=l[x][y]+1;
                        s[xnou][ynou].st=s[x][y].st+di[i];
                        intr(xnou, ynou);
                    }
        }
    }
}
int main()
{
    read();
    lee();
   /*
    for(i=0;i<n;++i)
        {for(j=0;j<m;++j)
            cout<<l[i][j]<<" ";
        cout<<"\n";}
    for(i=0;i<n;++i)
        {for(j=0;j<m;++j)
            cout<<s[i][j].st<<" ";
        cout<<"\n";}
    */
    cout<<l[m_i][m_j]<<"\n"<<s[m_i][m_j].st;
    cin.close();
    cout.close();
    return 0;
}
