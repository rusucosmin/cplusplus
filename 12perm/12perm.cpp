#include<fstream>
#define MOD  1048576
using namespace std;
ifstream cin("12perm.in");
ofstream cout("12perm.out");
int n, T[15000000];

int main ()
{

    cin>>n;
    T[1] = 1, T[2] = 2, T[3] = 6, T[4] = 12;
    for(int i=5;i<=n;i++)
    T[i] = (T[i - 1] + T[i - 3] + 2 * (i - 2)) & ( MOD - 1);
    cout<<T[n]<<"\n";   
                      
    
    
    
    
    
    return 0;
}
