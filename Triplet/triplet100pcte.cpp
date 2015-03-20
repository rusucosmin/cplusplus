#include<fstream>
using namespace std;
ifstream cin("triplet.in");
ofstream cout("triplet.out");
long long n;




int main()
{
    cin>>n;
    if(n%2==0)                                                 
    cout<<(n/2)<<" "<<(-1)*((n/2)-1)<<" 1";
      
    else
    cout<<(n+1)/2<<" "<<(-1)*((n-1)/2)<<" 0";
    
        
    
    
    return 0;    
}    
