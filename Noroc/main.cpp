#include <fstream>
#include <iomanip>
#include <stdio.h>
using namespace std;

ifstream cin("noroc.in");
ofstream cout("noroc.out");
long double x, m, res;
int main()
{
   //  freopen("noroc.out","w",stdout);
    cin>>x>>m;
  //  if((double)(1-(double)(x/m))<0)
//        cout<<0.0000000<<"\n";
 //   else
 {
     if(x>m){
        cout<<fixed<<setprecision(7)<<(float)0<<"\n"; return 0;}
else
 res=(long double)(1-(long double)(x/m));
    cout<<fixed<<setprecision(7)<<res<<"\n";
//    printf("%.7Lf", res);
}
    cin.close();
cout.close();
    return 0;
}
