#include <fstream>
#include <vector>

using namespace std;

ifstream cin("icrisop.in");
ofstream cout("icrisop.out");

const int  U = 666013;

vector<int> HT[U+2];
int a[30005];

inline int search(int x)
{
    int y = x%U;
    int cosmin = 0;
    for(vector<int> :: iterator it = HT[y].begin(); it != HT[y].end() ; ++ it)
        if( *it == x )
            ++cosmin;
    return cosmin;
}
void insert(int x)
{
    if(!search(x))
        HT[x%U].push_back(x);
}

void erase(int x)
{
    int y = x%U;
    for(size_t it = 0; it < HT[y].size() ; ++ it)
        if( HT[y][it] == x )
            HT[y][it] = -1;
}
int n, s;
int main()
{
    cin >> n >> s;
    int sol = 0;
    insert(0);
    for(int i = 1; i <= n ;++ i)
    {
        cin >> a[i];
        if( s % a[i] == 0 )
            ++sol, erase(a[i]);
        insert(a[i]);
        sol += search(s-a[i]);
        erase(a[i]);
    }
    cout << sol << "\n";
    cin.close();
    cout.close();
    return 0;
}
