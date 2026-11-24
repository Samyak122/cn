
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string data, received;
    int count = 0, parity, p;

    cout << "Enter binary data: ";
    cin >> data;

    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] == '1')
            count++;
    }

    cout << "Enter parity (0=Even, 1=Odd): ";
    cin >> parity;

    if (parity == 0)
        p = count % 2;
    else
        p = (count + 1) % 2;

    string transmitted = data + to_string(p);

    cout << "Parity bit: " << p;
    cout << "\nTransmitted data: " << transmitted;

    cout << "\nEnter received data: ";
    cin >> received;

    count = 0;

    for (int i = 0; i < received.length(); i++)
    {
        if (received[i] == '1')
            count++;
    }

    if (received.length() != transmitted.length())
    {
        cout << "\nInvalid data length!";
    }
    else if (count % 2 == parity)
    {
        cout << "\nNo error detected!";
    }
    else
    {
        cout << "\nError detected!";
    }

    return 0;
}