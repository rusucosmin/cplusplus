#include<fstream>   
using namespace std;
int i,j,n,m,s=-1,sl[2005],v[2005][2005],lungime,k,san;     
char a[20005],b[20005];
ifstream fin("edist.in");     
ofstream fout("edist.out");     
void citire(){     
fin>>n>>m>>k; 
san=m;    
for(i=1;i<=n;i++)     
fin>>a[i];
for(i=1;i<=m;i++)     
fin>>b[i];    

}     
int max(int a,int b){     
return (a>b)?a:b;     
}     
void din(){     
for(i=1;i<=n;i++)     
for(j=1;j<=m;j++)     
if(a[i]==b[j])     
v[i][j]=1+v[i-1][j-1];     
else     
v[i][j]=max(v[i-1][j],v[i][j-1]);     
i=n;     
j=m;     
   
     
}     
int main(){     
citire();     
din();  

lungime=san-v[n][m];  
fout<<lungime;

return 0;        
}
