#include<fstream>
#include<math.h>
using namespace std;
ifstream cin("triplet.in");
ofstream cout("triplet.out");
long long  n;
double r, q;

int main()
{ cin>>n;
  r=sqrt(n);
  if(powl(floor(r),2)==n)
      cout<<r<<" 0 0";
  else 
  if(n>0)
  { q=sqrt((n-2)/3);
    if(q*q==(n-2)/3)
      cout<<(q-1)<<" "<<q<<" "<<(q+1);
  }
  else
  {n=-n;
        q=sqrt((n-2)/3);
    if(q*q==(n-2)/3)
      cout<<-(q-1)<<" "<<-q<<" "<<-(q+1);
  }
return 0;
}
