#include <fstream>

using namespace std;
int x, y, n, l, nr, a[55][55], ind, i, sol, aux;
int contor, xnou, ynou;
int x_st, y_st;
bool figura_perfecta=0;
const int dx[]={ 1, 0, -1, 0};
const int dy[]={ 0,-1, 0, 1};
ifstream cin("zona.in");
ofstream cout("zona.out");
void citire()
{
    cin>>x>>y>>n>>l;
    x_st=x;
    y_st=y;
    for(i=1;i<=l+1;++i)
        {
            cin>>nr;
            a[x][y]=i;
            if(nr==1)
                    x--;
                else if(nr==2)
                        y++;
                    else if(nr==3)
                        x++;
                        else y--;
            if(a[x][y]==1)
                figura_perfecta=1;
            if(a[x][y]!=0)
                {   aux=a[x][y];
                    sol=i-a[x][y]+1;
                break;}
            }
}
void fill(int X, int Y)
{
    if(a[X][Y]<aux)
    {
        contor++;
        a[X][Y]=aux+1;
        if(X-1>=0)
        fill(X-1, Y);
        if(Y-1>=0)
        fill(X, Y-1);
        if(X+1<=n)
        fill(X+1, Y);
        if(Y+1<=n)
        fill(X, Y+1);
    }
}
void fill2(int X, int Y)
{
    if(a[X][Y]==0)
    {
        a[X][Y]=-1;
        if(X-1>=0)
        fill2(X-1, Y);
        if(Y-1>=0)
        fill2(X, Y-1);
        if(X+1<=n)
        fill2(X+1, Y);
        if(Y+1<=n)
        fill2(X, Y+1);
    }
}
int main()
{
    citire();
    for(i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(a[i][j]==0)
                     {fill2(i, j); i=n+1, j=n+1;}
    for(i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(a[i][j]==0)
                 {
                     fill(i, j);
                     i=n+1;
                     j=n+1;
                 }
    cout<<sol<<"\n";
    cout<<contor+(sol/2)-1<<'\n';
    cin.close();
    cout.close();
    return 0;
}
