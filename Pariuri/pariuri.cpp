#include <fstream>
#include <tr1/unordered_map>
 
using namespace std;
using namespace tr1;
 
ifstream cin("pariuri.in");
ofstream cout("pariuri.out");
 
unordered_map<int, long long> Hash;
 
int main() {
    int N;
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int M;
        cin >> M;
        for(int j = 1 ; j <= M ; ++ j) {
            int time, value;
            cin >> time >> value;
            Hash[time] += value;
        }
    }
    cout << Hash.size() << '\n';
    for(unordered_map<int, long long> :: iterator it = Hash.begin() ; it != Hash.end() ; ++ it)
       cout << it->first << ' ' << it->second << ' ';
    return 0;
}
