#include<fstream>
using namespace std;
long long b,n,r,p,MOD,k;
int main()
{
	ifstream cin("classictask.in");
	ofstream cout("classictask.out");
	cin>>n>>p>>MOD;
	for(r=1;p;p>>=1)
{
    if(p&1) r=r*p%k;
            n=n*p%k;
}
/*	for(b=n,r=1;p;p/=2)
		{
			if(p%2)
			r=(r*b)%MOD;
			b=(b*b)%MOD;
		}*/
	cout<<r<<"\n";
}
