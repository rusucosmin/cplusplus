#include<fstream>
using namespace std;
fstream cin("sir4.in");
ofstream cout("sir4.out");
long long A, B, M , Q, v[10000001], i,p;
int main()
{
    
    cin>>v[0]>>A>>B>>M>>Q;
    for(i=1;i<=Q;i++)
{       v[i]=(A * v[i-1] + B) % M;
}
    for(i=0;i<Q;i++)
   { cin>>p;
    cout<<v[p]<<" ";}
    cin.close();
    cout.close();
    return 0;
}
