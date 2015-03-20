#include <fstream>

using namespace std;

ifstream cin("portal3.in");
ofstream cout("portal3.out");

struct pereche_portale{
int x1, y1, x2, y2, c;
}  a[4];
inline int abs(int X)
{
    if(X<0) return -X;
    return X;
}
inline int manhattan(int X1, int Y1, int X2, int Y2)
{
    return (abs(X1-X2)+abs(Y1-Y2));
}
int main()
{
    int t, n, m;
    cin>>t;
    for(;t;--t)
    {
        cin>>n>>m;
        int solution_locale=((1<<31)-1), solution=((1<<31)-1);
        for(int i=1;i<=3;++i)
            {
                cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2>>a[i].c;
                solution_locale=min( manhattan(0, 0, a[i].x1, a[i].y1) + manhattan(a[i].x2, a[i].y2, n, m) + a[i].c ,manhattan(0, 0, a[i].x2, a[i].y2) + manhattan(a[i].x1, a[i].y1, n, m) + a[i].c );
                cout<<manhattan(0, 0, a[i].x1, a[i].y1) + manhattan(a[i].x2, a[i].y2, n, m) + a[i].c<<" "<<manhattan(0, 0, a[i].x2, a[i].y2) + manhattan(a[i].x1, a[i].y1, n, m) + a[i].c<<"\n\n";

                cout<<"locale  "<<solution_locale<<" ";
                solution=min(solution_locale, solution);
            }
        cout<<solution<<"\n";
    }

    cin.close();
    cout.close();
    return 0;
}
