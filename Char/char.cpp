#include<fstream>
using namespace std;

ifstream cin("iepuri.in");
ofstream cout("iepuri.out");
long long N, sol;
int i, j,T, A , B, C, unu, doi, trei;

int main()
{
    cin>>T;
    for(i=1;i<=T;i++)
    {                cin>>unu>>doi>>trei>>A>>B>>C>>N;   
                     sol=0;
                     for(j=1;j<=N-2;j++)
                     { sol=A*trei+B*doi+C*unu;
                        unu=doi;
                        doi=trei;
                        trei=sol; }
                        cout<<sol%666013<<"\n";
}
    
    cin.close();
    cout.close();
                                      
    return 0;
}
