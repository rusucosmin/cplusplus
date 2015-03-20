#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>
#include <set>
 
using namespace std;
 
ifstream cin("loto.in");
ofstream cout("loto.out");
 
const int MAXN = 105;
const int oo = (1<<31)-1;
 
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
 
int N, S;
set<int> mySet; // niceone
int s[MAXN];
 
inline void debug(int x){
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i ; j <= N ; ++ j)
            for(int k = j ; k <= N ; ++ k)
                if(s[i] + s[j] + s[k] == x)
                    cout << s[i] << " " << s[j] << " " << s[k] << " ";
}
int main()
{
    cin >> N >> S;
    for(int i = 1;  i <= N ; ++ i)
        cin >> s[i];
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i ; j <= N ; ++ j)
            for(int k = j ; k <= N ; ++ k)
                mySet.insert(s[i] + s[j] + s[k]);
    for(set<int> :: iterator it = mySet.begin(), fin = mySet.end() ; it != fin ; ++ it){
        if( mySet.find(S-*it) != mySet.end() ){
 
            debug(S-*it);
            debug(*it);
            cin.close();
            cout.close();
            return 0;
        }
    }
    cout << "-1\n";
    cin.close();
    cout.close();
    return 0;
}
