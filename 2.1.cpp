#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    vector<string> box_ids;
    for (string line; getline(cin, line);) {
        box_ids.push_back(line);
    }

    int two_boxes = 0;
    int three_boxes = 0;
    unordered_map<char, int> count;
    for (string& id : box_ids) {
        count.clear();
        for(char& c : id) {
            if (count.find(c) == count.end()) {
                count.insert(make_pair(c, 1));
            } else {
                count[c]++;
            }
        }

        bool two_box = false;
        bool three_box = false;
        for (char& c : id) {
            if (count[c] == 2) {
                two_box = true;
            }
            if (count[c] == 3) {
                three_box = true;
            }
        }

        if (two_box) {
            two_boxes++;
        }
        if (three_box) {
            three_boxes++;
        }
    }

    cout << to_string(two_boxes * three_boxes) << endl;

    return 0;
}