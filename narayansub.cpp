#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int ip[4], prefix;
    int mask[4], network[4], broadcast[4];

    cout << "Enter IP Address (e.g. 192 168 1 10): ";
    for (int i = 0; i < 4; i++)
        cin >> ip[i];

    cout << "Enter CIDR Prefix (e.g. 24): ";
    cin >> prefix;

    if (prefix < 0 || prefix > 32)
    {
        cout << "Invalid CIDR Prefix!";
        return 0;
    }

    for (int i = 0; i < 4; i++)
    {
        int bits = prefix - (i * 8);

        if (bits >= 8)
            mask[i] = 255;
        else if (bits <= 0)
            mask[i] = 0;
        else
            mask[i] = 256 - pow(2, 8 - bits);

        network[i] = ip[i] & mask[i];
        broadcast[i] = network[i] | (255 - mask[i]);
    }

    cout << "\nSubnet Mask: ";
    for (int i = 0; i < 4; i++)
        cout << mask[i] << (i < 3 ? "." : "");

    cout << "\nNetwork Address: ";
    for (int i = 0; i < 4; i++)
        cout << network[i] << (i < 3 ? "." : "");

    cout << "\nBroadcast Address: ";
    for (int i = 0; i < 4; i++)
        cout << broadcast[i] << (i < 3 ? "." : "");

    cout << "\nFirst Usable IP: ";
    for (int i = 0; i < 4; i++)
    {
        int first = network[i];
        if (i == 3) first++;
        cout << first << (i < 3 ? "." : "");
    }

    cout << "\nLast Usable IP: ";
    for (int i = 0; i < 4; i++)
    {
        int last = broadcast[i];
        if (i == 3) last--;
        cout << last << (i < 3 ? "." : "");
    }

    int hosts = (prefix == 32) ? 1 :
                (prefix == 31) ? 2 :
                (int)pow(2, 32 - prefix) - 2;

    cout << "\nTotal Usable Hosts: " << hosts << endl;

    return 0;
}