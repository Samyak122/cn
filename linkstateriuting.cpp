
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, source;
    int cost[10][10];
    int dist[10], visited[10] = {0};

    cout << "Enter number of routers: ";
    cin >> n;

    cout << "Enter cost matrix (999 for no connection):\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    cout << "Enter source router (0 to " << n-1 << "): ";
    cin >> source;

    for(int i = 0; i < n; i++)
        dist[i] = cost[source][i];

    dist[source] = 0;
    visited[source] = 1;

    for(int count = 1; count < n; count++)
    {
        int min = 999, u = -1;

        for(int i = 0; i < n; i++)
        {
            if(!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        if(u == -1)
            break;

        visited[u] = 1;

        for(int v = 0; v < n; v++)
        {
            if(!visited[v] &&
               cost[u][v] != 999 &&
               dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "\nShortest distances from Router "
         << char('A' + source) << ":\n";

    cout << "Destination\tCost\n";

    for(int i = 0; i < n; i++)
    {
        cout << char('A' + i) << "\t\t";

        if(dist[i] == 999)
            cout << "INF\n";
        else
            cout << dist[i] << endl;
    }

    return 0;
}
