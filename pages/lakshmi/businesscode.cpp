#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Ticket {
    string route;
    int price;
    int time;
};

// Merge Sort implementation
void merge(vector<Ticket>& tickets, int left, int mid, int right, string key) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Ticket> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = tickets[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = tickets[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((key == "price" && L[i].price <= R[j].price) || (key == "time" && L[i].time <= R[j].time)) {
            tickets[k] = L[i];
            ++i;
        } else {
            tickets[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        tickets[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        tickets[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<Ticket>& tickets, int left, int right, string key) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(tickets, left, mid, key);
        mergeSort(tickets, mid + 1, right, key);
        merge(tickets, left, mid, right, key);
    }
}

// Quick Sort implementation
int partition(vector<Ticket>& tickets, int low, int high, string key) {
    Ticket pivot = tickets[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if ((key == "price" && tickets[j].price < pivot.price) || (key == "time" && tickets[j].time < pivot.time)) {
            ++i;
            swap(tickets[i], tickets[j]);
        }
    }
    swap(tickets[i + 1], tickets[high]);
    return i + 1;
}

void quickSort(vector<Ticket>& tickets, int low, int high, string key) {
    if (low < high) {
        int pi = partition(tickets, low, high, key);
        quickSort(tickets, low, pi - 1, key);
        quickSort(tickets, pi + 1, high, key);
    }
}


void displayTickets(const vector<Ticket>& tickets) {
    for (const auto& ticket : tickets) {
        cout << "Route: " << ticket.route << ", Price: " << ticket.price << ", Time: " << ticket.time << " minutes" << endl;
    }
}

int main() {
    vector<Ticket> busTickets = {
        {"Bus A", 5, 15},
        {"Bus B", 3, 10},
        {"Bus C", 7, 20}
    };

    vector<Ticket> metroTickets = {
        {"Metro X", 10, 5},
        {"Metro Y", 8, 6},
        {"Metro Z", 12, 4}
    };

    vector<Ticket> trainTickets = {
        {"Train 1", 15, 30},
        {"Train 2", 20, 25},
        {"Train 3", 18, 35}
    };

    cout << "Choose sorting method: \n1. Merge Sort\n2. Quick Sort\nEnter choice: ";
    int choice;
    cin >> choice;

    cout << "Choose sorting key: \n1. Price\n2. Time\nEnter choice: ";
    int keyChoice;
    cin >> keyChoice;
    string key = (keyChoice == 1) ? "price" : "time";

    if (choice == 1) {
        cout << "\nSorting Bus Tickets using Merge Sort by " << key << ":\n";
        mergeSort(busTickets, 0, busTickets.size() - 1, key);
        displayTickets(busTickets);

        cout << "\nSorting Metro Tickets using Merge Sort by " << key << ":\n";
        mergeSort(metroTickets, 0, metroTickets.size() - 1, key);
        displayTickets(metroTickets);

        cout << "\nSorting Train Tickets using Merge Sort by " << key << ":\n";
        mergeSort(trainTickets, 0, trainTickets.size() - 1, key);
        displayTickets(trainTickets);
    } else if (choice == 2) {
        cout << "\nSorting Bus Tickets using Quick Sort by " << key << ":\n";
        quickSort(busTickets, 0, busTickets.size() - 1, key);
        displayTickets(busTickets);

        cout << "\nSorting Metro Tickets using Quick Sort by " << key << ":\n";
        quickSort(metroTickets, 0, metroTickets.size() - 1, key);
        displayTickets(metroTickets);

        cout << "\nSorting Train Tickets using Quick Sort by " << key << ":\n";
        quickSort(trainTickets, 0, trainTickets.size() - 1, key);
        displayTickets(trainTickets);
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
