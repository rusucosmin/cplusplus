
#include <fstream>
using namespace std;
ifstream cin("numar.in");
ofstream cout("numar.out");
long long i, n, inceput, s, k, a[500000], b[500000];
int main()
{
    cin >> n;
    s=n;
    while(i<=(n/2)+1)
    {
        s=0;
        inceput=i;
        do
        {
            s+=inceput;
            ++inceput;
        }
        while(s<n && inceput<=((n/2)+1));
        if(s==n)
            {
                k++;
                a[k]=i;
                b[k]=inceput-i;
            }
         //   cout<<s<<" "<<i<<" "<<inceput<<"\n";
        i++;
    }
    int ok=k;
    for(i=k;i>=1;--i)
        {
            cout<<a[i]<<" "<<b[i]<<"\n";
            ok++;
            a[ok]=1-a[k-i+1];
            b[ok]=b[k-i+1]+1+(a[k-i+1]-1)*2;
        }
    for(i=k+1;i<=ok;i++)
        cout<<a[i]<<" "<<b[i]<<"\n";
    cout<<-(n-1)<<" "<<2*n<<"\n";
    return 0;
} /*
#include <fstream>
#include <iostream>
using namespace std;

int n;

int gauss(int n) {
    if(n>=0) return n*(n+1)/2;
    else return n*(n-1)/-2;
}

int sum(int a,int b) {
    int ret=0;
    for(int i=a; i<=b; ++i) ret+=i;
    return ret;
}

int main()
{
    ifstream f("numar.in");
    ofstream g("numar.out");
    f>>n;
    for(int i=1; i*i<=n; ++i) if(0==n%i) {
        int sum=n/i;
        g<<2*i<<' ';
    }
    return 0;
} */
