#include <fstream>
#include <limits.h>
using namespace std;
ifstream cin("ai.in");
ofstream cout("ai.out");
int n, l[1005][1005],contor, a[1005][1005], k,aux, auy, directie,q[3][1000009], i, j, u, p, ii, jj, t1, t2, s1, s2, s3, s4, r1, r2, r3, r4, l_max=INT_MIN;

void read();
void fill(int x, int y);
void lee();
inline int ab(int a)
{
    if(a<0)
        return -a;
    return a;
}
int main()
{
    read();
    cout<<l_max<<"\n";
    lee();
    return 0;
}
void lee()
{

}
void read()
{
    //T1 T2 S1 S2 S3 S4 R1 R2 R3 R4
    // t  - tinta
    // s  - sursa
    // r  - robotii
    cin>>n;
    cin>>t1>>t2>>s1>>s2>>s3>>s4>>r1>>r2>>r3>>r4;
    //-3 tinta care trebuie aparata
    l[t1][t2]=-3;
  //  m[t1][t2]=-3;
    //  Unde putem apara sursa :)
  //  for(i=1;i<=n;i++)
    //    for(j=1;j<=n;j++)
    a[s1][s2]=l[s1][s2]=a[s1][s2]=a[s3][s4]=l[s3][s4]=a[s3][s4]=-2;
    l[r1][r2]=a[r1][r2]=l[r3][r4]=a[r3][r4]=0;
    a[r3][r4]=a[r1][r2]=-1;
    cin>>k;
    for(i=1;i<=k;i++)
        {
            cin>>ii>>jj;
            a[ii][jj]=-4;
            l[ii][jj]=-4;
        }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i][j]==-4)
                {
                     fill(i, j);
                     l_max=max(contor, l_max);
                }
    q[1][1]=r1;
    q[2][1]=r2;
}
void fill(int x, int y)
{

    contor=0;
    while(a[x][y]==-4)
        {
            x--;
            contor++;
        }
    x=i;
    y=j;
    l_max=max(l_max, contor);
    contor=0;
    while(a[x][y]==-4)
        {
            x++;
            contor++;
        }
    x=i;
    y=j;
    l_max=max(l_max, contor);
    contor=0;
    while(a[x][y]==-4)
        {
            y--;
            contor++;
        }
    x=i;
    y=j;
    l_max=max(l_max, contor);
    contor=0;
    while(a[x][y]==-4)
        {
            y++;
            contor++;
        }
}
