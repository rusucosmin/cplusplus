#include<fstream>
using namespace std;
ifstream cin("grigo.in");
ofstream cout("grigo.out");
long long N, M , i, x, rezultat=1;
bool v[1000001];
int main()
{
    cin>>N;//Permutari de N elemente;
    cin>>M;//Elementele care sunt vizibile
    for(i=1;i<=M;i++)
    {   cin>>x;
        v[x]=1;
    }
    cin.close();
    for(i=0;i<N;i++)
        if(v[i+1]==0)
               rezultat=rezultat*(i)%1000003;
    cout<<rezultat<<"\n";
    cout.close();
    return 0;
}
          
