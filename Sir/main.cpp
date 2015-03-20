#include <fstream>
#include <deque>
using namespace std;

void solve();
void write();

deque <int> dq_min, dq_max;
int x, st, end, lenght=-((1<<31)-1);
int a[100005];
int main()
{
    solve();
    write();
    return 0;
}
void solve()
{
    ifstream cin("sir.in");
    cin>>n>>x>>y>>z;
    for(i=1;i<=n;++i)
    {
        cin>>a[i];
        while(!dq_min.empty() && a[dq_min.back()]>=a[i])
            dq_min.pop_back;
        while(!dq_max.empty() && a[dq_max.back()]<=a[i])
            dq_max.pop_back;
        dq_min.push_back(i);
        dq_max.push_back(i);
        if(i-dq_min.front()>=y+1)
            dq_min.pop_front();
        if(i-dq_max.front()>=y+1)
            dq_max.pop_front();
        if(i-dq_min.front()>=x-1 && i-dq_max.front()>=x-1)
            if(a[dq_max.front()-a[dq_min.front()]>=z)   //conditia enuntului
                //trebuie acum verificata lungimea maxima;
                if(lenght<)


    }
    cin.close();
}
void write()
{
    ofstream cout("sir.out");
    cout<<array_number;
}
