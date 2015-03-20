#include<fstream>
using namespace std;
ifstream cin("intervale2.in");
ofstream cout("intervale2.out");
long N;
long long A[100005];
long P[100005];
int main()
{
    int i, contor=0,j;
   cin>>N;
   for(i=1;i<=N;i++)
      cin>>A[i];  
   for(i=1;i<=N;i++)
      cin>>P[i];
      for(i=1;i<=N;i++)
         {contor=0;
                       for(j=P[i];j<i;j++)
             if(A[j]>A[i])
                contor++;
             cout<<contor<<" ";}
             
        
    return 0;
}
