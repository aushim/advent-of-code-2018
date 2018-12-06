#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    queue<int> frequency_changes;
    for (string line; getline(cin, line);) {
        frequency_changes.push(stoi(line));
    }

    int current_frequency = 0;
    unordered_set<int> seen_frequencies;
    seen_frequencies.insert(current_frequency);
        
    while (true) {
        int frequency_change = frequency_changes.front();
        current_frequency += frequency_change;

        if (seen_frequencies.find(current_frequency) != seen_frequencies.end()) {
            cout << to_string(current_frequency) << endl;
            break;
        } else {
            seen_frequencies.insert(current_frequency);
        }
        
        frequency_changes.pop();
        frequency_changes.push(frequency_change);
    }

    return 0;
}