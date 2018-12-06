#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int main() {
    vector<string> polymers;
    for (string line; getline(cin, line);) {
        polymers.push_back(line);
    }

    for (string& polymer : polymers) {
        stack<char> units;
        for (char& unit : polymer) {
            if (!units.empty()) {
                char last_unit = units.top();
                if (unit != last_unit && toupper(unit) == toupper(last_unit)) {
                    units.pop();
                } else {
                    units.push(unit);
                }
            } else {
                units.push(unit);
            }
        }
        cout << to_string(units.size()) << endl;
    }

    return 0;
}