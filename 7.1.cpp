#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <queue>
 
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
    string step_order = "";

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
            if (all_required_steps_done && done_steps.find(step) == done_steps.end()) {
                available_steps.push(step);
            }
        }
        char next_step = available_steps.top();
        done_steps.insert(next_step);
        step_order += next_step;
    }

    cout << step_order << endl;

    return 0;
}