#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <set>
#include <map>

using namespace std;
using namespace chrono;

class ParkingLot {
private:
    set<int> availableSpaces; // Using a set to maintain sorted available spaces
    unordered_map<string, pair<int, system_clock::time_point>> occupiedSpaces;
    map<system_clock::time_point, string> parkingHistory; // For sliding window (track car entry times)
    int totalSpaces;
    int peakRateThreshold = 60; // Assume after 1 hour, differential pricing kicks in

public:
    ParkingLot(int total) : totalSpaces(total) {
        for (int i = 1; i <= totalSpaces; i++) {
            availableSpaces.insert(i);
        }
    }

    // Binary search approach using set (no explicit binary search function needed)
    void allocateSpace(const string& carNumber) {
    if (!availableSpaces.empty()) {
        int allocatedSpace = *availableSpaces.begin(); // Get the smallest available space
        availableSpaces.erase(availableSpaces.begin()); // Remove it from available spaces
        occupiedSpaces[carNumber] = {allocatedSpace, system_clock::now()};
        parkingHistory[system_clock::now()] = carNumber;
        cout << "Allocated Space " << allocatedSpace << " to Car " << carNumber << ".\n";
    } else {
        cout << "No parking space available for Car " << carNumber << ".\n";
    }
}

    // Release space and calculate differential pricing
    void releaseSpace(const string& carNumber) {
        if (occupiedSpaces.find(carNumber) != occupiedSpaces.end()) {
            int allocatedSpace = occupiedSpaces[carNumber].first;
            system_clock::time_point startTime = occupiedSpaces[carNumber].second;
            auto duration = duration_cast<seconds>(system_clock::now() - startTime).count();

            // Differential pricing based on duration
            double fee = calculateFee(duration);

            occupiedSpaces.erase(carNumber);
            availableSpaces.insert(allocatedSpace);
            cout << "Car " << carNumber << " left Space " << allocatedSpace
                 << ". Duration: " << duration << " seconds. Fee: $" << fee << "\n";
        } else {
            cout << "Car " << carNumber << " not found in the parking lot.\n";
        }
    }

    // Sliding window to remove cars that have stayed longer than 24 hours (or any fixed window)
    void checkParkingHistory() {
        system_clock::time_point now = system_clock::now();
        for (auto it = parkingHistory.begin(); it != parkingHistory.end();) {
            auto duration = duration_cast<hours>(now - it->first).count();
            if (duration > 24) { // Remove cars that have been parked for more than 24 hours
                occupiedSpaces.erase(it->second); // Erase from occupied spaces
                availableSpaces.insert(occupiedSpaces[it->second].first); // Re-add to available spaces
                it = parkingHistory.erase(it); // Remove from parking history
            } else {
                ++it;
            }
        }
    }

    // Differential pricing based on the duration of parking
    double calculateFee(long duration) {
        double fee = 5.0; // Base fee
        if (duration > peakRateThreshold) {
            fee += (duration - peakRateThreshold) * 0.1; // Additional fee per second after peak threshold
        }
        return fee;
    }

    // Process operations from file
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

    // Optionally, check the parking history (e.g., remove cars that stayed longer than 24 hours)
    parkingLot.checkParkingHistory();

    return 0;
}
