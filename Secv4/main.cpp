#include <fstream>
#include <math.h>
#include <deque>
using namespace std;
deque <int> dq;
ifstream cin("secv4.in");
ofstream cout("secv4.out");
int n, x, y, nr, a[100005], s[100005], i, j;
int main()
{
    cin>>n>>x>>y;
    for(i=1;i<=n;++i)
        {
            cin>>nr;
            a[i]=log10(nr);
            s[i]=nr;
            cout<<s[i]<<" ";
        }
    for(i=1;i<=n;++i)
        {
            while(!dq.empty() && s[dq.back()]<=s[i-x])
                dq.pop_back();
            dq.push_back(i-x);
            if(dq.front()==i-y)
                dq.pop_front();
            cout<<s[dq.front()]<<" ";
        }
    cin.close();
    cout.close();
    return 0;
}
