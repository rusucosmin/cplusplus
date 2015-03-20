# include<fstream>
# include<deque>
using namespace std;
deque <int> deque_min, deque_max;
ifstream cin("secvdist.in");
ofstream cout("secvdist.out");
int n, k, a[1000005], i, j, st, dr;
int main()
{
    cin>>n>>k;
    for(i=1;i<=n;++i)
        {
            cin>>a[i];
            while(!deque_min.empty() && a[deque_min.back()]>=a[i])
                deque_min.pop_back();
            deque_min.push_back(i);
            while(!deque_max.empty() && a[deque_max.back()]<=a[i])
                deque_max.pop_back();
            deque_max.push_back(i);

        }
    cout<<st<<" "<<dr<<"\n";
    cin.close();
    cout.close();
    return 0;
}
