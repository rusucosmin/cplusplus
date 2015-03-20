#include <fstream>
#include <math.h>
//#define cosmin
using namespace std;

ifstream cin("gheizere.in");
ofstream cout("gheizere.out");
const int dx[]={-1, 0, 1};
const int dy[]={ 0, 1, 0};
int n, m, pr, a, b, r, t, d, v, e, i, j, u, p, ts, xx;
short q[3][100000];
int gh[255][255];
//struct vulcani_mai_multi{
//int du; //numarul de vulcani
//int v[50];//
//}
int M[255][255];
bool ok;
int timp[255][255];
inline int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
inline int caut(int l, int c, int xxx, int ts)
{
    int i, j, t, d;
    //caut existenta centrului unui gheizer unee am memorate date despre durata
  //  for (i=l-xxx; i<=l+xxx; i++)
    //     for (j=c-xxx; j<=c+xxx; j++)
            if (gh[l][c] && i>0 && j>0 && i<=n && j<=m)
            {
                //calculez daca este afectata celula (i,j)
                t = gh[l][c] / 100;   // timpul intre eruptii

                d = gh[l][c] % 100;   // durata unei eruptii
                if (ts % (t + d) >= t) return 0;
            }
    return 1;
}
void init()
{
    cin>>n>>m>>pr; //prima linie din fiser
    cin>>v>>e;    //a doua linie din -||-
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            timp[i][j]=-1;
    q[1][1]=v;
    q[2][1]=1;
    timp[v][1]=1;
    for(int i=1;i<=pr;i++)
        {
            cin>>a>>b>>r>>t>>d;
            gh[a][b]=t*100+d;
            for(int ii=a-r;ii<=a+r;ii++)
                for(int jj=b-r;jj<=b+r;jj++)
                   M[ii][jj]=max(r, M[ii][jj]);
                  // M[ii][jj].v[++M[ii][jj].du]=r;
        }
}
void intr(int c, int d)
{
    u=u+1;
    q[1][u]=c;
    q[2][u]=d;
}
void extr(int &c, int &d)
{
    p=p+1;
    c=q[1][p];
    d=q[2][p];
}
void lee()
{
    int x, y, xnou, ynou;
    u=1;
    p=0;
    while(p!=u)
    {
        extr(x, y);
        if (timp[x][y]!=-1 && x == e && y == m)
		{
		    break;
		}
//		 timpul scurs
        ts = timp[x][y];
        for(int ab=0;ab<3;++ab)
            {
                xnou=x+dx[ab];
                ynou=y+dy[ab];
                xx = M[xnou][ynou];
                ok = 1;
                if (xx && caut(xnou,ynou,xx,ts) == 0) ok=0;
                if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
                        if((timp[xnou][ynou]>timp[x][y]+1 || timp[xnou][ynou]==-1) && ok)
                        {
                                timp[xnou][ynou]=timp[x][y]+1;
                                intr(xnou, ynou);
                        }
            }
    }
}
int main()
{
    init();
    lee();
    #ifdef cosmin
    for(int ii=1;ii<=n;ii++)
        {for(int jj=1;jj<=m;jj++)
                    cout<<gh[ii][jj]<<" ";
                cout<<"\n";}
    cout<<"\n";
    for(int ii=1;ii<=n;ii++)
                {for(int jj=1;jj<=m;jj++)
                    {for(int jjj=1;jjj<=M[ii][jj].du;++jjj) cout<<M[ii][jj].v[jjj]<<"a";
                    cout<<"   ";}
                cout<<"\n";}

    cout<<"\n";
    for(int ii=1;ii<=n;ii++)
                {for(int jj=1;jj<=m;jj++)
                    cout<<timp[ii][jj]<<" ";
                cout<<"\n";}
    #endif
    if (timp[e][m] == -1) cout<<"0\n"; //nu este cazul
    else cout<<timp[e][m]<<"\n";
    cin.close();
    cout.close();
    return 0;
}
