#include <iostream>
#include <vector>
#include <string>

using namespace std;


int Part(vector<pair<string, string>>& w, int low, int high) 
{
    string p = w[low].second;  )
    int i = low, j = high;

    while (i < j) 
    {
        while (w[i].second <= p && i <= high) i++;                                                                               // Move i to right
        while (w[j].second > p) j--;                                                                                         // Move j to left
        if (i < j) swap(w[i], w[j]);                                                                                         // Swap 
    }
    swap(w[low], w[j]); 
    return j;
}

// QuickSort to segregate waste items by type
void Quick(vector<pair<string, string>>& w, int low, int high) {
    if (low < high) {
        int pI = Part(w, low, high); 
        Quick(w, low, pI - 1); 
        Quick(w, pI + 1, high); 
    }
}

// Function to merge two sorted subarrays 
void Merge(vector<pair<string, string>>& w, int left, int mid, int right) {
    vector<pair<string, string>> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (w[i].second <= w[j].second)
            temp.push_back(w[i++]);              // smaller item
        else
            temp.push_back(w[j++]); //  smaller item
    }

    while (i <= mid) temp.push_back(w[i++]);                                         // Copy remaining items from left
    while (j <= right) temp.push_back(w[j++]);                                          // Copy remaining items from right

    // Copy the sorted array  to the original waste array
    for (int k = left; k <= right; k++) w[k] = temp[k - left];
}

// MergeSort to store the waste items in a sorted order
void MergeSort(vector<pair<string, string>>& w, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; 

        MergeSort(w, left, mid);                              // Sort left part
        MergeSort(w, mid + 1, right);                          // Sort  right part

        Merge(w, left, mid, right);                            // Merge the sorted parts
    }
}

int main() {
    int n;
    cout << "Enter the number of waste items: ";
    cin >> n;

    vector<pair<string, string>> w;

    // Input waste items and their types
    cout << "Enter waste items and their types (Dry, Wet, E-Waste, Glass, Metal):\n";
    cin.ignore();t
    for (int i = 0; i < n; i++) {
        string desc, type;
        cout << "Waste " << i + 1 << " description: ";
        getline(cin, desc);  
        cout << "Waste " << i + 1 << " type (Dry, Wet, E-Waste, Glass, Metal): ";
        getline(cin, type);  
        w.push_back({desc, type});
    }

    // Display before sorting
    cout << "\nBefore sorting:\n";
    for (const auto& item : w) {
        cout << item.first << " - " << item.second << endl;
    }

    // QuickSort to segregate waste by type
    Quick(w, 0, n - 1);

    // Display after QuickSort segregation
    cout << "\nAfter QuickSort segregation (sorted by type):\n";
    for (const auto& item : w) {
        cout << item.first << " - " << item.second << endl;
    }

    //  MergeSort to store and organize the waste
    MergeSort(w, 0, n - 1);

    // Display after MergeSort
    cout << "\nAfter MergeSort (sorted by type):\n";
    for (const auto& item : w) {
        cout << item.first << " - " << item.second << endl;
    }

    return 0;
}
