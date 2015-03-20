#include<fstream>
//#include<iostream>
using namespace std;
ifstream cin("rucsac2.in");
ofstream cout("rucsac.out");
int n,Cmax[305],S,k, Gmax,i,j,g[102], c[101],uz[305][105];
int main()
{
 cin>>n>>Gmax;
 for(i=1;i<=n;i++)
 cin>>g[i];
 for(i=1;i<=n;i++)
 cin>>c[i];
 for(S=1;S<=Gmax;S++)
                     Cmax[S]=-1;
 for(S=1;S<=Gmax;S++)
                     for(i=1;i<=n;i++)
                                      if(g[i]<=S && Cmax[S-g[i]]!=-1 && !uz[S-g[i]][i])
                                                 if(Cmax[S]<c[i]+Cmax[S-g[i]])
                                                 { Cmax[S]=c[i]+Cmax[S-g[i]];
                                                   for(k=1;k<=n;k++)
                                                                    uz[S][k]=uz[S-g[i]][k];
                                                   uz[S][i]=1;}
                                                   
if(Cmax[Gmax]==-1)
cout<<"imposibil";
else {cout<<Cmax[Gmax]<<endl; 
                 for(k=1;k<=n;k++)
                        if(uz[Gmax][k])
                        cout<<k<<" ";
                                   }

 
   
 
    
    
    
 return 0;   
}
