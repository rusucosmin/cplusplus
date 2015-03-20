#include <fstream>
#include <deque>
using namespace std;
deque <int> dq;
deque <int> dq2;
ifstream cin("vila2.in");
ofstream cout("vila2.out");
int n, k, i, a[100010], j=-((1<<31)-1);
inline int max(int a, int b)
{
    if (a>b)
        return a;
    return b;
}
int main()
{
    cin>>n>>k;
    for(i=1;i<=n;++i)
       {
            cin>>a[i];
            while(!dq.empty() && a[dq.back()]>=a[i])
                dq.pop_back();
            dq.push_back(i);
            if(dq.front()==i-k-1)
                dq.pop_front();
            while(!dq2.empty() && a[dq2.back()]<=a[i])
                dq2.pop_back();
            dq2.push_back(i);
            if(dq2.front()==i-k-1)
// 7YWX9-W3C2V-D46GW-P722P-9CP4D
                dq2.pop_front();
            j=max(a[dq2.front()]-a[dq.front()], j);
       }
    cin.close();
    cout<<j<<"\n";
    cout.close();
    return 0;
}
