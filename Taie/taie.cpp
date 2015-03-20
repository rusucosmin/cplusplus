#include<fstream>
#include<iomanip>
using namespace std;
ifstream cin("taie.in");
ofstream cout("taie.out");
int N ;
double x1,y1,x2,y2,a[1005],b[1005];
int main()
{
    cin>>N;
    for(int i=1; i<=N;i++)
      {  cin>>x1>>y1>>x2>>y2;
      cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
         a[i]=(y1-y2)/(x1-x2);
         b[i]=y1-(x1*a[i]);
         cout<<a[i]<<" "<<b[i]<<"\n";
         }
    for(int i=1;i<N;i++)
      if(a[i]!=a[i+1] || b[i]!=b[i+1])
         {   cout<<"-1\n";
             return 0;
             }
    cout<<fixed<<setprecision(6)<<x1<<" "<<a[1]*x1+b[1]<<" "<<x2<<" "<<a[1]*x2+b[1]<<"\n";    
    cin.close();
    cout.close();   
    return 0;
}
