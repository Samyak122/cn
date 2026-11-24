
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int cost[10][10], dist[10][10];
    int nextHop[10][10];

    cout << "Enter number of routers: ";
    cin >> n;

    cout << "Enter cost matrix (999 for no connection):\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> cost[i][j];

            dist[i][j] = cost[i][j];

            if(i != j && cost[i][j] != 999)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }

    bool updated;

    do
    {
        updated = false;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    if(cost[i][k] != 999 &&
                       dist[k][j] != 999 &&
                       cost[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = cost[i][k] + dist[k][j];
                        nextHop[i][j] = k;
                        updated = true;
                    }
                }
            }
        }

    } while(updated);

    // Display routing tables
    for(int i = 0; i < n; i++)
    {
        cout << "\nRouter " << char('A' + i)
             << " Routing Table\n";

        cout << "Destination\tCost\tNext Hop\n";

        for(int j = 0; j < n; j++)
        {
            cout << char('A' + j) << "\t\t";

            if(dist[i][j] == 999)
                cout << "INF\t-\n";
            else if(i == j)
                cout << "0\t-\n";
            else
                cout << dist[i][j] << "\t"
                     << char('A' + nextHop[i][j]) << endl;
        }
    }

    return 0;
}
