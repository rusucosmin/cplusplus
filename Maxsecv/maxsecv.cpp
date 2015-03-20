#include<fstream>
using namespace std;
ifstream cin("maxsecv.in");
ofstream cout("maxsecv.out");
int i, j,cati_de_1[1000001],aux,suma;
bool x[1000001];
long long n;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
  {     cin>>x[i];
//    for(i=1;i<=n;i++)
      if(x[i]==0)
        {cati_de_1[i]=i-1-aux;
        aux=i;}}
    if(x[n]!=0)
         cati_de_1[n]=n-aux;
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            if(cati_de_1[i]<cati_de_1[j])
                 {aux=cati_de_1[i];    
                   cati_de_1[i]=cati_de_1[j];
                   cati_de_1[j]=aux;
                   }
   cout<<(cati_de_1[1]+cati_de_1[2])<<"\n";   
    return 0;
}
        
    
