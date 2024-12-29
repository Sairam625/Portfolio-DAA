#include <iostream>
using namespace std;


void u(int p[], int r[], int x, int y) {// U-Union 
    int rx = f(p, x), ry = f(p, y);
    if (rx != ry) {
        if (r[rx] > r[ry]) p[ry] = rx;
        else if (r[rx] < r[ry]) p[rx] = ry;
        else { p[ry] = rx; r[rx]++; }
    }
}


int f(int p[], int x) { // F-Find 
    if (p[x] != x) p[x] = f(p, p[x]);  // Path compression
    return p[x];
}


bool c(int p[], int x, int y) { // C- connected
    return f(p, x) == f(p, y);
}

int main() {
    int n, cns;  // n = number of areas, cns = number of connections
    cout << "Enter number of areas: ";
    cin >> n;

    int p[n], r[n];
    for (int i = 0; i < n; i++) p[i] = i, r[i] = 0;

    cout << "Enter number of connections: ";
    cin >> cns;

  
    for (int i = 0; i < cns; i++) {  // Connect areas
        int x, y;
        cout << "Enter connection (x y): ";
        cin >> x >> y;
        u(p, r, x, y);
    }

    // Connectivity check
    int chks;  // chks = number of checks
    cout << "Enter number of connectivity checks: ";
    cin >> chks;

    for (int i = 0; i < chks; i++) {
        int x, y;
        cout << "Check if areas " << x << " and " << y << " are connected (x y): ";
        cin >> x >> y;
        cout << "Connected: " << (c(p, x, y) ? "Yes" : "No") << endl;
    }

    return 0;
}
manage interconnected farming areas
