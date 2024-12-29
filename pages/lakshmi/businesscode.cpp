#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Ticket structure
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

// Function to display tickets
void displayTickets(const vector<Ticket>& tickets, const string& transportType) {
    cout << "Sorted Tickets for " << transportType << ":\n";
    for (const auto& ticket : tickets) {
        cout << "Route: " << ticket.route 
             << ", Price: " << ticket.price 
             << ", Time: " << ticket.time << " minutes\n";
    }
    cout << endl;
}

// Function to load tickets from a CSV file
void loadTicketsFromFile(const string& filename, vector<Ticket>& tickets) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line, route;
    int price, time;

    getline(file, line); // Skip the header row
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, route, ',');
        ss >> price;
        ss.ignore(1); // Ignore the comma
        ss >> time;
        tickets.push_back({route, price, time});
    }
    file.close();
}

// Function to add tickets manually
void addTicket(vector<Ticket>& tickets) {
    string route;
    int price, time;

    cout << "Enter route name: ";
    cin >> route;
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter time in minutes: ";
    cin >> time;

    tickets.push_back({route, price, time});
}

// Main function
int main() {
    vector<Ticket> busTickets, metroTickets, trainTickets;

    // Load tickets from CSV files
    loadTicketsFromFile("bus_tickets.csv", busTickets);
    loadTicketsFromFile("metro_tickets.csv", metroTickets);
    loadTicketsFromFile("train_tickets.csv", trainTickets);

    // Option to add tickets manually
    cout << "Do you want to add tickets manually? (yes/no): ";
    string response;
    cin >> response;
    if (response == "yes") {
        cout << "Add tickets for Bus:\n";
        addTicket(busTickets);
        cout << "Add tickets for Metro:\n";
        addTicket(metroTickets);
        cout << "Add tickets for Train:\n";
        addTicket(trainTickets);
    }

    cout << "Choose sorting method: \n1. Merge Sort\n2. Quick Sort\nEnter choice: ";
    int choice;
    cin >> choice;

    cout << "Choose sorting key: \n1. Price\n2. Time\nEnter choice: ";
    int keyChoice;
    cin >> keyChoice;
    string key = (keyChoice == 1) ? "price" : "time";

    // Sorting based on user input
    if (choice == 1) {
        mergeSort(busTickets, 0, busTickets.size() - 1, key);
        mergeSort(metroTickets, 0, metroTickets.size() - 1, key);
        mergeSort(trainTickets, 0, trainTickets.size() - 1, key);
    } else if (choice == 2) {
        quickSort(busTickets, 0, busTickets.size() - 1, key);
        quickSort(metroTickets, 0, metroTickets.size() - 1, key);
        quickSort(trainTickets, 0, trainTickets.size() - 1, key);
    } else {
        cout << "Invalid choice." << endl;
        return 0;
    }

    // Display sorted tickets
    displayTickets(busTickets, "Bus");
    displayTickets(metroTickets, "Metro");
    displayTickets(trainTickets, "Train");

    return 0;
}
