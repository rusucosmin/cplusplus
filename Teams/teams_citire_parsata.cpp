#include<fstream>
#include<cstring>
#include <algorithm>
using namespace std;
int n, a[100001];
char s[1000005]; // trebuie mai mare deoarece ai 100.000 numere a cate 5 cifre max + spatii
int A,B,c,i,j;
 
int caz1(int b, int li) {
    int  ls=n, mij, fin;
    while( li<=ls) {
        mij=(li+ls)/2;
        if (a[mij]<=b) {
            fin=mij;
            li=mij+1;
        } else
            ls=mij-1;
    }
    return fin;
}
 
int caz2(int b, int li) {
    int ls=n,mij,fin;
    while(li<=ls) {
        mij=(li+ls)/2;
        if (a[mij]>=b) {
            fin=mij;
            ls=mij-1;
        } else
            li=mij+1;
    }
    return fin;
}
int N;
int main() {
    ifstream cin("teams.in");
    ofstream cout("teams.out");
    cin>>N>>A>>B;
    cin.getline(s,15);
    cin.getline(s,1000005);
    //cout << s << "\n";
    int aux = 0;
    n=0;
    for (i=0; (s[i] >= '0' && s[i] <= '9') || s[i] == ' '; ++i) {
        if (s[i]==' ') {
            a[++n]=aux;
            aux=0;
        } else
            aux=aux*10+s[i]-'0';
    }
    /*a[++n]=aux;
     for(i=1; i<=n; i++)
        cout<<a[i]<<" ";
    cout << "\n";
   if (n == N + 1) return -1;*/
 
    cin.close();
    sort (a + 1, a + n + 1);
    for(i=1; i<n; i++)
        if(a[i]+a[i+1]<=B)
            c+=caz1(B-a[i], i+1)-caz2(A-a[i], i+1)+1 ;
    cout<<c;
    cout.close();
    return 0;
}
