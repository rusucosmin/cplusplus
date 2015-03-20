/*
    Ciclu hamiltonian = functia cost;
    Greedy...
*/

#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>
using namespace std;

ifstream cin("orase.in");
ofstream cout("orase.out");

const int oo = (1<<31)-1;

int a[105][105], n, costmin = oo;

vector<int> V, noduri;
bitset<105> viz;

int cost(int start)
{
    int returnare = 0;
    for(int i = 1 ; i <= n ;++ i)
        viz[i] = false;
    noduri.clear();
    noduri.push_back(start);
    viz[start] = true;
    for(int i = 1 ; i < n ; ++ i)
    {
        int costminim = oo;
        int node = noduri[i-1];
        int newnode;
        for(int j = 1 ; j <= n ; ++ j)
            if(!viz[j] && a[node][j] != 0 )
                    if ( costminim > a[node][j] )
                    {
                        costminim = a[node][j];
                        newnode = j;
                    }
        viz[newnode] = true;
        noduri.push_back(newnode);
        returnare += costminim;
    }
    noduri.push_back(noduri[0]);
    return returnare;
}

int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ;++ j)
            cin >> a[i][j];

    for(int i = 1 ; i <= n ; ++ i)
    {
        int costnow = cost(i);
        if( costnow < costmin )
        {
            costmin = costnow;
            V = noduri;
        }
    }
    cout << costmin << "\n";
    for(vector <int> :: iterator it = V.begin(), fin = V.end(); it != fin ; ++ it)
        cout << *it << " ";
    return 0;
}
