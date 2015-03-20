#include <fstream>
using namespace std;
ifstream cin("citylog.in");
ofstream cout("citylog.out");
long n, m, t[1000005][3], i, j, curent, a, b, x, y ;
bool tip;
long current[]={0,1,1,1,1,3,0};
int main()
{
    //1 X yal y-lea;
    //0 y x
    j=0;
    cin>>n>>m;
    for(i=1;i<=m;i++) {
        cin>>tip>>a>>b;
        x=a^current[j];
        y=b^current[j];
      //  cout<<tip<<" "<<x<<" "<<y<<"\n";
        if(tip==0)
        {
            t[x][1]=y;
            t[x][2]=t[y][2]+1;
        }
        else {
            if(t[x][2]<y || y==0)
               cout<<"0\n";
            else cout<<" a\n";
            j++;}


    }
    return 0;
}
