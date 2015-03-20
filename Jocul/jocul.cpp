#include<fstream>
using namespace std;
int main()
{
    int min,i, n, a[1005],r1,r2, s[1005];
    ifstream in("jocul.in");
    ofstream out("jocul.out");
    in>>n;
    for(i=1;i<=n;i++)
    in>>a[i];
    for(i=1;i<=n;i++)
    s[i]=s[i-1]+a[i];
    
        out<<s[n/2]<<"\n"<<s[n]-s[n/2];
    return 0;
}
