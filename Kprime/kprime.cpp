#include<fstream>
#include<bitset>
using namespace std;
ifstream cin("kprime.in");
ofstream cout("kprime.out");
bitset <1005> ciur;
int n, a[100005], i, S[100005], k, j, nr, q;
int main()
{
    S[0]=0;
    ciur[1]=1;
    //fac ciurul pana la 1001;
    for(i=2;i<=1001;++i)
        if(ciur[i]==0)
            for(j=i+i; j<=1001; j+=i)
               ciur[j]=1; 
    cin>>n>>k;
    for(i=1;i<=n;++i)
        { cin>>a[i];
          if(ciur[a[i]]==0)
               S[++q]=i; 
              }
        S[q+1]=n+1;
  for (i = 1; i <= q; i++)
        j = i + k - 1, nr += (S[i] - S[i - 1]) * ( S[j + 1] - S[j]) > 0 ?(S[i] - S[i - 1]) * ( S[j + 1] - S[j]) : 0 ;
	cout<<nr<<"\n";
    return 0;
}
