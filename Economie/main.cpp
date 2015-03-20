#include<fstream>
#include<algorithm>
#define Valmax 50000
using namespace std;
ifstream f("economie.in");
ofstream g("economie.out");
int N, A[1001],S[50005],C[1001];
int main ()
{
 int i, j ,k;
 f>>N;
 for(i=1;i<=N;i++)
 f>>A[i];
 sort(A+1,A+N+1);
 k=0; S[0]=1;
 for(i=1;i<=N;i++){
   if(!S[A[i]])
        C[++k]=A[i];
   for(j=0; j+A[i]<=Valmax;j++)
        if(S[j])
            S[j+A[i]]=1;
}
g<<k<<endl;
for(i=1;i<=k;i++)
g<<C[i]<<endl;
return 0; }
