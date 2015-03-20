#include<fstream>
#include<iostream>
using namespace std;
  
int a[1005][1005],i,j,ok,u,p,P,q[3][10005],c,d,y,m,sir[3][10005],maxi,l[1005][1005],n,k=0;
ifstream fin("pescari.in");
ofstream g("pescari.out");
  
void init()
  
{
       
     //citim datele din fisierul pescari.in
     fin>>n>>m>>P;
   //  cout<<n;
      for(i=1;i<=n;i++)
             for(j=1;j<=m;j++)
            { fin>>a[i][j];
              l[i][j]=0;
              if(a[i][j]==2) {l[i][j]=0;k++;sir[1][k]=i;sir[2][k]=j;}
            }
             fin.close();     
}
//instroduc linia c si col d in coada
void intr(int c,int d)
{
     u=u+1;
      if(u>20000)
       u=1;
         
       q[1][u]=c;
       q[2][u]=d;
} 
//extrag un element din coada
void extr(int &c,int &d)
{
     p=p+1;
     if(p>20000)
     p=1;
       
     c=q[1][p];
     d=q[2][p];
}
  
//algoritmul LEE
void lee(int x,int y)
{
     p=0;u=0;
     intr(x,y);
     while(p!=u)
    { extr(x,y);
     
   //vecinul de sus 
   //daca are inaltime mai mare si numarul de catarari mai mic atunci
   //actualizez numarul de catarari cu l[x][y]+1
     if(x>1)
       
      if(a[x-1][y]==0 || a[x-1][y]==1)
       if((l[x-1][y]>l[x][y]+1||l[x-1][y]==0))
       {
                                       l[x-1][y]=l[x][y]+1;
       intr(x-1,y);
  
      }
       
     //
      if(x<n)
       if(a[x+1][y]==0 || a[x+1][y]==1)
        if(l[x+1][y]>l[x][y]+1||l[x+1][y]==0)
        {l[x+1][y]=l[x][y]+1;
         intr(x+1,y);
   
         }
  
    if(y>1)
     if(a[x][y-1]==0 || a[x][y-1]==1)      
           if(l[x][y-1]>l[x][y]+1 || l[x][y-1]==0)
           {l[x][y-1]=l[x][y]+1;
                                  intr(x,y-1);
 
                                  }
    if(y<m)
     if(a[x][y+1]==0 || a[x][y+1]==1)
      if(l[x][y+1]>l[x][y]+1||l[x][y+1]==0)
    {l[x][y+1]=l[x][y]+1;
    intr(x,y+1);
    
    }
    if(y<m && x<n)
     if(a[x+1][y+1]==0 || a[x+1][y+1]==1)
      if(l[x+1][y+1]>l[x][y]+1||l[x+1][y+1]==0)
    {l[x+1][y+1]=l[x][y]+1;
    intr(x+1,y+1);}
    if(y>1 && x<n)
     if(a[x+1][y-1]==0 || a[x+1][y-1]==1)
      if(l[x+1][y-1]>l[x][y]+1||l[x+1][y-1]==0)
    {l[x+1][y-1]=l[x][y]+1;
    intr(x+1,y-1);}
     
    if(y<m && x>1)
     if(a[x-1][y+1]==0 || a[x-1][y+1]==1)
      if(l[x-1][y+1]>l[x][y]+1||l[x-1][y+1]==0)
    {l[x-1][y+1]=l[x][y]+1;
    intr(x-1,y+1);}
     
    if(y>1 && x>1)
     if(a[x-1][y-1]==0 || a[x-1][y-1]==1)
      if(l[x-1][y-1]>l[x][y]+1||l[x-1][y-1]==0)
    {l[x-1][y-1]=l[x][y]+1;
    intr(x-1,y-1);
    
    }
      
}
  
}
void scriere()
{ 
   
      for(i=1;i<=n;i++)
                     {  for(j=1;j<=m;j++)
                          g<<l[i][j]<<" ";
                         g<<"\n";
                         }
}
int main()
{
   
    init();
    for(i=1;i<=k;i++)
     lee(sir[1][i],sir[2][i]);
      
     scriere();
    
    return 0;
}
