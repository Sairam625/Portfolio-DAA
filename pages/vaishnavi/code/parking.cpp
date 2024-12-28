
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <sstream>

using namespace std;
using namespace chrono;

class ParkingLot {
private:
    priority_queue<int, vector<int>, greater<int>> availableSpaces;
    unordered_map<string, pair<int, system_clock::time_point>> occupiedSpaces;
    int totalSpaces;

public:
    ParkingLot(int total) : totalSpaces(total) {
        for (int i = 1; i <= totalSpaces; i++) {
            availableSpaces.push(i);
        }
    }

    void allocateSpace(const string& carNumber) {
        if (!availableSpaces.empty()) {
            int allocatedSpace = availableSpaces.top();
            availableSpaces.pop();
            occupiedSpaces[carNumber] = {allocatedSpace, system_clock::now()};
            cout << "Allocated Space " << allocatedSpace << " to Car " << carNumber << ".\n";
        } else {
            cout << "No parking space available for Car " << carNumber << ".\n";
        }
    }

    void releaseSpace(const string& carNumber) {
        if (occupiedSpaces.find(carNumber) != occupiedSpaces.end()) {
            int allocatedSpace = occupiedSpaces[carNumber].first;
            system_clock::time_point startTime = occupiedSpaces[carNumber].second;
            auto duration = duration_cast<seconds>(system_clock::now() - startTime).count();
            occupiedSpaces.erase(carNumber);
            availableSpaces.push(allocatedSpace);
            cout << "Car " << carNumber << " left Space " << allocatedSpace
                 << ". Duration: " << duration << " seconds.\n";
        } else {
            cout << "Car " << carNumber << " not found in the parking lot.\n";
        }
    }

    void processFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string command, carNumber;
            ss >> command >> carNumber;

            if (command == "ALLOCATE") {
                allocateSpace(carNumber);
            } else if (command == "RELEASE") {
                releaseSpace(carNumber);
            } else {
                cout << "Invalid command: " << command << endl;
            }
        }

        file.close();
    }
};

int main() {
    ParkingLot parkingLot(5); // Initialize with 5 spaces

    // Process operations from file
    parkingLot.processFile("parking_operations.txt");

    return 0;
}
