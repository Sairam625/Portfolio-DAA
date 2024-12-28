#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Resident {
public:
    int id;
    float income;
    int family_size;
    float proximity_score;

    Resident(int id, float income, int family_size, float proximity_score) {
        this->id = id;
        this->income = income;
        this->family_size = family_size;
        this->proximity_score = proximity_score;
    }
};

class House {
public:
    int id;
    float cost;
    int size;
    float location_score;

    House(int id, float cost, int size, float location_score) {
        this->id = id;
        this->cost = cost;
        this->size = size;
        this->location_score = location_score;
    }
};

vector<Resident> readResidentsFromFile(const string& filename) {
    vector<Resident> residents;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string type;
        int id, family_size;
        float income, proximity_score;

        ss >> type >> id >> income >> family_size >> proximity_score;

        if (type == "Resident") {
            residents.push_back(Resident(id, income, family_size, proximity_score));
        }
    }

    return residents;
}

vector<House> readHousesFromFile(const string& filename) {
    vector<House> houses;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string type;
        int id, size;
        float cost, location_score;

        ss >> type >> id >> cost >> size >> location_score;

        if (type == "House") {
            houses.push_back(House(id, cost, size, location_score));
        }
    }

    return houses;
}

// Backtracking to explore different allocation possibilities
void backtrackAllocation(int i, vector<pair<int, int>>& current_allocation, int current_satisfaction, const vector<Resident>& residents, const vector<House>& houses, int& best_satisfaction, vector<pair<int, int>>& best_allocation) {
    // Debug: Show the current step
    cout << "At backtrack level " << i << ", current allocation size: " << current_allocation.size() << endl;

    // If we've checked all residents, compare satisfaction and update best solution
    if (i == residents.size()) {
        cout << "End of allocation branch: Satisfaction = " << current_satisfaction << endl;
        if (current_satisfaction > best_satisfaction) {
            best_satisfaction = current_satisfaction;
            best_allocation = current_allocation;
            cout << "New best satisfaction: " << best_satisfaction << endl;
        }
        return;
    }

    for (int j = 0; j < houses.size(); j++) {
        // Check if the current house can be allocated to the resident
        if (houses[j].cost <= residents[i].income) {
            cout << "Trying Resident " << residents[i].id << " with House " << houses[j].id << endl;

            // Add the allocation and continue to the next resident
            current_allocation.push_back({residents[i].id, houses[j].id});
            backtrackAllocation(i + 1, current_allocation, current_satisfaction + houses[j].location_score, residents, houses, best_satisfaction, best_allocation);

            // Remove the allocation (backtrack)
            current_allocation.pop_back();
        }
    }
}

// Explore all possible allocations using backtracking
void exploreAllocations(const vector<Resident>& residents, const vector<House>& houses) {
    vector<pair<int, int>> best_allocation;
    int best_satisfaction = 0;

    vector<pair<int, int>> current_allocation; // Initialize an empty vector for current allocation
    backtrackAllocation(0, current_allocation, 0, residents, houses, best_satisfaction, best_allocation);

    if (best_allocation.empty()) {
        cout << "No valid allocation found." << endl;
    } else {
        cout << "Best Allocation (Backtracking):\n";
        for (const auto& allocation : best_allocation) {
            cout << "Resident " << allocation.first << " -> House " << allocation.second << endl;
        }
    }
}

int main() {
    string input_file = "housing_input.txt";  // Input data file
    vector<Resident> residents = readResidentsFromFile(input_file);
    vector<House> houses = readHousesFromFile(input_file);

    // Debug: Check if data is read correctly
    cout << "Number of residents: " << residents.size() << endl;
    cout << "Number of houses: " << houses.size() << endl;

    // Explore different allocations using backtracking
    exploreAllocations(residents, houses);

    return 0;
}
