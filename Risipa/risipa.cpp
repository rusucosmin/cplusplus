#include<fstream>
using namespace std;
ifstream cin("risipa.in");
ofstream cout("risipa.out");
int S, A, B, ziua[100004],suma[100004], i=1, j;
int main()
{
    cin>>S>>A>>B;
    suma[1]=S;
    ziua[1]=S;
    while(suma[S]!=2)
    {if(S%3==0)
           {i++;
           S=S-((2*S)/3);
           suma[S]++;
           ziua[i]=S;}
    else if( S%3==1 )
           { i++;
             S=S+(3*A)+2;
             suma[S]++;
             ziua[i]=S;
             }
    else 
    { i++;
      S=S+(3*B)+1;
      suma[S]++;
      ziua[i]=S;
      }}
   cout<<S<<"\n";
   for(i=1;i<=100023;i++)
      if(ziua[i]==S)
       cout<<i<<" ";
    return 0;
}
