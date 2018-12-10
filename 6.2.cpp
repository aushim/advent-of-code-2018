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

    int area = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.front().size(); j++) {
            int sum_distance = 0;
            for (int k = 0; k < coords.size(); k++) {
                int distance = abs(i - coords[k].first) + abs(j - coords[k].second);
                sum_distance += distance;
            }
            if (sum_distance < 10000) {
                area++;
            }
        }
    }

    cout << to_string(area) << endl;

    return 0;
}