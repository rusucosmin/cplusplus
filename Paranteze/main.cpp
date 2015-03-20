
#include <fstream>
#include<string.h>
#include<limits.h>
using namespace std;

ifstream cin("paranteze.in");
ofstream cout("paranteze.out");
char s[1000000], c[1000000];
int st[1000], i, n, j, pr, u, ul, maxi=INT_MIN;
int main()
{
    cin>>n;
    cin.getline(c, 10);
    cin.getline(s, n+1);
    int aux, bux;
    for(i=0;i<n;i++)
       {
           aux=pr;
           bux=ul;
         if( (s[i]=='(' && s[i+1]==')')  || (s[i]=='[' && s[i+1]==']') || (s[i]=='{' && s[i+1]=='}') )
         {
                    pr=i;
                    ul=i+1;
                    while((pr-1)>=0 && (ul+1)<=n-1 && ((s[pr-1]=='(' && s[ul+1]==')')  || (s[pr-1]=='[' && s[ul+1]==']') || (s[pr-1]=='{' && s[ul+1]=='}'))){
                    pr--;
                    ul++;
                    i=ul;
                    }
            //       cout<<pr<<" "<<ul;
                   if(pr==bux+1)
                      {maxi=maxi+(ul-pr+1);  }
                else
                   if((ul-pr+1)>maxi)
                       maxi=(ul-pr+1);

         }
}

    cout<<maxi;
    return 0;
}
