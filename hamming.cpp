
#include <iostream>
using namespace std;

int main()
{
    int h[7], s1, s2, s4, error;

    cout << "Enter 4 data bits: ";

    cin >> h[2] >> h[4] >> h[5] >> h[6];

    // Calculate parity bits
    h[0] = h[2] ^ h[4] ^ h[6];
    h[1] = h[2] ^ h[5] ^ h[6];
    h[3] = h[4] ^ h[5] ^ h[6];

    cout << "Hamming code: ";

    for(int i = 0; i < 7; i++)
        cout << h[i];

    cout << endl;

    // Receiver side
    cout << "Enter received 7 bits: ";

    for(int i = 0; i < 7; i++)
        cin >> h[i];

    // Check parity
    s1 = h[0] ^ h[2] ^ h[4] ^ h[6];
    s2 = h[1] ^ h[2] ^ h[5] ^ h[6];
    s4 = h[3] ^ h[4] ^ h[5] ^ h[6];

    error = s4 * 4 + s2 * 2 + s1;

    if(error == 0)
    {
        cout << "No error detected";
    }
    else
    {
        cout << "Error at position: " << error << endl;

        h[error - 1] = h[error - 1] ^ 1;

        cout << "Corrected data: ";

        for(int i = 0; i < 7; i++)
            cout << h[i];
    }

    return 0;
}
