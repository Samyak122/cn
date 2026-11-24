
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Returns 1 if frame is lost
int lost()
{
    return rand() % 2 == 0;
}

// Go-Back-N ARQ
void goBackN(int n, int w)
{
    cout << "\n--- Go-Back-N ARQ ---\n";

    for(int i = 1; i <= n; i += w)
    {
        int end = i + w - 1;

        if(end > n)
            end = n;

        for(int j = i; j <= end; j++)
        {
            cout << "Sending Frame " << j << endl;

            if(lost())
            {
                cout << "Frame " << j << " lost\n";

                cout << "Go-Back-N: Retransmitting from Frame "
                     << j << endl;

                for(int k = j; k <= end; k++)
                {
                    cout << "Retransmitting Frame " << k << endl;
                }

                break;
            }

            cout << "ACK " << j << " received\n";
        }
    }
}

int main()
{
    srand(time(0));

    int n, w;

    cout << "Enter number of frames: ";
    cin >> n;

    cout << "Enter window size: ";
    cin >> w;

    goBackN(n, w);

    return 0;
}
