
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    string ip;
    int a, b, c, d, prefix;

    cout << "Enter IP Address: ";
    cin >> ip;

    cout << "Enter Subnet Prefix (0-32): ";
    cin >> prefix;

    if (sscanf(ip.c_str(), "%d.%d.%d.%d",
        &a, &b, &c, &d) != 4 ||
        a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255 ||
        prefix < 0 || prefix > 32)
    {
        cout << "Invalid IP or Prefix!";
        return 0;
    }

    // Convert IP into 32-bit number
    unsigned int ipNum =
        ((unsigned int)a << 24) |
        ((unsigned int)b << 16) |
        ((unsigned int)c << 8) |
        (unsigned int)d;

    // Calculate subnet mask
    unsigned int mask =
        (prefix == 0) ? 0 : (0xFFFFFFFFu << (32-prefix));

    // Calculate network and broadcast
    unsigned int network = ipNum & mask;
    unsigned int broadcast = network | ~mask;

    cout << "\nSubnet Mask: "
         << ((mask >> 24) & 255) << "."
         << ((mask >> 16) & 255) << "."
         << ((mask >> 8) & 255) << "."
         << (mask & 255);

    cout << "\nNetwork Address: "
         << ((network >> 24) & 255) << "."
         << ((network >> 16) & 255) << "."
         << ((network >> 8) & 255) << "."
         << (network & 255);

    cout << "\nBroadcast Address: "
         << ((broadcast >> 24) & 255) << "."
         << ((broadcast >> 16) & 255) << "."
         << ((broadcast >> 8) & 255) << "."
         << (broadcast & 255);

    unsigned long long total = 1ULL << (32-prefix);

    cout << "\nTotal IP Addresses: " << total;

    if(prefix <= 30)
    {
        cout << "\nFirst Host: "
             << ((network + 1) >> 24 & 255) << "."
             << ((network + 1) >> 16 & 255) << "."
             << ((network + 1) >> 8 & 255) << "."
             << ((network + 1) & 255);

        cout << "\nLast Host: "
             << ((broadcast - 1) >> 24 & 255) << "."
             << ((broadcast - 1) >> 16 & 255) << "."
             << ((broadcast - 1) >> 8 & 255) << "."
             << ((broadcast - 1) & 255);

        cout << "\nUsable Hosts: " << total - 2;
    }
    else if(prefix == 31)
    {
        cout << "\nUsable Addresses: 2 (point-to-point subnet)";
    }
    else
    {
        cout << "\nUsable Addresses: 1 (/32 host route)";
    }

    return 0;
}
