#include <fstream>

using namespace std;

ifstream cin("1234.in");
ofstream cout("1234.out");

short n, m;
const int numbers[]={97, 129, 100, 141};
//const int dif[]={5, 10};
bool a[155][155];
int contor;
void fill(int x, int y)
{
    if(a[x][y]==1){
        a[x][y]=0;
        ++contor;
        if(x>1 && y>1)
            fill(x-1, y-1);
        if(x<n && y<m)
            fill(x+1, y+1);
        if(x>1 && y<m)
            fill(x-1, y+1);
        if(x<n && y>1)
            fill(x+1, y-1);
        if(x>1)
            fill(x-1, y);
        if(x<n)
            fill(x+1, y);
        if(y>1)
            fill(x, y-1);
        if(y<m)
            fill(x, y+1);
    }
}
int main()
{
    char x;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
                cin.get(x);
                if(x=='\n') cin.get(x);
                if(x=='1') a[i][j]=0;
                else a[i][j]=1;
        }
    int ok=0;
    bool semn=1;
    int first=0, second=0;
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j)
        {
            if(a[j][i]==1){
                contor=0;
                fill(j, i);
                if(contor==24)
                    ok=1;
                else if(contor==96) //plus
                    ok=2;
                else if(contor==52) //egal
                    {
                        if(ok==2)
                            cout<<second+first;
                        else cout<<second-first;
                        return 0;
                    }
                else
                if(ok!=0)
                    {for(int ii=0;ii<4;++ii)
                        if(numbers[ii]==contor){
                            first=first*10+(ii+1);
                            break;
                        }}
                else {for(int ii=0;ii<4;++ii)
                        if(numbers[ii]==contor){
                            second=second*10+(ii+1);
                            break;
                        }}

            }}
    if(ok==2) cout<<second+first;
    else cout<<first-second;
    cin.close();
    cout.close();
    return 0;
}
