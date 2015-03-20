#include <fstream>
#include <deque>
using namespace std;
deque <int> dq;
int N, C, x, rotatii, i;
ifstream cin("carti3.in");
ofstream cout("carti3.out");
int main()
{
    cin>>N>>C;
    for(i=1;i<=C;++i)
        {
            cin>>x;
            dq.push_back(x);
        }
  //  while(!dq.empty())
    //{
      //  cout<<dq.front()<<"\n";
       // dq.pop_front();
   // }
    for(i=1;i<=N;++i)
        {
            cin>>x;
            if(x==-1)
                rotatii++;
            else if(rotatii%2==0)
                    dq.push_front(x);
                else dq.push_back(x);
        }
    cin.close();
    if(rotatii%2==0)
    while(!dq.empty())
    {
        cout<<dq.front()<<"\n";
        dq.pop_front();
    }
    else
    while(!dq.empty())
    {
        cout<<dq.back()<<"\n";
        dq.pop_back();
    }
    cout.close();
    return 0;
}
