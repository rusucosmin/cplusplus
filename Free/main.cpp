//#include<iostream> //  free
#include<fstream>
#include<math.h>
using namespace std;
ifstream cin("free.in");
ofstream cout("free.out");
long long  n;
long double radical;
int main()
{
    cin>>n;
    radical=sqrt(n);
cout<<n-floor(radical);
//system("pause");
return 0;
}
