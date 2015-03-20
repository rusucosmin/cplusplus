#include<fstream>
using namespace std;
long a, b, contor,nr_pare;
int main()
{
    ifstream cin("simpla.in");
    ofstream cout("simpla.out");
    cin>>a>>b;
    contor=b-a+1;
         nr_pare=contor/2;
    cout<<nr_pare;
    cin.close();
    cout.close();
    return 0;     
}
    
