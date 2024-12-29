#include <bits/stdc++.h>
using namespace std;

// BFS to manage resources in farming zones
void bfs(int m[10][10], int v, int s) {
    int q[20], f = 0, r = 0, u, i;
    int vis[10] = {0}; 

    q[r] = s;  
    vis[s] = 1; 

    cout << "Resource distribution from zone " << s << ":\n";

    
    while (f <= r) {
        u = q[f];  
        cout << "Zone " << u << " has received resources.\n"; 
        f++; 

      s
        for (i = 0; i < v; i++) {
            if (m[u][i] == 1 && vis[i] == 0)
            {  
                vis[i] = 1;  
                r++;  
                q[r] = i;  
            }
        }
    }
}

int main() {
    int v, m[10][10], s;
    
    //  number of zones
    cout << "Enter number of zones: ";
    cin >> v;

    //  connectivity matrix
    cout << "Enter connectivity matrix:\n";
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            cin >> m[i][j];

    // source zone for resource distribution
    cout << "Enter the source zone (0 to " << v-1 << "): ";
    cin >> s;

    
    bfs(m, v, s);

    return 0;
}
