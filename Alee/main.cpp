#include <fstream>
//#define DEBUG
using namespace std;
ifstream cin("alee.in");
ofstream cout("alee.out");
int l[180][180], q[3][10005], i,j , starti, startj, endi, endj, u, p, xnou, ynou;
short n, m;

const int dx[]={0, 1,  0, -1};
const int dy[]={1, 0, -1,  0};
void init()
{
    cout<<(double)(10*sizeof(int)/1000)+(double)(sizeof(q)/1000)+double(2*sizeof(short))<<" ";;
    int x, y;
    cin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            l[i][j]=-2;
    for(i=1;i<=m;++i)
        {
            cin>>x>>y;
            l[x][y]=-1;
        }
    cin>>starti>>startj;
    l[starti][startj]=1;
    cin>>endi>>endj;
    l[endi][endj]=-3;
    q[1][1]=starti;
    q[2][1]=startj;
}
void intr(int c, int d)
{
    u=u+1;
    if(u>10000)
        u=1;
    q[1][u]=c;
    q[2][u]=d;
}
void extr(int &c, int &d)
{
    p=p+1;
    if(p>10000)
        p=1;
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
        extr(x,y);
        for(i=0;i<4;++i)
        {
            xnou=x+dx[i];
            ynou=y+dy[i];
            if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=n)
                if(l[xnou][ynou]==-2 || l[xnou][ynou]==-3)
                    l[xnou][ynou]=l[x][y]+1, intr(xnou, ynou);
        }

    }
}
void afisare()
{
    #ifdef DEBUG
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<l[i][j]<<" ";
        cout<<"\n";
    }
    #endif
    if(l[endi][endj]==-3)
        cout<<"0\n";
    else
    cout<<l[endi][endj]<<"\n";
}
int main()
{
    init();
    lee();
    afisare();
    return 0;
}
