#include <fstream>
#include <deque>
using namespace std;
deque <double> dq;
ifstream cin("secv3.in");
ofstream cout("secv3.out");
double cost[1005];
short timp[1005], n, l, u, i;
double sol=-((1<<31)-1);
int main()
{
    cin>>n>>l>>u;
    for(i=1;i<=n;++i)
        {
            cin>>cost[i];
            cost[i]+=cost[i-1];
        }
    for(i=1;i<=n;++i)
        {
            cin>>timp[i];
            timp[i]+=timp[i-1];
        }
    for(i=1;i<=n;++i)
        {
            while(!dq.empty() && (double)dq.back()>=(double)(cost[i]/timp[i]))
                dq.pop_back();
            dq.push_back(cost[i]/timp[i]);
            if((double)(cost[i]/timp[i])-dq.front()==(double)(cost[u+1]/timp[u+1]))
                dq.pop_front();
            if((double)(cost[i]/timp[i])-dq.front()==(double)(cost[u+1]/timp[u+1]))
                { sol=max(sol,dq.front());
             //       if(aux!=sol)
               //         cout<<i<<" ";
                }

         //   cout<<"dq.fornt()="<<i-dq.front()<<" ";

        }
    cout<<sol<<"\n";
    cin.close();
    cout.close();
    return 0;
}
