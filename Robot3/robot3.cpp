#include<fstream>
#include<string.h>
using namespace std;
ifstream cin("robot3.in");
ofstream cout("robot3.out");
int n, m, l,c, i,j, a[1005][5005], b[5005],en;
char ch,x[100];
int main()
{
    cin>>n>>m>>l>>c;
    cin.getline(x,100);
    do
       { cin.get(ch);
          m--;
          if(ch=='N')
             b[i]=1;
          else if(ch=='S') b[i]=2;
          else if(ch=='E') b[i]=3;
          else if(ch=='V') b[i]=4; 
       }while(ch!=' ' && m>=0);
       for(i=1;i<=m;i++)
       cout<<b[i]<<" " ;
    for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
           cin>>a[i][j];
           
    en=a[l][c];
    i=1;
    while(en>=0 && i<=m )
       {
                if(b[i]==1)
                    l--;
                else if(b[i]==2)
                    l++;
                else if(b[i]==3)
                    c++;
                else c--;
                en=en+a[l][c]-1; 
                i++;
                cout<<l<<c<<en;
                }
    cout<<l<<" "<<c<<"\n";
    
    
    
    return 0;
}
