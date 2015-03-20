#include <fstream>

using namespace std;

ifstream cin("perle2.in");
ofstream cout("perle2.out");
int main()
{
    int n, k, bestSum=-((1<<31)-1), nr, sum=0;
    cin>>n; cin>>k;
    for(int i=1; i<=n; ++i)
        {
            cin>>nr;
            nr-=k;
            if(sum+nr>nr)
                sum+=nr;
            else sum=nr;
            if(sum>bestSum)
                bestSum=sum;
        }
    cout<<bestSum<<"\n";
    cin.close();
    cout.close();
    return 0;
}
