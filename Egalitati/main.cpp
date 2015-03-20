#include <fstream>
#include<string.h>
using namespace std;
ifstream in("egalitati.in");
ofstream out("egalitati.out");
char s[100005], st[100005];
bool ok=1;
int n, i, u, vf;
int main()
{
    in.getline(s, 100005);
    in.close();
    i=0;
    while(s[i])
    {
        if(s[i]=='(')
            ++u;
        else if(s[i]==')')
                if(u<1) ok=0;
                else
                    --u;
            else
                if(s[i]=='=')
                    {
                        if(u>0)
                            ok=0;
                        u=0;
                    }
                if(s[i]==';' || s[i]=='.')
                    {
                        if(u!=0)
                            ok=0;
                        out<<ok<<"\n";
                        ok=1;
                        u=0;
                    }
                if(s[i]=='.')
                    break;
        i++;
    }
    out.close();
    return 0;
}
