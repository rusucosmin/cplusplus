#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

ifstream cin("cpal.in");
ofstream cout("cpal.out");
int main()
{
    int iSecret, iGuess;

    srand (time(NULL));

    iSecret = rand() % 2 ;
    cout<<iSecret << "\n";

    cin.close();
    cout.close();
    return 0;
}
