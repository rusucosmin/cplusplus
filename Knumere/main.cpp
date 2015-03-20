#include <fstream>
#include <deque>
#include <cassert>

using namespace std;

deque <int> dq;
int n, k, a[1000005], v[1000005], sol = ((1<<31)-1), l;
int main()
{
    ifstream cin("knumere.in");
    ofstream cout("knumere.out");

    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> a[i];
    for(int i = 1 ; i < n ; ++ i)
        v[i] = a[i+1]-a[i];
    l = n - k - 1;
    for(int i = 1 ; i < n ; ++ i)
    {
        if( i - dq.front() >= l - 1 && !dq.empty())
            dq.pop_front();
        while(!dq.empty() && v[dq.back()] < v[i])
            dq.pop_back();
        dq.push_back(i);
        if ( i >= l + 1 ) {
            assert(dq.front() >= 0);
            if(sol > v[dq.front()])
                sol = v[dq.front()];
        }
    }
    if(sol != ((1<<31)-1))
        cout << sol << "\n";
    else cout <<"-1\n";
    return 0;
}
