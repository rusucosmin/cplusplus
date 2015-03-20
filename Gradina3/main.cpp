#include <fstream>
#define debug
using namespace std;

ifstream cin("gradina3.in");
ofstream cout("gradina3.out");

int n, p, k;
int s[1005][1005];
int sol1 = -((1<<31)-1) , sol2;
int main()
{
    cin >> n >> p >> k;
    for(int  i = 1, x, y ; i <= p ; ++ i)
        cin >> x >> y,
        s[x][y] = 1;
    for(int i = 1 ; i <= n ;++ i)
        for(int j = 1 ; j <= n ; ++ j)
            s[i][j] = s[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
    for(int i = k; i <= n ; ++ i)
        for(int j = k ; j <= n ; ++ j)
        {
            int variabila = s[i][j] - s[i-k][j] - s[i][j-k] +s[i-k][j-k];

            if(variabila > sol1)
                sol1 = variabila, sol2 = 1;
            else if (variabila == sol1)
                    ++sol2;
        }
    cout << sol1 << "\n" << sol2 << "\n";
    cin.close();
    cout.close();
    return 0;
}
