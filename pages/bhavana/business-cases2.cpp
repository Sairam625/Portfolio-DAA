#include <iostream>
using namespace std;

// Function to merge two cultural gatherings into the same group
void Union(int arr[], int u, int v) 
{
    int temp = arr[u];  
    for (int i = 0; i < 5; i++)
      {  // Loop through all gatherings
        if (arr[i] == temp)
        {  // If gathering belongs to u's group
            arr[i] = arr[v];            // Merge it into v's group
        }
    }
}

// Function to check if two gatherings belong to the same group
bool Find(int arr[], int u, int v)
{
    return arr[u] == arr[v];  
}

int main()
{
    int arr[5];  // Array to store group info for 5 gatherings
    
    for (int i = 0; i < 5; i++) 
    {
        arr[i] = i;
    }

    int u, v;
    char choice;
    
    do
      {
        // Merge two gatherings
        cout << "Enter two gatherings to merge (u v): ";
        cin >> u >> v;
        Union(arr, u, v);
        
        // Check if two gatherings are in the same group
        cout << "Enter two gatherings to check (u v): ";
        cin >> u >> v;
        if (Find(arr, u, v)) {
            cout << "Gatherings " << u << " and " << v << " are in  same group.\n";
        } else {
            cout << "Gatherings " << u << " and " << v << " are in different groups.\n";
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> choice;

    } while (choice == 'y');

    return 0;
}
