#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream cin("interclasari.in");
ofstream cout("interclasari.out");

int t, n, s;
vector<int> v;

int main()
{
    for(cin >> t ; t ; --t)
    {
        int n;
        cin >> n;
        s += n;
        for(int i = 1 ; i <= n ; ++ i)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }
    }
    stable_sort(v.begin(), v.end());

    cout << s << "\n";
    for(vector<int> :: iterator i = v.begin(), gin = v.end(); i!=gin ; ++i)
        cout << *i << " ";
    cin.close();
    cout.close();
    return 0;
}
