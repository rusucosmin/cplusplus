#include <fstream>
///#define DEBUG
using namespace std;
ofstream cout("alee.in");

//    if(u>30625)
int main()
{
    cout<<175<<" ";
    cout<<30625-(175+175-1)<<"\n";
    for(int i=1;i<=175;i++)
         for(int j=1;j<=175;j++)
              if(i!=1 && j!=175)
                      cout<<i<<" "<<j<<"\n";
    cout<<1<<" "<<1<<" "<<175<<" "<<175<<"\n";
 ///   init();
    //lee();
   // afisare();
    return 0;
}
