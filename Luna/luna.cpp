#include <fstream>

using namespace std;
typedef struct{
        int lat,lung;}
        DREPT;
        
DREPT calcul[10000][10000];
DREPT tari[5001];
int a[100][100],i,n,j,m;

ifstream fin("luna.in");
ofstream fout("luna.out");
int main()
{
    fin>>n>>m;
    
    for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
        {fin>>a[i][j];
        calcul[i][j].lat=calcul[i][j].lung=1;}
        
        for(j=2;j<=m;j++)
           if (a[i][j-1]==a[i][j]) calcul[i][j].lung=calcul[i][j-1].lung+1;
           
        
        for(i=2;i<=n;i++)
           if (a[i-1][j]==a[i][j]) calcul[i][j].lat=calcul[i-1][j].lat+1;
           
        
    for(i=2;i<=n;i++)
      for(j=2;j<=m;j++)
        {
        if (a[i][j]==a[i-1][j]) calcul[i][j].lat=calcul[i-1][j].lat+1;
        if (a[i][j-1]==a[i][j]) calcul[i][j].lung=calcul[i][j-1].lung+1;
        
    
        }
     
     
        int t;
        for(i=1;i<=n;i++)
           for(j=1;j<=m;j++)
             {t=a[i][j];

if ((calcul[i][j].lung>=tari[t].lung&&calcul[i][j].lat>=tari[t].lat)||
(calcul[i][j].lung>=tari[t].lat&&calcul[i][j].lat>=tari[t].lung))
             {tari[t].lung=calcul[i][j].lung;
             tari[t].lat=calcul[i][j].lat;
             }
             }
       int k,gasit; 
        fin>>k;
      int ii,jj,tara,lati,lungi;

    for(i=1;i<=k;i++)
     {fin>>tara>>lati>>lungi;
  if (tari[tara].lat==0&&tari[tara].lung==0)   fout<<"Tara de provenienta nu are parcele pe Luna!\n";
 
  else
    if ((tari[tara].lat>=lati&&tari[tara].lung>=lungi)||(tari[tara].lat>=lungi&&tari[tara].lung>=lati)) 
                                        fout<<"Cererea poate fi satisfacuta!\n";
              else  fout<<"Cererea nu poate fi satisfacuta!\n"; 
                                                          
     }      
return 0;
                          
}
