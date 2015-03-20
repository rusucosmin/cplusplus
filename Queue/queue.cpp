#include <fstream>
#include <stack>
#include <string.h>
#include <ctype.h>
using namespace std;
stack <int> stiva_intrare, stiva_iesire; //st1, st2
ifstream cin;
int n, i, j;
int nr;
char s[22];
ofstream cout("queue.out");
int main()
{
    cin.open("queue.in");
    cin>>n;
    cin.get();
    for(i=1;i<=n;++i)
    {
        cin.getline(s, 20);
        if(strstr(s, "push_back"))
            {
                j=10;
                nr=s[j]-'0';
                while(isdigit(s[++j]))
                    nr=nr*10+s[j]-'0';
                stiva_intrare.push(nr);
                cout<<i<<": read("<<nr<<") push(1,"<<nr<<")\n";
            }
        else{
        if(!stiva_iesire.empty())
            cout<<i<<": pop(2) write("<<stiva_iesire.top()<<")\n", stiva_iesire.pop();
        else{
            cout<<i<<":";
            while(stiva_intrare.size()>=2)
            {
                cout<<" pop(1) push(2,"<<stiva_intrare.top()<<")";
                stiva_iesire.push(stiva_intrare.top());
                stiva_intrare.pop();
            }
            cout<<" pop(1)";
            stiva_iesire.push(stiva_intrare.top());
            stiva_intrare.pop();
            cout<<" write("<<stiva_iesire.top()<<")\n";
            stiva_iesire.pop();
            }
        }
    }
    cin.close();
    cout.close();
    return 0;
}
