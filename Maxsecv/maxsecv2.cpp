#include<fstream>
using namespace std;
ifstream cin("maxsecv.in");
ofstream cout("maxsecv.out");
int i, aparitii,max1,max2;
bool x;
long long n;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
  {     cin>>x;
      if(x==0)
        {   if(aparitii>max1)
                 {max2=max1;
                 max1=aparitii;}
            else if(aparitii>max2)
                     max2=aparitii;
         aparitii=0;}
      else
          aparitii++;}
         cout<<(max1+max2)<<"\n";   
    return 0;
}
        
