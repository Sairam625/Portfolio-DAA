#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to partition the waste array (used by QuickSort)
int Partition(vector<pair<string, string>>& waste, int low, int high) {
    string pivot = waste[low].second;  // Pivot is the waste type
    int i = low, j = high;

    while (i < j) {
        while (waste[i].second <= pivot && i <= high) i++; 
        while (waste[j].second > pivot) j--; 
        if (i < j) swap(waste[i], waste[j]); 
    }
    swap(waste[low], waste[j]); // Place pivot in correct position
    return j;
}

// QuickSort to segregate waste items by type
void QuickSort(vector<pair<string, string>>& waste, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(waste, low, high); // Partitioning step
        QuickSort(waste, low, pivotIndex - 1); // Sort left part
        QuickSort(waste, pivotIndex + 1, high); // Sort right part
    }
}

// Function to merge two sorted subarrays (used by MergeSort)
void Merge(vector<pair<string, string>>& waste, int left, int mid, int right) {
    vector<pair<string, string>> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (waste[i].second <= waste[j].second)
            temp.push_back(waste[i++]); // Add smaller item
        else
            temp.push_back(waste[j++]); // Add smaller item
    }

    while (i <= mid) temp.push_back(waste[i++]); // Copy remaining items from left
    while (j <= right) temp.push_back(waste[j++]); // Copy remaining items from right

    // Copy the sorted array back to the original waste array
    for (int k = left; k <= right; k++) waste[k] = temp[k - left];
}

// MergeSort to store the waste items in a sorted order
void MergeSort(vector<pair<string, string>>& waste, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; 

        MergeSort(waste, left, mid); // Sort the left part
        MergeSort(waste, mid + 1, right); // Sort the right part

        Merge(waste, left, mid, right); // Merge the sorted parts
    }
}

int main() {
    int n;
    cout << "Enter the number of waste items: ";
    cin >> n;

    vector<pair<string, string>> waste;

    cout << "Enter waste items and their types (Dry, Wet, E-Waste, Glass, Metal):\n";
    cin.ignore(); 
    for (int i = 0; i < n; i++) {
        string description, type;
        cout << "Waste " << i + 1 << " description: ";
        getline(cin, description);  
        cout << "Waste " << i + 1 << " type (Dry, Wet, E-Waste, Glass, Metal): ";
        getline(cin, type); 
        waste.push_back({description, type});
    }

    // Display before sorting
    cout << "\nBefore sorting:\n";
    for (const auto& item : waste) {
        cout << item.first << " - " << item.second << endl;
    }

    // QuickSort to segregate waste by type
    QuickSort(waste, 0, n - 1);

    // Display after QuickSort segregation
    cout << "\nAfter QuickSort segregation (sorted by type):\n";
    for (const auto& item : waste) {
        cout << item.first << " - " << item.second << endl;
    }

    // Now, use MergeSort to store and organize the waste
    MergeSort(waste, 0, n - 1);

    // Display after MergeSort
    cout << "\nAfter MergeSort (sorted by type):\n";
    for (const auto& item : waste) {
        cout << item.first << " - " << item.second << endl;
    }

    return 0;
}

