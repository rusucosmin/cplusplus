#include <fstream>
#include<deque>
#include<math.h>
using namespace std;
deque<int>dq;
ifstream cin("secv4.in");
ofstream cout("secv4.out");
int i, n, x, y;
float sol=-((1<<31)-1);
float nr;
int p, l;
double s[100001];
bool semn[1000001];
double modul(double a)
{
    if(a<0) {
                semn[i]=1;
                return -a;}
    else return a;

}
int main()
{
    cin>>n>>x>>y;
    p=1; l=n;
    for(i=1;i<=n;++i)
    {
        cin>>nr;
        nr=modul(nr);
        s[i]=s[i-1]+log10(nr);
     //0   cout<<"s[i]"<<" "<<s[i]<<"\n";
        while(!dq.empty() && s[dq.back()]<=s[i] && s[i]<=0)
            dq.pop_back();
        dq.push_back(i);
        if(i-dq.front()>=y+1)
            dq.pop_front();
        if(i-dq.front()>=x-1)
            if(sol<(s[i]-s[dq.front()]))
                {
                    sol=s[i]-s[dq.front()];
                    p=dq.front();
                    l=i-dq.front()+1;
                    //cout<<i;
                }
     //   cout<<"sol"<<sol<<"\n";
    }

    cout<<p<<" "<<l<<"\n";
    cin.close();
    cout.close();
    return 0;
}
