#include <fstream>
#include <bitset>
using namespace std;

ifstream cin("magicnum.in");
ofstream cout("magicnum.out");
int ciur[1000010];
int main()
{
    int x, y, i, j, contor=0;
    cin>>x>>y;
    for(i=2;i<=y;i++)
        for(j=i+i;j<=y;j+=i)
            ciur[j]++;

    ciur[1]=-1;
    for(i=x;i<=y;i++)
        if(i%(ciur[i]+2)==0)
            contor++;
    cout<<contor<<"\n";
    return 0;
}
