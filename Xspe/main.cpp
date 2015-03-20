#include <fstream>
//#include <vector>
using namespace std;
//vector <int> ST;
ifstream cin("xspe.in");
ofstream cout("xspe.out");
int st[1000005],n, s[1000005],sol[1000005], i, vf;
int main()
{
    cin>>n;
    for(i=1;i<=n;++i)
        cin>>s[i];
    for(int i=n; i>=1; --i) {
        sol[i]=s[i];
        for(;vf && st[vf]>=s[i];--vf);
        if(vf) sol[i]+=st[vf];
        st[++vf]=s[i];
    }
    for(i=1;i<=n;++i)
        cout<<sol[i]<<" ";
    cin.close();
    cout.close();
    return 0;
}
