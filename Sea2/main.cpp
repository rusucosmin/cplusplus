#include <stdio.h>
#include <set>
#include <utility>
using namespace std;

set< pair<int,int> > Ships;
set< pair<int,int> >::iterator It, It2, t;

int main()
{
    FILE *fi = fopen("sea2.in", "rt");
    FILE *fo = fopen("sea2.out", "wt");
    int x, y, nr;

    for (fscanf(fi, "%d", &nr); nr; nr--)
    {
        fscanf(fi, "%d %d", &x, &y);
        It = Ships.upper_bound(make_pair(x, y));
        if (It != Ships.end() && It->second > y)
        {
            fprintf(fo, "-1\n");
            continue;
        }
        if (Ships.size())
        {
            for (It2 = It; It2 != Ships.begin() && (--(t = It2))->second < y; It2 = t);
            Ships.erase(It2, It);
        }
        Ships.insert(make_pair(x, y));
        fprintf(fo, "%d\n", Ships.size());
    }
    fclose(fo);
    fclose(fi);
    return 0;
}
