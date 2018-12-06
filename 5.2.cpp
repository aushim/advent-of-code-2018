#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    vector<string> polymers;
    for (string line; getline(cin, line);) {
        polymers.push_back(line);
    }

    for (string& polymer : polymers) {
        int min_length = INT_MAX;
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for(char& c : alphabet) {
            string condensed_polymer = polymer;
            condensed_polymer.erase(remove(condensed_polymer.begin(), condensed_polymer.end(), toupper(c)), condensed_polymer.end());
            condensed_polymer.erase(remove(condensed_polymer.begin(), condensed_polymer.end(), c), condensed_polymer.end());
            stack<char> units;
            for (char& unit : condensed_polymer) {
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
            if (units.size() < min_length) {
                min_length = units.size();
            }
        }
        cout << to_string(min_length) << endl;
    }

    return 0;
}