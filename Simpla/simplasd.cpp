#include<fstream>
using namespace std;
ifstream cin("simpla.in");
ofstream cout("simpla.out");
long long a, b;
int main()
{
    cin>>a>>b;
    cout<<((b-a)/2)+1;
    
    
    return 0;
}
