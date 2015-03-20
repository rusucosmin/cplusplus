#include <fstream>

using namespace std;

ifstream cin("drepte2.in");
ofstream cout("drepte2.out");
int main()
{
    int n;
    cin >> n;
    cin.close();
    int a = 1 ;
    for(int i = 1 ; i <= n ; ++ i)
        a += i;
    cout << a <<"\n";
    cout.close();
    return 0;
}
