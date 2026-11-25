
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

        int firstLost = -1;

        // Initial transmission
        for(int j = i; j <= end; j++)
        {
            cout << "Sending Frame " << j << endl;

            if(lost())
            {
                cout << "Frame " << j << " lost\n";

                if(firstLost == -1)
                    firstLost = j;
            }
            else
            {
                cout << "ACK " << j << " received\n";
            }
        }

        // Retransmit from first lost frame
        if(firstLost != -1)
        {
            cout << "\nGo-Back-N: Retransmitting from Frame "
                 << firstLost << endl;

            for(int j = firstLost; j <= end; j++)
            {
                bool success = false;

                while(!success)
                {
                    cout << "Retransmitting Frame " << j << endl;

                    if(lost())
                        cout << "Frame " << j << " lost again\n";
                    else
                    {
                        cout << "ACK " << j << " received\n";
                        success = true;
                    }
                }
            }
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

    if(n <= 0 || w <= 0)
    {
        cout << "Invalid input!";
        return 0;
    }

    goBackN(n, w);

    return 0;
}
