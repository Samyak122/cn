#include<iostream>
using namespace std;

// Function for CRC division
string divideCRC(string data, string gen)
{
    int n = gen.length();

    for(int i = 0; i <= data.length()-n; i++)
    {
        if(data[i] == '1')
        {
            for(int j = 0; j < n; j++)
            {   //XOR
                if(data[i+j] == gen[j])
                    data[i+j] = '0';
                else
                    data[i+j] = '1';
            }
        }
    }

    return data.substr(data.length()-n+1);
}

int main()
{
    string s, gen;

    cout << "Enter the data: ";
    cin >> s;

    cout << "Enter the generator: ";
    cin >> gen;

    // Add zeros to data
    string temp = s + string(gen.length()-1, '0');

    // Calculate CRC remainder
    string crc = divideCRC(temp, gen);

    cout << "CRC remainder: " << crc << endl;

    // Transmitted data
    string transmitted = s + crc;

    cout << "Transmitted data: " << transmitted << endl;

    // Receiver side
    string r;

    cout << "Enter the received data: ";
    cin >> r;

    string rem = divideCRC(r, gen);

    cout << "Receiver remainder: " << rem << endl;

    if(rem.find('1') == string::npos)
    {
        cout << "No error detected" << endl;
    }
    else
    {
        cout << "Error detected" << endl;
    }

    return 0;
}