#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <unordered_set>
 
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
    vector<pair<int, int> > coords;
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    for (string line; getline(cin, line);) {
        vector<string> parts = split(line, ", ");
        int x = stoi(parts[0]);
        int y = stoi(parts[1]);
        coords.push_back(make_pair(x, y));
        if (x > max_x) {
            max_x = x;
        }
        if (y > max_y) {
            max_y = y;
        }
    }

    vector<vector<int> > grid(max_x + 1, vector<int>(max_y + 1, -1));

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.front().size(); j++) {
            int min_distance = INT_MAX;
            for (int k = 0; k < coords.size(); k++) {
                int distance = abs(i - coords[k].first) + abs(j - coords[k].second);
                if (distance < min_distance) {
                    min_distance = distance;
                    grid[i][j] = k;
                } else if (distance == min_distance) {
                    grid[i][j] = -1;
                }
            }
        }
    }

    unordered_set<int> infinite_area_coords;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.front().size(); j++) {
            if (i != 0 && j != 0 && i != (grid.size() - 1) && j != (grid.front().size() - 1)) {
                continue;
            }
            if (grid[i][j] > -1) {
                infinite_area_coords.insert(grid[i][j]);
            }
        }
    }

    vector<int> area(coords.size());
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.front().size(); j++) {
            if (grid[i][j] > -1 && infinite_area_coords.find(grid[i][j]) == infinite_area_coords.end()) {
                area[grid[i][j]]++;
            }
        }
    }

    int max_area = INT_MIN;
    for (int i = 0; i < area.size(); i++) {
        if (area[i] > max_area) {
            max_area = area[i];
        }
    }

    cout << to_string(max_area) << endl;

    return 0;
}