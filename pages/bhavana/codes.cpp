#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Partition function
int partition(vector<string>& arr, int low, int high) {
    string pivot = arr[high]; // Choosing the last element as the pivot
    int i = low - 1; // Index for smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    // List of waste categories
    vector<string> wasteData = {"Plastic", "Glass", "Metal", "Organic", "Paper", "Plastic", "Organic"};

    cout << "Unsorted Waste Data:" << endl;
    for (const auto& item : wasteData) {
        cout << item << " ";
    }
    cout << endl;

    // Sorting the waste data
    quickSort(wasteData, 0, wasteData.size() - 1);

    cout << "Sorted Waste Data:" << endl;
    for (const auto& item : wasteData) {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}
