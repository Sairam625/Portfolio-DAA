#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// Dock Class
class Dock {
public:
    int id;
    time_t availableTime;

    Dock(int id) : id(id), availableTime(0) {}

    void schedule(time_t startTime, int loadTimeHours) {
        availableTime = startTime + (loadTimeHours * 3600); // Add load time in seconds
    }

    bool isAvailable(time_t requestedTime) {
        return requestedTime >= availableTime;
    }
};

// Truck Class
class Truck {
public:
    int truckId;
    time_t arrivalTime;
    int loadTime;

    Truck(int id, time_t arrival, int loadHours)
        : truckId(id), arrivalTime(arrival), loadTime(loadHours) {}
};

// Compare trucks based on arrival time
struct CompareArrival {
    bool operator()(const Truck& t1, const Truck& t2) {
        return t1.arrivalTime > t2.arrivalTime;
    }
};

// Scheduling System Class
class SchedulingSystem {
private:
    vector<Dock> docks;
    priority_queue<Truck, vector<Truck>, CompareArrival> trucksQueue;

    string formatTime(time_t rawTime) {
        tm* timeInfo = localtime(&rawTime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }

    Dock& findEarliestDock() {
        return *min_element(docks.begin(), docks.end(),
            [](const Dock& d1, const Dock& d2) { return d1.availableTime < d2.availableTime; });
    }

public:
    SchedulingSystem(int numDocks) {
        for (int i = 0; i < numDocks; ++i) {
            docks.push_back(Dock(i));
        }
    }

    void addTruck(int id, time_t arrival, int loadHours) {
        trucksQueue.push(Truck(id, arrival, loadHours));
    }

    void efficientSchedule() {
        while (!trucksQueue.empty()) {
            Truck currentTruck = trucksQueue.top();
            trucksQueue.pop();

            bool scheduled = false;

            // Check available docks and assign if possible
            for (auto& dock : docks) {
                if (dock.isAvailable(currentTruck.arrivalTime)) {
                    time_t startTime = max(dock.availableTime, currentTruck.arrivalTime);
                    dock.schedule(startTime, currentTruck.loadTime);

                    cout << "Truck " << currentTruck.truckId
                         << " scheduled from " << formatTime(startTime)
                         << " to " << formatTime(dock.availableTime)
                         << " at Dock " << dock.id << endl;
                    scheduled = true;
                    break;
                }
            }

            // If no dock is available, find the earliest available dock
            if (!scheduled) {
                Dock& earliestDock = findEarliestDock();
                time_t startTime = earliestDock.availableTime;
                earliestDock.schedule(startTime, currentTruck.loadTime);

                cout << "Truck " << currentTruck.truckId
                     << " scheduled from " << formatTime(startTime)
                     << " to " << formatTime(earliestDock.availableTime)
                     << " at Dock " << earliestDock.id << endl;
            }
        }
    }
};

// Main Function
int main() {
    int numDocks, numTrucks;

    cout << "Enter number of docks: ";
    cin >> numDocks;

    cout << "Enter number of trucks: ";
    cin >> numTrucks;

    SchedulingSystem system(numDocks);

    for (int i = 0; i < numTrucks; ++i) {
        int truckId, hour, minute, loadTimeHours;

        cout << "Enter truck " << (i + 1) << " details:" << endl;
        cout << "Truck ID: ";
        cin >> truckId;

        cout << "Arrival time (hour minute): ";
        cin >> hour >> minute;

        if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) {
            cout << "Invalid time entered. Please enter time in HH MM format." << endl;
            --i;
            continue;
        }

        cout << "Loading time (in hours): ";
        cin >> loadTimeHours;

        time_t currentTime = time(0);
        tm* timeInfo = localtime(&currentTime);
        timeInfo->tm_hour = hour;
        timeInfo->tm_min = minute;
        timeInfo->tm_sec = 0;
        time_t arrivalTime = mktime(timeInfo);

        system.addTruck(truckId, arrivalTime, loadTimeHours);
    }

    system.efficientSchedule();
    return 0;
}
