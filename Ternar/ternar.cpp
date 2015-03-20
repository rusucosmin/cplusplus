#include<fstream>
using namespace std;
ifstream cin("ternar.in");
ofstream cout("ternar.out");
int n, m,i,j,aux=-1,bux=-1,cux=-1,dux=-1,fux, a[1239][1239],min_i,max_i,min_j,max_j,k,jj;
int check(int A, int b, int c, int d)
{     int i;           for(i=A-1;i<=c+1;i++)
                               if(a[i][b-1]!=1 || a[i][d+1]!=1)
                                    return 0;
                       for(i=b-1;i<=d+1;i++)
                               if(a[A-1][i]!=1 || a[b+1][i]!=1)
                                    return 0;
                       return 1;
     }


int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
                     for(j=1;j<=m;j++)
                                      cin>>a[i][j];
    fux=2;
    for(i=fux;i<=n;i++)
                    for(j=2;j<=m;j++)
                                      if(a[i][j]==2)
                                      {          min_i=max_i=i;
                                                 min_j=max_j=j;
                                                 k=i+1; jj=j+1;
                                                                             while(a[k][jj]==2 && a[k-1][jj]==2 && a[k][jj-1]==2)
                                                                            { max_i=k;
                                                                              max_j=jj;
                                                                              k++;
                                                                              jj++;
                                                                              }
                                                                            if(check(min_i,max_i,min_j,max_j))
                                                                             {     if((max_i-min_i)<(bux-aux) && (max_j-min_j)<(dux-cux))        
                                                                                             {   min_i=aux; max_i=bux; min_j=cux; max_j=dux;}}
                                                                            else {aux=min_i; bux=max_i, cux=min_j;dux=max_j;
                                                                              fux=max_i+1;} } 
    cout<<aux<<" "<<cux<<"\n"<<bux<<" "<<dux;
    cout<<a[aux][cux]<<" "<<a[bux][dux]<<"\n";                                                                              
                                                                           
    
    return 0;
}
