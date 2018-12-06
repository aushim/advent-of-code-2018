#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> box_ids;
    for (string line; getline(cin, line);) {
        box_ids.push_back(line);
    }

    for (string& id1 : box_ids) {
        for (string& id2 : box_ids) {
            if (id1 == id2 || id1.length() != id2.length()) {
                continue;
            }
            int diffCount = 0;
            string similar = "";
            for (int i = 0; i < id1.length(); i++) {
                if (id1[i] != id2[i]) {
                    diffCount++;
                } else {
                    similar += id1.substr(i, 1);
                }
            }
            if (diffCount == 1) {
                cout << similar << endl;
                return 0;
            }
        }
    }

    return 0;
}