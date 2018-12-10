#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
 
using namespace std;

int main() {
    unordered_map<char, unordered_set<char> > dependencies;
    unordered_set<char> unique_steps;
    for (string line; getline(cin, line);) {
        char dependency = line[5];
        char dependent = line[36];
        if (dependencies.find(dependent) == dependencies.end()) {
            unordered_set<char> chars;
            chars.insert(dependency);
            dependencies.insert(make_pair(dependent, chars));
        } else {
            unordered_set<char>& chars = dependencies.at(dependent);
            chars.insert(dependency);
        }
        if (dependencies.find(dependency) == dependencies.end()) {
            unordered_set<char> chars;
            dependencies.insert(make_pair(dependency, chars));
        }
        unique_steps.insert(dependency);
        unique_steps.insert(dependent);
    }

    unordered_set<char> done_steps;
    int num_workers = 5;
    int base_time = 60;
    unordered_map<char, int> doing_steps;
    string step_order = "";
    int total_time = 0;

    while (done_steps.size() != unique_steps.size()) {
        priority_queue<char, vector<char>, greater<char> > available_steps;
        for (auto it : dependencies) {
            char step = it.first;
            unordered_set<char>& step_dependencies = dependencies.at(step);
            bool all_required_steps_done = true;
            for (auto required_step : step_dependencies) {
                if (done_steps.find(required_step) == done_steps.end()) {
                    all_required_steps_done = false;
                }
            }
            if (all_required_steps_done && doing_steps.find(step) == doing_steps.end() && done_steps.find(step) == done_steps.end()) {
                available_steps.push(step);
            }
        }
        while (doing_steps.size() < num_workers && available_steps.size() > 0) {
            char next_step = available_steps.top();
            available_steps.pop();
            doing_steps.insert(make_pair(next_step, 0));   
        }
        for (auto it : doing_steps) {
            char current_step = it.first;
            int current_time = it.second + 1;
            doing_steps[current_step]++;
            int value = current_step - 64;
            int required_time = base_time + value;
            if (current_time == required_time) {
                done_steps.insert(current_step);
                step_order += current_step;
            }
        }
        for (auto done_step : done_steps) {
            if (doing_steps.find(done_step) != doing_steps.end()) {
                doing_steps.erase(done_step);
            }
        }
        total_time++;
    }

    cout << to_string(total_time) << endl;

    return 0;
}