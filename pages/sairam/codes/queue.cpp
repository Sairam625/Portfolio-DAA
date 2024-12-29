#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;


class Queue {
private:
    queue<string> q; 

public:
    
    void enqueue(const string& data) {
        q.push(data);
    }

    void dequeue() {
        if (!q.empty()) {
            cout << "Dequeued: " << q.front() << endl;
            q.pop();
        } else {
            cout << "Queue is empty, cannot dequeue." << endl;
        }
    }


    void display() {
        if (!q.empty()) {
            cout << "Front of the queue: " << q.front() << endl;
        } else {
            cout << "Queue is empty." << endl;
        }
    }

    
    bool isEmpty() {
        return q.empty();
    }
};

void readFileAndEnqueue(const string& buses.txt, Queue& queue) {
    ifstream file(buses.txt);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            queue.enqueue(line); 
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    Queue queue;

    
    string filename = "bus.txt"; 
    readFileAndEnqueue(bus.txt, queue);

    
    queue.display();

    
    queue.dequeue();  
    queue.display();  

    
    queue.dequeue();
    queue.display();


    queue.dequeue();

    return 0;
}
