#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

// Brute Force String Search to find patterns in noise data
bool bruteForceSearch(const std::string& text, const std::string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    
    for (int i = 0; i <= textLength - patternLength; i++) {
        int j = 0;
        while (j < patternLength && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == patternLength) {
            return true; // Pattern found
        }
    }
    return false;
}

// Rabin-Karp Algorithm for pattern matching (e.g., detect specific noise types)
bool rabinKarpSearch(const std::string& text, const std::string& pattern) {
    int m = pattern.length();
    int n = text.length();
    int d = 256; // Number of characters in the input alphabet
    int q = 101; // A prime number for hashing
    int h = 1;
    int t = 0; // Hash value for text
    int p = 0; // Hash value for pattern

    // Calculate the hash value for the pattern and the first window of the text
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate hash values for pattern and text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) {
                j++;
            }
            if (j == m) return true; // Pattern found
        }

        // Calculate hash value for next window of text
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    return false;
}

// Skip List Node
struct Node {
    int value;
    std::vector<Node*> forward;
    Node(int level, int value) : value(value), forward(level, nullptr) {}
};

// Skip List to store and efficiently manage noise data
class SkipList {
private:
    int maxLevel;
    int level;
    Node* header;
    
public:
    SkipList(int maxLevel) : maxLevel(maxLevel), level(0) {
        header = new Node(maxLevel, -1); // Header node with sentinel value
    }

    void insert(int value) {
        std::vector<Node*> update(maxLevel, nullptr);
        Node* current = header;
        
        // Traverse the skip list to find the position for insertion
        for (int i = level - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        // If the value is not already present, insert it
        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level; i < newLevel; i++) {
                    update[i] = header;
                }
                level = newLevel;
            }
            
            current = new Node(newLevel, value);
            for (int i = 0; i < newLevel; i++) {
                current->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = current;
            }
        }
    }

    void display() {
        std::cout << "Skip List:" << std::endl;
        for (int i = 0; i < level; i++) {
            Node* current = header->forward[i];
            std::cout << "Level " << i + 1 << ": ";
            while (current != nullptr) {
                std::cout << current->value << " ";
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }

    // Generate a random level for the new node
    int randomLevel() {
        int level = 1;
        while (rand() % 2 && level < maxLevel) {
            level++;
        }
        return level;
    }
};

// Lookup Table for noise mitigation strategies based on thresholds
std::unordered_map<std::string, std::string> lookupTable = {
    {"high", "Implement noise barriers and restrict construction during peak hours."},
    {"medium", "Encourage noise-reducing technology in construction sites."},
    {"low", "Encourage use of quieter machines and implement green spaces."}
};

int main() {
    // Brute Force Search: Detect spikes in noise data
    std::string noiseData = "trafficconstructiontraffictraffic";
    std::string noisePattern = "construction";
    bool foundPattern = bruteForceSearch(noiseData, noisePattern);
    std::cout << "Brute Force Search: Pattern Found? " << (foundPattern ? "Yes" : "No") << std::endl;

    // Rabin-Karp Algorithm: Detect specific noise types
    bool patternFound = rabinKarpSearch(noiseData, noisePattern);
    std::cout << "Rabin-Karp Search: Pattern Found? " << (patternFound ? "Yes" : "No") << std::endl;

    // Skip List: Managing noise records for efficient search
    SkipList skipList(3);
    skipList.insert(100);  // 100 decibels in a city block
    skipList.insert(75);
    skipList.insert(80);
    skipList.insert(90);
    skipList.display();

    // Lookup Table: Lookup noise mitigation strategies
    std::string noiseLevel = "high";
    std::cout << "Lookup Table: " << lookupTable[noiseLevel] << std::endl;

    return 0;
}
