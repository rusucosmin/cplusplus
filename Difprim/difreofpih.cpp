#include <fstream>
#include <bitset>
using namespace std;
ifstream cin("difprim.in");
ofstream cout("difprim.out");
bitset <10000005>ciur;
int main() 
{
    long long i,j,nr1=0,nr2=0,dif=0,a,b,sol=0,aux=0,bux=0, dif_precedenta;
    cin>>a>>b;
    for(i=2; i<=b; i++)
             for (j=i+i;j<=b;j=j+i)
                      ciur[j]=1;             
                
     cout<<-1<<"\n";
    
    cin.close();
    cout.close();
    return 0;
}
    
             
    
