#include <fstream>
using namespace std;
int a[1000][1000],sarpe[1000000],u[1000][3],contor=0,n,m;
ifstream fin("sarpe2.in");
ofstream fout("sarpe2.out");

int valid(int ii,int jj,int p)
{
   if (ii<1||ii>n||jj<1||jj>n||a[ii][jj]!=sarpe[p])
               return 0;
   else
               return 1;
}
void back(int ii,int jj,int p)
//ii linia in matrice,jj coloana in matrice
//p nivelul in stiva
{   int pval;
    for(pval=1;pval<=8;pval++)
    {  if (valid(ii+u[pval][1],jj+u[pval][2],p+1))
              if (p+1==m)
               contor++;
               else
               back(ii+u[pval][1],jj+u[pval][2],p+1);          }
}
void citire()
{    int i,j;
     fin>>n>>m;
     for(i=1;i<=m;i++)
         fin>>sarpe[i];
     for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
         fin>>a[i][j];
}
int main()
{
    citire();
    u[1][1]=-1;   u[1][2]=0;
    u[2][1]=-1;   u[2][2]=1;
    u[3][1]=0;    u[3][2]=1;
    u[4][1]=1;    u[4][2]=1;
    u[5][1]=1;    u[5][2]=0;
    u[6][1]=1;    u[6][2]=-1;
    u[7][1]=0;    u[7][2]=-1;
    u[8][1]=-1;   u[8][2]=-1;

    int i,j;
        for(i=1;i<=n;i++)
                         for(j=1;j<=n;j++)
                                               if (a[i][j]==sarpe[1])   back(i,j,1);
    fout<<contor;
    fout.close();
    fin.close();
    return 0;
}
