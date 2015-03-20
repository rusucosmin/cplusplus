#include<fstream>
using namespace std;
ifstream cin("pescari.in");
ofstream cout("pescari.out");
int i, j, k, n, m, p,u, a[10005][10005], q[3][10005], sir[3][10005], l[1005][1005];
void init(){
     cin>>n>>m>>p;
     for(i=1;i<=n;i++)
                      for(j=1;j<=m;j++)
                                       { cin>>a[i][j];
                                         l[i][j]=0;
                                    ////   if(a[i][j]==1)
                                        //  l[i][j]=1;
                                         if(a[i][j]==2)
                                         {//             l[i][j]=0;
                                                       k++;
                                                       sir[1][k]=i;
                                                       sir[2][k]=j;
                                                       } 
                                        }
     }
void extr(int &c, int &d)
{
     p=p+1;
     if(p>20000)
     p=1;
     c=q[1][p];
     d=q[2][p];
}
void intr(int c, int d)
{
     u=u+1;
     if(u>20000)
     u=1;
     q[1][u]=c;
     q[2][u]=d;
     }
void lee(int x, int y)
{
     p=0;
     u=0;
     intr(x, y);
     while(p!=u)
     {   extr(x,y);
         if(x>1)
            if(a[x-1][y]==0||a[x-1][y]==1)
                if(l[x-1][y]>l[x][y]+1 || l[x-1][y]==0)
                    { l[x-1][y]=l[x][y]+1;
                    intr (x-1,y);}
         if(y>1)
            if(a[x][y-1]==0||a[x][y-1]==1)
                if(l[x][y-1]>l[x][y]+1 || l[x][y-1]==0)
                    { l[x][y-1]=l[x][y]+1;
                    intr (x,y-1); }
         if(y<m)
            if(a[x][y+1]==0||a[x][y+1]==1)
                if(l[x][y+1]>l[x][y]+1 || l[x][y+1]==0)
                    { l[x][y+1]=l[x][y]+1;
                      intr (x,y+1);}
         if(x<n)
            if(a[x+1][y]==0||a[x+1][y]==1)
                if(l[x+1][y]>l[x][y]+1 || l[x+1][y]==0)
                    { l[x+1][y]=l[x][y]+1;
                       intr(x+1, y);}
         if(y>1 && x>1)
            if(a[x-1][y-1]==0||a[x-1][y-1]==1)
                if(l[x-1][y-1]>l[x][y]+1 || l[x-1][y-1]==0)
                    { l[x-1][y-1]=l[x][y]+1;
                      intr (x-1,y-1);}
         if(y>1 && x<n)
            if(a[x+1][y-1]==0||a[x+1][y-1]==1)
                if(l[x+1][y-1]>l[x][y]+1 || l[x+1][y-1]==0)
                    {l[x+1][y-1]=l[x][y]+1;
                     intr (x+1,y-1);}
         if(y<m && x<n)
            if(a[x+1][y+1]==0||a[x+1][y+1]==1)
                if(l[x+1][y+1]>l[x][y]+1 || l[x+1][y+1]==0)
                    { l[x+1][y+1]=l[x][y]+1;
                    intr (x+1,y+1);}
         if(y<m && x>1)
            if(a[x-1][y+1]==1||a[x-1][y+1]==0)
                if(l[x-1][y+1]>l[x][y]+1 || l[x-1][y+1]==0)
                    { l[x-1][y+1]=l[x][y]+1;       
                      intr (x-1,y+1);}
                
                
                }
}
void afisare()
{
     for(i=1;i<=n;i++)
        { for(j=1;j<=m;j++)
           cout<<l[i][j]<<" ";
           cout<<"\n";}
     
     }
int main()
{
    init();    
    for(i=1;i<=k;i++)
                     lee(sir[1][i], sir[2][i]);
    afisare();
    return 0;
}
