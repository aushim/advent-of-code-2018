#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
 
using namespace std;

vector<string> split(string& str, const string& separators) {
    vector<string> results;
    char * pch;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    pch = strtok(cstr, separators.c_str());
    while (pch != NULL) {
        results.push_back(pch);
        pch = strtok (NULL, separators.c_str());
    }
    delete [] cstr;
    return results;
}

int main() {
    vector<string> records;
    for (string line; getline(cin, line);) {
        records.push_back(line);
    }

    sort(records.begin(), records.end());

    int current_guard = -1;
    int prev_time = -1;
    int current_time = -1;
    
    unordered_map<int, unordered_map<int, int> > asleep_minutes_count;

    for (string& record : records) {
        vector<string> parts = split(record, " []-:#");
        prev_time = current_time;
        current_time = stoi(parts[4]);
        if (parts[5] == "Guard") {
            current_guard = stoi(parts[6]);
        }
        if (parts[5] == "wakes") {
            int duration = current_time - prev_time;
            if (asleep_minutes_count.find(current_guard) == asleep_minutes_count.end()) {
                unordered_map<int, int> count;
                for (int time = prev_time; time < current_time; time++) {
                    count.insert(make_pair(time, 1));
                }
                asleep_minutes_count.insert(make_pair(current_guard, count));
            } else {
                unordered_map<int, int>& count = asleep_minutes_count.at(current_guard);
                for (int time = prev_time; time < current_time; time++) {
                    if (count.find(time) == count.end()) {
                        count.insert(make_pair(time, 1));
                    } else {
                        count[time]++;
                    }
                }
            }
        }

    }

    int max_count = INT_MIN;
    int max_count_minute = -1;
    int max_count_guard = -1;
    for (auto it1: asleep_minutes_count) {
        for (auto it2: it1.second) {
            if (it2.second > max_count) {
                max_count = it2.second;
                max_count_minute = it2.first;
                max_count_guard = it1.first;
            }
        }
    }

    cout << to_string(max_count_guard * max_count_minute) << endl;

    return 0;
}