#include <fstream>
using namespace std;
bool are[22509], vizitat[151][151];
int key[151][151], poz[151][151];
int n, m, k, i, j, nr;
struct punct{
    int i, j;
};
punct act, vx[22509];
int nb;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int main()
{
    ifstream f("castel.in");
    ofstream g("castel.out");
    f>>n>>m>>k;
    are[k]=1;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            nr++;
            poz[i][j]=nr;
            if(nr==k)
            {
                nb++;
                act.i=i;
                act.j=j;
                vx[nb]=act;
                vizitat[act.i][act.j]=1;
            }
            f>>key[i][j];
        }
    }
    bool ok=true;
    while(ok)
    {
        ok=false;
        for(i=1; i<=nb; i++)
        {
            for(j=0; j<4; j++)
            {
                if(!vizitat[vx[i].i+dx[j]][vx[i].j+dy[j]] && are[key[vx[i].i+dx[j]][vx[i].j+dy[j]]])
                {
                    nb++;
                    act.i=vx[i].i+dx[j];
                    act.j=vx[i].j+dy[j];
                    vx[nb]=act;
                    are[poz[act.i][act.j]]=1;
                    vizitat[vx[i].i+dx[j]][vx[i].j+dy[j]]=1;
                    ok=true;
                }
            }
        }
    }
    g<<nb;
}
