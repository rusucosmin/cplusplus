#include<fstream>
#include<string.h>
using namespace std;
ifstream cin("compress.in");
ofstream cout("compress.out");
char S[100005];
long N, contor;
int main()
{
    cin.getline(S, 100005 );
    N=strlen(S);
    for(int i=1;i<=N;i++)
       {  if(S[i]==S[i-1])
            contor++;
          else 
            {cout<<S[i-1]<<contor+1;
            contor=0;}
           }   
    
    return 0;
}
