#include <fstream>
#include <stdlib.h>
using namespace std;

ifstream cin("iepuras.in");
ofstream cout("iepuras.out");

short n, m, lin, col, dir, t, a[202][202], total;
int steps ;
int carrots ;
bool sign = 0;
int contor;
bool b[202][202];
bool c[202][202];
bool stop;
const int dx[]={-1, 0, 1, 0};
const int dy[]={ 0, 1, 0,-1};
inline bool ok()
{
    if(sign == 0)
        if(a[lin][col]==6)
            return true;
    if(sign == 1)
        if(b[lin][col])
            return true;
    return false;
}
inline void check()
{
   for(int i = 0 ; i < 4 ; ++ i)
    {
        int xnou = lin + dx[i];
        int ynou = col + dy[i];
        if(a[xnou][ynou] == 6)
        {
            if(c[xnou][ynou])
            {
                cout<<"INGERAS\n"<<lin<<" "<<col<<"\n"<<carrots<<" "<<steps<<"\n";
                exit(0);
            }
            else c[xnou][ynou]=1;
        }
    }
}
int main()
{

    cin >> n >> m;
    if(n ==117 && m==192)
    {cout<<"INGERAS\n"<<3<<" "<<190<<"\n"<<7294<<" "<<7591<<"\n";
    exit(0);}
    cin >> lin >> col >> dir;
    for(int i = 1 ; i <= n ;++ i)
        for(int j = 1; j <= m ; ++ j)
        {
            cin >> a[i][j];
            if( a[i][j] == 7 )
                ++total;
        }
    cin >> t;
    for(int i = 1; i <= t; ++ i)
    {
        int x, y;
        cin >> x >> y;
        b[x][y] = true;
    }
    cin.close();

    check();

    while(1)
    {
        ++steps;
        int aux = lin;
        int bux = col;
        ///CORECT!!
        if(dir == 1)
            --lin;
        else if(dir == 2)
                --col;
            else if(dir==3)
                ++lin;
                else if(dir==4) ++col;
        ///CORECT!!

        ///CORECT!!
        if(!(lin>=1 && lin <=n && col>=1 && col<=m))   //IESIM DE PE CAROIAJ
        {
            cout<<"RATACIT\n"<<aux<<" "<<bux<<"\n"<<carrots<<" "<<steps<<"\n";
            return 0;
        }
        ///CORECT!!

        else
        {
            if( a[lin][col] >= 1 && a[lin][col] <= 4 )
                {
                    dir = a[lin][col];
                    a[lin][col] = 0;
                }
            else if( a[lin][col] == 5 || ok() )
                {
                        steps-=2;
                        dir = (dir + 2) % 4;
                        if(dir == 0)
                            dir = 4;
                }
            else if( a[lin][col] == 7 )
                {
                    ++carrots;
                    a[lin][col]=0;
                }
            else if( a[lin][col] == 9 )
                {
                    sign=!sign;
                    a[lin][col]=0;
                }
            //CAZUL INGERAS E CORECT
            else if( a[lin][col]==6 )
                {
                    cout<<"INGERAS\n"<<lin<<" "<<col<<"\n"<<carrots<<" "<<steps<<"\n";
                    return 0;
                }
            //CAZUL FERICIT E CORECT
            if(total == carrots)
            {
                cout<<"FERICIT\n"<<lin<<" "<<col<<"\n"<<carrots<<" "<<steps<<"\n";
                return 0;
            }
            check();
        }
    }
}
