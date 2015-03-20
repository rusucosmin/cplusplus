#include<fstream>
using namespace std;
unsigned long N, forta[100001], v[10000], sol;
unsigned int A,B,c,i,j;
int main()
{
    ifstream cin("teams.in");
    ofstream cout("teams.out");
    cin>>N>>A>>B;
    for(i=1;i<=N;i++)
    cin>>forta[i];
    cin.close();
    for(i=1;i<=N;i++)
      // for(j=i+1;j<=N;j++)
       //    if((forta[i]+forta[j])>=A && (forta[i]+forta[j])<=B)
         //     c++;
         if(forta[i]<=i)
           v[i]++;
    for(i=1;i<=N;i++)
     if(i>=A && i<=B)
       sol=sol+v[i];
    cout<<sol;
    cout.close();
    return 0;
}
