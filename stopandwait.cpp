
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Returns 1 if frame is lost
int lost()
{
    return rand() % 2 == 0;
}

// Stop and Wait ARQ
void stopWait(int n)
{
    cout << "\n--- Stop and Wait ARQ ---\n";

    for(int i = 1; i <= n; i++)
    {
        cout << "Sending Frame " << i << endl;

        while(lost())
        {
            cout << "Frame " << i << " lost\n";
            cout << "Retransmitting Frame " << i << endl;
        }

        cout << "Frame " << i << " received\n";
        cout << "ACK " << i << " received\n";
    }
}

int main()
{
    srand(time(0));

    int n;

    cout << "Enter number of frames: ";
    cin >> n;

    stopWait(n);

    return 0;
}
