#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>
#include <algorithm> // For min_element

using namespace std;

class Dock {
public:
    int id;
    time_t availableTime;

    Dock(int id) : id(id), availableTime(time(0)) {}

    bool isAvailable(time_t requestedTime) {
        return requestedTime >= availableTime;
    }

    void schedule(time_t startTime, int loadTimeHours) {
        availableTime = startTime + (loadTimeHours * 3600);
    }
};

class Truck {
public:
    int truckId;
    time_t arrivalTime;
    int loadTime;

    Truck(int id, time_t arrival, int loadHours)
        : truckId(id), arrivalTime(arrival), loadTime(loadHours) {}
};

struct CompareArrival {
    bool operator()(Truck const& t1, Truck const& t2) {
        return t1.arrivalTime > t2.arrivalTime;
    }
};

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

public:
    SchedulingSystem(int numDocks) {
        for (int i = 0; i < numDocks; ++i) {
            docks.push_back(Dock(i));
        }
    }

    void addTruck(int id, time_t arrival, int loadHours) {
        trucksQueue.push(Truck(id, arrival, loadHours));
    }

    void loadBalancing() {
        while (!trucksQueue.empty()) {
            Truck currentTruck = trucksQueue.top();
            trucksQueue.pop();

            auto leastLoadedDock = min_element(docks.begin(), docks.end(),
                [](Dock& d1, Dock& d2) { return d1.availableTime < d2.availableTime; });

            time_t startTime = max(leastLoadedDock->availableTime, currentTruck.arrivalTime);
            time_t endTime = startTime + (currentTruck.loadTime * 3600);

            leastLoadedDock->schedule(startTime, currentTruck.loadTime);

            cout << "Truck " << currentTruck.truckId
                 << " scheduled from " << formatTime(startTime)
                 << " to " << formatTime(endTime)
                 << " at Dock " << leastLoadedDock->id << endl;
        }
    }
};

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

    system.loadBalancing();

    return 0;
}
