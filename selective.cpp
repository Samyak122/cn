
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Returns 1 if frame is lost
int lost()
{
    return rand() % 2 == 0;
}

// Selective Repeat ARQ
void selectiveRepeat(int n, int w)
{
    cout << "\n--- Selective Repeat ARQ ---\n";

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

                bool success = false;

                while(!success)
                {
                    cout << "Retransmitting only Frame "
                         << j << endl;

                    if(lost())
                        cout << "Frame " << j << " lost again\n";
                    else
                    {
                        cout << "ACK " << j << " received\n";
                        success = true;
                    }
                }
            }
            else
            {
                cout << "ACK " << j << " received\n";
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

    selectiveRepeat(n, w);

    return 0;
}
